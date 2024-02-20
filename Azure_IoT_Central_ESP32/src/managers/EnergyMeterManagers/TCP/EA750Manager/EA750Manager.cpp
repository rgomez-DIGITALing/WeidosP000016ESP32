#include "EA750Manager.h"

#include "../../../../payloadGenerators/payloadGenerators.h"
#include "../../../../collections/DataHubCollection/DataHubCollection.h"
#include "../../../../collections/AzureIoTCollection/AzureIoTCollection.h"


EA750Manager::EA750Manager(ModbusTCPClient& client, IPAddress ip, int deviceId) : EM3PHManager_BaseClass(deviceId) {
  Serial.println("Let's create an EA750 Manager");
  em3ph = new EA3PH_TCP_ValueLine(client, ip);
}

EA750Manager::~EA750Manager(){
  delete em3ph;
}

bool EA750Manager::sendProperties(){
  AzureIoTDevice* azureDevice = AzureIoTCollection[deviceId];

  if(propertiesSent) return propertiesSent;
  // propertiesSent = true;
  if(azureDevice->getStatus() == azure_iot_connected){
    size_t payload_buffer_length = 0;
    uint8_t* payload_buffer = azureDevice->getDataBuffer2();
    azure_iot_t* azureIoT = azureDevice->getAzureIoT();
    az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
    ea750_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, this);
    int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
    if(!error) propertiesSent = true;
  }

  return propertiesSent;
}
