#include "EM3PH_Manager_BaseClass.h"
#include <LogModule.h>
#include <clockModule.h>


#include "../../../payloadGenerators/payloadGenerators.h"
#include "../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../collections/AzureIoTCollection/AzureIoTCollection.h"




EM3PHManager_BaseClass::EM3PHManager_BaseClass(uint8_t deviceId) : deviceId(deviceId)
{
}

EM3PHManager_BaseClass::EM3PHManager_BaseClass(uint8_t deviceId, int ctPrimary, int ctSecondary) : deviceId(deviceId),
  ctPrimary(ctPrimary),
  ctSecondary(ctSecondary)
{
}


// EM3PHManager_BaseClass::~EM3PHManager_BaseClass()
// {
//   delete em3ph;
// }



EnergyMeterUpdateState_t EM3PHManager_BaseClass::loop(){
    em3phManagerData_t msg;

    switch(state){
      case ENERGY_METER_IDLE:
        break;


      case UPDATE_ENERGY_METER:
        //state = ENERGY_METER_UPDATED;
        if(!em3ph->begin()){
         state = ENERGY_METER_RETRY_UPDATE;
         em3ph->stop();
         LogError("Modbus Client for device ID %i could not begin.", deviceId);
         break;
        }

        if(em3ph->update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_RETRY_UPDATE;
        em3ph->stop();
        break;

      case ENERGY_METER_RETRY_UPDATE:
        numTries++;
        if(numTries>maxTries){
          numTries = 0;
          //state = PASS_MESSAGE;
          state = ENERGY_METER_UPDATE_FAILED;
          LogError("Energy meter update failed.");
        }else{
          state = UPDATE_ENERGY_METER;
          LogError("Retrying (%i/%i)", numTries, maxTries);
        }
        break;

      case ENERGY_METER_UPDATED:
        LogInfo(" Updated EM750  (ID:%i)", deviceId);
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        msg.dataSourceStatus = 0;
        em3ph->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        em3ph->updatePreviousValues();
        state = END_TASK;
        break;

      case ENERGY_METER_UPDATE_FAILED:
        
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        em3ph->resetPrevValues();
        em3ph->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        
        state = END_TASK;
        break;

      case END_TASK:

        state = ENERGY_METER_IDLE;
        //em750.stop();
        break;
    }

    return state;
}

// bool EM3PHManager::sendProperties(){
//   AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];

//   if(propertiesSent) return propertiesSent;
//   if(azureDevice->getStatus() == azure_iot_connected){
//     size_t payload_buffer_length = 0;
//     uint8_t* payload_buffer = azureDevice->getDataBuffer2();
//     azure_iot_t* azureIoT = azureDevice->getAzureIoT();
//     az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
//     //em750_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, &em750);
//     int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
//     if(!error) propertiesSent = true;
//   }
//   return propertiesSent;
// }
