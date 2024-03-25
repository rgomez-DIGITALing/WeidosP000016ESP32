#include "DataHubCollection.h"



void DataHubCollectionClass::init(){
    weidosDataHub = nullptr;
    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        em1phDataHubPool[i] = nullptr;
        em3phDataHubPool[i] = nullptr;
        flowMeterDataHubPool[i] = nullptr;
        
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

void DataHubCollectionClass::push(flowMeterManagerData_t data, int slot){
    if(flowMeterDataHubPool[slot]) flowMeterDataHubPool[slot]->push(data);
}

void DataHubCollectionClass::loop(){

    if(weidosDataHub) weidosDataHub->loop();

    for(int i=0; i<MAX_DATA_HUBS_ALLOWED; i++){
        if(em1phDataHubPool[i]) em1phDataHubPool[i]->loop();
        if(em3phDataHubPool[i]) em3phDataHubPool[i]->loop();
        if(flowMeterDataHubPool[i]) flowMeterDataHubPool[i]->loop();
    }
}



void DataHubCollectionClass::setDataHub(DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>* dataHub){ 
    weidosDataHub = dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<em1phManagerData_t, RING_BUFFER_SIZE>* dataHub, int slot){ 
    em1phDataHubPool[slot] = dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub, int slot){ 
    em3phDataHubPool[slot] = dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE>* dataHub, int slot){ 
    flowMeterDataHubPool[slot] = dataHub;
}




void DataHubCollectionClass::setDataHub(DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>& dataHub){ 
    weidosDataHub = &dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<em1phManagerData_t, RING_BUFFER_SIZE>& dataHub, int slot){ 
    em1phDataHubPool[slot] = &dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<em3phManagerData_t, RING_BUFFER_SIZE>& dataHub, int slot){ 
    em3phDataHubPool[slot] = &dataHub;
}

void DataHubCollectionClass::setDataHub(DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE>& dataHub, int slot){ 
    flowMeterDataHubPool[slot] = &dataHub;
}

void DataHubCollectionClass::setPayloadGenerator2(uint8_t slot, payloadGenerator3ph generatePayload){
    if(em3phDataHubPool[slot]) em3phDataHubPool[slot]->setPayloadGenerator2(generatePayload);
}

DataHubCollectionClass DataHubCollection;
