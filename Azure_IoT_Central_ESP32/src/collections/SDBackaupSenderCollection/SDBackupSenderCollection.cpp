#include "SDBackupSenderCollection.h"



void SDBackupSenderCollectionClass::init(){
    weidosBackupSender = nullptr;
    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        em1phBackupSenderPool[i] = nullptr;
        em3phBackupSenderPool[i] = nullptr;
        flowMeterBackupSenderPool[i] = nullptr;
        
    }
}


void SDBackupSenderCollectionClass::begin(){
    if(weidosBackupSender) weidosBackupSender->begin();
    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        if(em1phBackupSenderPool[i]) em1phBackupSenderPool[i]->begin();
        if(em3phBackupSenderPool[i]) em3phBackupSenderPool[i]->begin();
        if(flowMeterBackupSenderPool[i]) flowMeterBackupSenderPool[i]->begin();
    }
}



void SDBackupSenderCollectionClass::loop(){
    if(weidosBackupSender) weidosBackupSender->loop();
    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        if(em1phBackupSenderPool[i]) em1phBackupSenderPool[i]->loop();
        if(em3phBackupSenderPool[i]) em3phBackupSenderPool[i]->loop();
        if(flowMeterBackupSenderPool[i]) flowMeterBackupSenderPool[i]->loop();
    }
}



void SDBackupSenderCollectionClass::setBackupSender(SDBackupSenderClass<WeidosManagerData_t>& sdBackupDataSender){ 
    weidosBackupSender = &sdBackupDataSender;
}

void SDBackupSenderCollectionClass::setBackupSender(SDBackupSenderClass<em1phManagerData_t>& sdBackupDataSender, int slot){ 
    em1phBackupSenderPool[slot] = &sdBackupDataSender;
}

void SDBackupSenderCollectionClass::setBackupSender(SDBackupSenderClass<em3phManagerData_t>& sdBackupDataSender, int slot){ 
    em3phBackupSenderPool[slot] = &sdBackupDataSender;
}

void SDBackupSenderCollectionClass::setBackupSender(SDBackupSenderClass<flowMeterManagerData_t>& sdBackupDataSender, int slot){
    flowMeterBackupSenderPool[slot] = &sdBackupDataSender;
}



SDBackupSenderCollectionClass SDBackupSenderCollection;
