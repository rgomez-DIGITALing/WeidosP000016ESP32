#include "EM110Manager.h"

//#include "DataHub.h"
//#include "../../AzureDevices.h"
#include "../../payloadGenerators.h"
#include <LogModule.h>
#include <clockModule.h>
#include "../DataHubCollection/DataHubCollection.h"
//#include "../../globals/AzureDevices.h"


EM110Manager::EM110Manager(int deviceId, int ctPrimary, int ctSecondary, uint8_t maxTries) : 
em110(nullptr), 
deviceId(deviceId),
maxTries(maxTries)
{
  Serial.println("Creating an EM110Manager");
  Serial.print("CT Primary: ");
  Serial.print(ctPrimary);
  Serial.print("  -  CT Secondary: ");
  Serial.println(ctSecondary);
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
         LogError("Modbus Client for device ID %i could not begin.", deviceId);
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
          state = END_TASK;
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
        em1phManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        em110->validateData();
        em110->getData(msg.payload);
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


bool EM110Manager::sendProperties(){
  //AzureIoTDevice* azureDevice = AzureDeviceCollection.getAzureIoTDevice(deviceId);
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];
  if(!propertiesSent){
    if(azureDevice->getStatus() == azure_iot_connected){
      size_t payload_buffer_length = 0;
      uint8_t* payload_buffer = azureDevice->getDataBuffer2();
      azure_iot_t* azureIoT = azureDevice->getAzureIoT();
      az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
      //em750_generete_payload(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
      em110_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, em110);
      int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
      if(!error) propertiesSent = true;
    }
  }
  return propertiesSent;
}
