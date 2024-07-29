#include "EM122TCPManager.h"

#include "../../../../payloadGenerators/payloadGenerators.h"
#include "../../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../../collections/AzureIoTCollection/AzureIoTCollection.h"



EM122TCPManager::EM122TCPManager(ModbusTCPClient& client, IPAddress ip, int deviceId) : EM3PHManager_BaseClass(deviceId) {
  Serial.println("Let's create an EM120-TCP Manager");
  em3ph = new EM3PH_TCP_BasicLine(deviceId, client, ip);
}


EM122TCPManager::~EM122TCPManager(){
  delete em3ph;
}


bool EM122TCPManager::sendProperties(){

  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];
  if(propertiesSent) return propertiesSent;
  //propertiesSent = true;
  
  if(azureDevice->getStatus() == azure_iot_connected){
    size_t payload_buffer_length = 0;
    uint8_t* payload_buffer = azureDevice->getDataBuffer2();
    azure_iot_t* azureIoT = azureDevice->getAzureIoT();
    az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
    em122Tcp_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, this);
    int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
    if(!error) propertiesSent = true;
  }

  return propertiesSent;
}
