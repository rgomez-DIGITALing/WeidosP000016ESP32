#include "AzureIoTCollection.h"



void AzureIoTCollectionClass::init(){
    for(int i=0; i<NUM_AZURE_IOT_DEVICES; i++){
        AzureIoTPool[i] = nullptr;
    }
    return;
}

void AzureIoTCollectionClass::setAzureIoTDevice(AzureIoTDevice* azureIoTDevice, int slot){ 
    AzureIoTPool[slot] = azureIoTDevice;
    return;
}

void AzureIoTCollectionClass::loop(){
    for(int i=0; i<NUM_AZURE_IOT_DEVICES; i++){
        if(AzureIoTPool[i]) AzureIoTPool[i]->loop();
    }
    return;
}


void AzureIoTCollectionClass::stop(){
    for(int i=0; i<NUM_AZURE_IOT_DEVICES; i++){
        if(AzureIoTPool[i]) AzureIoTPool[i]->stop();
    }
    return;
}





AzureIoTCollectionClass AzureIoTCollection;
