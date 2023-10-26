#include "EM110Manager.h"
#include <LogModule.h>
#include <clockModule.h>


#include "../../../payloadGenerators.h"
#include "../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../collections/AzureIoTCollection/AzureIoTCollection.h"



EM110Manager::EM110Manager(int deviceId, int ctPrimary, int ctSecondary, uint8_t maxTries) : 
em110(nullptr), 
deviceId(deviceId),
maxTries(maxTries)
{
  em110 = new EM110(deviceId, ctPrimary, ctSecondary);
}


EM110Manager::~EM110Manager()
{
  delete em110;
}


EnergyMeterUpdateState_t EM110Manager::loop(){
    switch(state){
      case ENERGY_METER_IDLE:
        break;

      case UPDATE_ENERGY_METER:
        //state = EM220_SUCCESS;
        if(!em110->begin()){
         state = ENERGY_METER_UPDATE_FAILED;
         em110->stop();
         LogError2(F("Modbus Client for device ID %i could not begin."), deviceId);
         break;
        }

        if(em110->update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_UPDATE_FAILED;
        em110->stop();
        break;
      
      case ENERGY_METER_UPDATE_FAILED:
        numTries++;
        if(numTries>maxTries){
          numTries = 0;
          state = PASS_MESSAGE;
          LogError2(F("Energy meter update failed."));
        }else{
          state = UPDATE_ENERGY_METER;
          LogError2(F("Retrying (%i/%i)"), numTries, maxTries);
        }
        break;

      case ENERGY_METER_UPDATED:
        LogInfo2(F(" Updated EM110  (ID:%i)"), deviceId);
        state = PASS_MESSAGE;
      break;

      case PASS_MESSAGE:
        em1phManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        em110->getData(msg.payload);
        LogInfo2(F("Pushing data for device ID: %i"), deviceId);
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


bool EM110Manager::sendProperties(){
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];
  if(!propertiesSent){
    if(azureDevice->getStatus() == azure_iot_connected){
      size_t payload_buffer_length = 0;
      uint8_t* payload_buffer = azureDevice->getDataBuffer2();
      azure_iot_t* azureIoT = azureDevice->getAzureIoT();
      az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
      em110_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, em110);
      int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
      if(!error) propertiesSent = true;
    }
  }
  return propertiesSent;
}
