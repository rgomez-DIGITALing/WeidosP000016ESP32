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

// static unsigned long lastTime = 0;
// static int counter = 0;
void AzureIoTCollectionClass::loop(){
    for(int i=0; i<NUM_AZURE_IOT_DEVICES; i++){
        if(AzureIoTPool[i]) AzureIoTPool[i]->loop();
    }
    //Serial.print("Counter: ");
    //Serial.println(counter);
    // if(millis()-lastTime>50){
    //     if(AzureIoTPool[counter]) AzureIoTPool[counter]->loop();    
    //     counter++;
    //     if(counter == 6) counter = 0;
    //     lastTime = millis();
    // }
    
    return;
}


void AzureIoTCollectionClass::stop(){
    for(int i=0; i<NUM_AZURE_IOT_DEVICES; i++){
        if(AzureIoTPool[i]) AzureIoTPool[i]->stop();
    }
    return;
}





AzureIoTCollectionClass AzureIoTCollection;
