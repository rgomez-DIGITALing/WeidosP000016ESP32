#include "EM220Manager.h"
#include <LogModule.h>
#include <clockModule.h>


#include "../../../payloadGenerators.h"
#include "../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../collections/AzureIoTCollection/AzureIoTCollection.h"



EM220Manager::EM220Manager(int deviceId, int ctPrimary, int ctSecondary, uint8_t maxTries) : 
em220(nullptr), 
deviceId(deviceId),
maxTries(maxTries)
{
  Serial.println("Creating an EM220Manager");
  Serial.println("Creating an EM110Manager");
  Serial.print("CT Primary: ");
  Serial.print(ctPrimary);
  Serial.print("  -  CT Secondary: ");
  Serial.println(ctSecondary);
  em220 = new EM220(deviceId, ctPrimary, ctSecondary);
}


EM220Manager::~EM220Manager()
{
  delete em220;
}



EnergyMeterUpdateState_t EM220Manager::loop(){
    switch(state){
      case ENERGY_METER_IDLE:
        break;

      case UPDATE_ENERGY_METER:
        //state = EM220_SUCCESS;
        if(!em220->begin()){
         state = ENERGY_METER_UPDATE_FAILED;
         em220->stop();
         LogError("Modbus Client for device ID %i could not begin.", deviceId);  
         break;
        }

        if(em220->update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_UPDATE_FAILED;
        em220->stop();
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
        LogInfo(" Updated EM220  (ID:%i)", deviceId);
        state = PASS_MESSAGE;
      break;

      case PASS_MESSAGE:
        em3phManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        em220->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        state = END_TASK;
        break;
      case END_TASK:
        state = ENERGY_METER_IDLE;
        //em220->stop();
        break;
    }

    return state;
}


bool EM220Manager::sendProperties(){
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];
  if(!propertiesSent){
    if(azureDevice->getStatus() == azure_iot_connected){
      size_t payload_buffer_length = 0;
      uint8_t* payload_buffer = azureDevice->getDataBuffer2();
      azure_iot_t* azureIoT = azureDevice->getAzureIoT();
      az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
      em220_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, em220);
      int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
      if(!error) propertiesSent = true;
    }
  }
  return propertiesSent;
}
