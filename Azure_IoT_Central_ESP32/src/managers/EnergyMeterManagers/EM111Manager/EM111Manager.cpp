#include "EM111Manager.h"
#include <LogModule.h>
#include <clockModule.h>


#include "../../../payloadGenerators.h"
#include "../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../collections/AzureIoTCollection/AzureIoTCollection.h"



EM111Manager::EM111Manager(int deviceId, uint8_t maxTries) : 
em111(nullptr), 
deviceId(deviceId),
maxTries(maxTries)
{
  Serial.println("Creating an EM111Manager");
  em111 = new EM111(deviceId);
}


EM111Manager::~EM111Manager()
{
  delete em111;
}


EnergyMeterUpdateState_t EM111Manager::loop(){
    switch(state){
      case ENERGY_METER_IDLE:
        break;

      case UPDATE_ENERGY_METER:
        //state = EM220_SUCCESS;
        if(!em111->begin()){
         state = ENERGY_METER_UPDATE_FAILED;
         em111->stop();
         LogError("Modbus Client for device ID %i could not begin.", deviceId);  
         break;
        }

        if(em111->update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_UPDATE_FAILED;
        em111->stop();
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
        LogInfo(" Updated EM111  (ID:%i)", deviceId);
        state = PASS_MESSAGE;
      break;

      case PASS_MESSAGE:
        em1phManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        msg.backup = 0;
        em111->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        state = END_TASK;
        break;
      case END_TASK:
        state = ENERGY_METER_IDLE;
        //em111->stop();
        break;
    }

    return state;
}


bool EM111Manager::sendProperties(){
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];
  if(!propertiesSent){
    if(azureDevice->getStatus() == azure_iot_connected){
      size_t payload_buffer_length = 0;
      uint8_t* payload_buffer = azureDevice->getDataBuffer2();
      azure_iot_t* azureIoT = azureDevice->getAzureIoT();
      az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
      em111_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, em111);
      int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
      if(!error) propertiesSent = true;
    }
  }
  return propertiesSent;
}
