#include "EA750Manager.h"
#include <LogModule.h>
#include <clockModule.h>


#include "../../../payloadGenerators.h"
#include "../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../collections/AzureIoTCollection/AzureIoTCollection.h"



EnergyMeterUpdateState_t EA750Manager::loop(){
    switch(state){
      case ENERGY_METER_IDLE:
        break;

      case UPDATE_ENERGY_METER:
        //state = ENERGY_METER_UPDATED;
        if(!ea750.begin()){
         state = ENERGY_METER_UPDATE_FAILED;
         ea750.stop();
         LogError("Modbus Client for device ID %i could not begin.", deviceId);  
         break;
        }

        if(ea750.update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_UPDATE_FAILED;
        ea750.stop();
        break;
      
      case ENERGY_METER_UPDATE_FAILED:
        numTries++;
        if(numTries>maxTries){
          numTries = 0;
          state = PASS_MESSAGE;
          LogError("Energy meter update failed.");
        }else{
          state = UPDATE_ENERGY_METER;
          LogError("Retrying (%i/%i)", numTries, maxTries);
        }
        break;

      case ENERGY_METER_UPDATED:
        LogInfo(" Updated EA750  (ID:%i)", deviceId);
        state = PASS_MESSAGE;
        break;

      case PASS_MESSAGE:
        em3phManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        ea750.getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        state = END_TASK;
        break;

      case END_TASK:
        state = ENERGY_METER_IDLE;
        //ea750.stop();
        break;
    }

    return state;
}

bool EA750Manager::sendProperties(){
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];

  if(propertiesSent) return propertiesSent;
  if(azureDevice->getStatus() == azure_iot_connected){
    size_t payload_buffer_length = 0;
    uint8_t* payload_buffer = azureDevice->getDataBuffer2();
    azure_iot_t* azureIoT = azureDevice->getAzureIoT();
    az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
    ea750_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, &ea750);
    int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
    if(!error) propertiesSent = true;
  }
  return propertiesSent;
}
