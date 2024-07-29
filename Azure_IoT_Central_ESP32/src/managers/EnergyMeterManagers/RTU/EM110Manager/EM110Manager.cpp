#include "EM110Manager.h"

#include "../../../../payloadGenerators/payloadGenerators.h"
#include "../../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../../collections/AzureIoTCollection/AzureIoTCollection.h"



EM110Manager::EM110Manager(uint8_t deviceId, int ctPrimary, int ctSecondary) : EM1PHManager_BaseClass(deviceId, ctPrimary, ctSecondary) {
  Serial.println("Let's create an EM120 Manager");
  em1ph = new EM1PH_RTU_BasicLine(deviceId);
}


EM110Manager::EM110Manager(uint8_t deviceId) : EM1PHManager_BaseClass(deviceId) {
  Serial.println("Let's create an EM110 Manager");
  em1ph = new EM1PH_RTU_BasicLine(deviceId);
}


EM110Manager::~EM110Manager(){
  delete em1ph;
}


bool EM110Manager::sendProperties(){
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];

  if(propertiesSent) return propertiesSent;
  if(azureDevice->getStatus() == azure_iot_connected){
    size_t payload_buffer_length = 0;
    uint8_t* payload_buffer = azureDevice->getDataBuffer2();
    azure_iot_t* azureIoT = azureDevice->getAzureIoT();
    az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
    em110_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, this);
    int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
    if(!error) propertiesSent = true;
  }

  return propertiesSent;
}
