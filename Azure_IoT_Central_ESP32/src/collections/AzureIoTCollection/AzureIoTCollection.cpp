#include "AzureIoTCollection.h"
#include <Ethernet.h>
#include <ArduinoBearSSL.h>
#include "../../classes/PersistentData/PersistentDataClass.h"

#define MQTT_CLIENT_BUFFER_SIZE 3000

void AzureIoTCollectionClass::init(){
    for(int i=0; i<MAX_NUM_AZURE_DEVICES; i++){
        AzureIoTPool[i] = nullptr;
    }

    if(PersistentDataModule.isScopeIdSet()) {
        PersistentDataModule.getScopeId(scopeId);
        scopeIdSet = true;
    }


    return;
}

char* emptyModelId2 = "";
void AzureIoTCollectionClass::configure(){
    if(!scopeIdSet){
        // Serial.println("Scope ID is not set heheheh");
        //return;
    }
    PersistentDataModule.getScopeId(scopeId);

    for(uint8_t i=0; i<MAX_NUM_AZURE_DEVICES; i++){
        // Serial.println("Is it configured? ");
        if(!PersistentDataModule.isAzureIdSet(i)) continue;
        if(!PersistentDataModule.isSasKeySet(i)) continue;
        PersistentDataModule.getAzureId(azureDeviceIds[i], i);
        PersistentDataModule.getSasKey(azureSasKeys[i], i);

        AzureIoTDevice* azureIoTDevice = new AzureIoTDevice(i);
        azureIoTDevice->setDpsScopeId(scopeId);
        azureIoTDevice->setDeviceId(azureDeviceIds[i]);
        azureIoTDevice->usingSasToken(azureSasKeys[i]);
        azureIoTDevice->setModelId(azureSasKeys[i]);
        azureIoTDevice->setModelId(emptyModelId2);
        azureIoTDevice->init();

        AzureIoTPool[i] = azureIoTDevice;
    }
    return;
}


void AzureIoTCollectionClass::createObjects(){
    for(int i=0; i<MAX_NUM_AZURE_DEVICES; i++){
        if(AzureIoTPool[i]){
            Serial.print("Lets create MQTT and Bear SSL clients for Azure #");
            Serial.println(i);
            uint8_t* bufferPtr = nullptr;
            Serial.print("Ethernet socket: ");
            Serial.println(i+1);
            EthernetClient* ethernetClient = new EthernetClient(i+1);
            BearSSLClient* bear_ssl_client = new BearSSLClient(*ethernetClient);
            MQTTClient* mqttClient = new MQTTClient(MQTT_CLIENT_BUFFER_SIZE);
            AzureIoTPool[i]->setClients(mqttClient, bear_ssl_client);
            bufferPtr = new uint8_t[AZ_IOT_DATA_BUFFER_SIZE];
            AzureIoTPool[i]->setDataBuffer(bufferPtr);
            bufferPtr = new uint8_t[DATA_BUFFER_SIZE];
            AzureIoTPool[i]->setDataBuffer2(bufferPtr);
        }
    }
}

void AzureIoTCollectionClass::setAzureIoTDevice(AzureIoTDevice* azureIoTDevice, int slot){ 
    AzureIoTPool[slot] = azureIoTDevice;
    return;
}


void AzureIoTCollectionClass::loop(){
    for(int i=0; i<MAX_NUM_AZURE_DEVICES; i++){
        if(AzureIoTPool[i]) AzureIoTPool[i]->loop();
    }

    return;
}


void AzureIoTCollectionClass::stop(){
    for(int i=0; i<MAX_NUM_AZURE_DEVICES; i++){
        if(AzureIoTPool[i]) AzureIoTPool[i]->stop();
    }

    return;
}


void AzureIoTCollectionClass::restoreScopeId(){
    PersistentDataModule.getScopeId(scopeId);
    return;
}


void AzureIoTCollectionClass::restoreAzureId(uint8_t slot){
    PersistentDataModule.getAzureId(azureDeviceIds[slot], slot);
    return;
}


void AzureIoTCollectionClass::restoreSasKey(uint8_t slot){
    PersistentDataModule.getSasKey(azureSasKeys[slot], slot);
    return;
}

void AzureIoTCollectionClass::setAzureId(String& azureId, uint8_t slot){
    PersistentDataModule.saveAzureId(azureId, slot);
    char* destination = azureDeviceIds[slot];
    strcpy(destination, azureId.c_str());

    return;
}

void AzureIoTCollectionClass::setSasKey(String& sasKey, uint8_t slot){
    PersistentDataModule.saveAzureSasKey(sasKey, slot);
    char* destination = azureSasKeys[slot];
    strcpy(destination, sasKey.c_str());

    return;
}



AzureIoTCollectionClass AzureIoTCollection;
