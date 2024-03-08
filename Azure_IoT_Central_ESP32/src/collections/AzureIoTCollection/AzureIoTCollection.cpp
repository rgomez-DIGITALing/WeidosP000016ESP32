#include "AzureIoTCollection.h"
#include "../../classes/PersistentData/PersistentDataClass.h"



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


void AzureIoTCollectionClass::configure(){
    if(!scopeIdSet){
        Serial.println("Scope ID is not set heheheh");
        //return;
    } 

    for(uint8_t i=0; i<MAX_NUM_AZURE_DEVICES; i++){
        Serial.println("Is it configured? ");
        if(!PersistentDataModule.isAzureIdSet(i)) continue;
        if(!PersistentDataModule.isSasKeySet(i)) continue;
        Serial.print("Azure paremeters are set for: ");
        Serial.println(i);
        AzureIoTDevice* azureIoTDevice = new AzureIoTDevice(i);
        PersistentDataModule.getAzureId(azureDeviceIds[i], i);
        PersistentDataModule.getSasKey(azureSasKeys[i], i);
        azureIoTDevice->setDeviceId(azureDeviceIds[i]);
        azureIoTDevice->usingSasToken(azureSasKeys[i]);

        AzureIoTPool[i] = azureIoTDevice;
    }
    return;
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





AzureIoTCollectionClass AzureIoTCollection;
