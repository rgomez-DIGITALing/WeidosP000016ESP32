#include "DataHubCollection.h"



void DataHubCollectionClass::init(){
    weidosDataHub = nullptr;
    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        em1phDataHubPool[i] = nullptr;
        em3phDataHubPool[i] = nullptr;
    }
}


void DataHubCollectionClass::push(WeidosManagerData_t data){
    if(weidosDataHub) weidosDataHub->push(data);
}

void DataHubCollectionClass::push(em1phManagerData_t data, int slot){
    if(em1phDataHubPool[slot]) em1phDataHubPool[slot]->push(data);
}

void DataHubCollectionClass::push(em3phManagerData_t data, int slot){
    if(em3phDataHubPool[slot]) em3phDataHubPool[slot]->push(data);
}

void DataHubCollectionClass::loop(){
    weidosDataHub->loop();
    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        if(em1phDataHubPool[i]){
            // Serial.print("Looping for em1phDataHUB: ");
            // Serial.println(i);
            em1phDataHubPool[i]->loop();
        } 
        if(em3phDataHubPool[i]) em3phDataHubPool[i]->loop();
    }
}


void DataHubCollectionClass::setDataHub(DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE>& dataHub){ 
    weidosDataHub = &dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>& dataHub, int slot){ 
    em1phDataHubPool[slot] = &dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>& dataHub, int slot){ 
    em3phDataHubPool[slot] = &dataHub;
}



DataHubCollectionClass DataHubCollection;
