#include "AzureDevices.h"
#include "../classes/AzureIoTClass/mqttCallbacks.h"
#include <Ethernet.h>
#include <ArduinoBearSSL.h>

#include "../classes/AzureIoTCollection/AzureIoTCollection.h"

EthernetClient ethernetClient0(1);
EthernetClient ethernetClient1(2);
EthernetClient ethernetClient2(3);
EthernetClient ethernetClient3(4);
EthernetClient ethernetClient4(5);
EthernetClient ethernetClient5(6);

AzureIoTDevice* Azure0 = nullptr;
AzureIoTDevice* Azure1 = nullptr;
AzureIoTDevice* Azure2 = nullptr;
AzureIoTDevice* Azure3 = nullptr;
AzureIoTDevice* Azure4 = nullptr;
AzureIoTDevice* Azure5 = nullptr;


#define MQTT_CLIENT_BUFFER_SIZE 3000

void createObjects(){
    BearSSLClient* bear_ssl_client0 = new BearSSLClient(ethernetClient0);
    MQTTClient* mqttClient0 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure0 = new AzureIoTDevice(mqttClient0, bear_ssl_client0);
    uint8_t* bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
    Azure0->setDataBuffer(bufferPtr);
    bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
    Azure0->setDataBuffer2(bufferPtr);


    BearSSLClient* bear_ssl_client1 = new BearSSLClient(ethernetClient1);
    MQTTClient* mqttClient1 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure1 = new AzureIoTDevice(mqttClient1, bear_ssl_client1);
    bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
    Azure1->setDataBuffer(bufferPtr);
    bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
    Azure1->setDataBuffer2(bufferPtr);



    BearSSLClient* bear_ssl_client2 = new BearSSLClient(ethernetClient2);
    MQTTClient* mqttClient2 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure2 = new AzureIoTDevice(mqttClient2, bear_ssl_client2);
    bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
    Azure2->setDataBuffer(bufferPtr);
    bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
    Azure2->setDataBuffer2(bufferPtr);


    BearSSLClient* bear_ssl_client3 = new BearSSLClient(ethernetClient3);
    MQTTClient* mqttClient3 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    Azure3 = new AzureIoTDevice(mqttClient3, bear_ssl_client3);
    bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
    Azure3->setDataBuffer(bufferPtr);
    bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
    Azure3->setDataBuffer2(bufferPtr);


    // BearSSLClient* bear_ssl_client4 = new BearSSLClient(ethernetClient4);
    // MQTTClient* mqttClient4 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    // Azure4 = new AzureIoTDevice(mqttClient4, bear_ssl_client4);
    // bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
    // Azure4->setDataBuffer(bufferPtr);
    // bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
    // Azure4->setDataBuffer2(bufferPtr);

    // BearSSLClient* bear_ssl_client5 = new BearSSLClient(ethernetClient5);
    // MQTTClient* mqttClient5 = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
    // Azure5 = new AzureIoTDevice(mqttClient5, bear_ssl_client5);
    // bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
    // Azure5->setDataBuffer(bufferPtr);
    // bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
    // Azure5->setDataBuffer2(bufferPtr);
}

char emModelId[60] = "dtmi:conexiones:EnergyMeter_6bm;1";
char gwModelId[60] = "dtmi:conexionesSmartFactory:gateway_62;1";
char gatewayId[50] = IOT_CONFIG_DEVICE_GATEWAY_ID;
char* scopeId = DPS_ID_SCOPE;

void configureAzureDevices(){
    //Azure 0 is always for the Gateway
    Azure0->usingSasToken(IOT_CONFIG_DEVICE_GATEWAY_KEY);
    Azure0->setDeviceId(IOT_CONFIG_DEVICE_GATEWAY_ID);
    Azure0->setDpsScopeId(scopeId);
    Azure0->setModelId(gwModelId);
    Azure0->init();
    Azure0->setOnCommandReceived(gateway_on_command_request_received);
  
    Azure1->usingSasToken(IOT_CONFIG_DEVICE_1_KEY);
    Azure1->setDeviceId(IOT_CONFIG_DEVICE_1_ID);
    Azure1->setDpsScopeId(scopeId);
    Azure1->setGatewayId(gatewayId);
    Azure1->setModelId(emModelId);
    Azure1->init();

    Azure2->usingSasToken(IOT_CONFIG_DEVICE_2_KEY);
    Azure2->setDeviceId(IOT_CONFIG_DEVICE_2_ID);
    Azure2->setDpsScopeId(scopeId);
    Azure2->setGatewayId(gatewayId);
    Azure2->setModelId(emModelId);
    Azure2->init();

    #ifndef BATCH_IT
    Azure3->usingSasToken(IOT_CONFIG_DEVICE_3_KEY);
    Azure3->setDeviceId(IOT_CONFIG_DEVICE_3_ID);
    Azure3->setDpsScopeId(scopeId);
    Azure3->setGatewayId(gatewayId);
    Azure3->setModelId(emModelId);
    Azure3->init();


    Azure4->usingSasToken(IOT_CONFIG_DEVICE_4_KEY);
    Azure4->setDeviceId(IOT_CONFIG_DEVICE_4_ID);
    Azure4->setDpsScopeId(scopeId);
    Azure4->setGatewayId(gatewayId);
    Azure4->setModelId(emModelId);
    Azure4->init();

    Azure5->usingSasToken(IOT_CONFIG_DEVICE_5_KEY);
    Azure5->setDeviceId(IOT_CONFIG_DEVICE_5_ID);
    Azure5->setDpsScopeId(scopeId);
    Azure5->setGatewayId(gatewayId);
    Azure5->setModelId(emModelId);
    Azure5->init();


    #endif
}


void setAzureIoTCollectionDevices(){
    AzureIoTCollection.setAzureIoTDevice(Azure0, 0);
    AzureIoTCollection.setAzureIoTDevice(Azure1, 1);
    AzureIoTCollection.setAzureIoTDevice(Azure2, 2);
    AzureIoTCollection.setAzureIoTDevice(Azure3, 3);
    // AzureIoTCollection.setAzureIoTDevice(Azure4, 4);
    //AzureIoTCollection.setAzureIoTDevice(Azure5, 5);
    return;
}
