#include "DeviceCollection.h"



void DeviceCollectionClass::init(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        EM750Pool[i] = nullptr;
        EM110Pool[i] = nullptr;
        EM111Pool[i] = nullptr;
        EM120Pool[i] = nullptr;
        EM122Pool[i] = nullptr;
        EM220Pool[i] = nullptr;
    }

    return;
}


void DeviceCollectionClass::loopDevices(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(EM110Pool[i]){
            if(EM110Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EM111Pool[i]){
            if(EM111Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EM120Pool[i]){
            if(EM120Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EM122Pool[i]){
            if(EM122Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EM220Pool[i]){
            if(EM220Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EM750Pool[i]){
            if(EM750Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }
    }

    return;
}


void DeviceCollectionClass::triggerUpdateRTU(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(EM110Pool[i]) EM110Pool[i]->triggerUpdate();
        if(EM111Pool[i]) EM111Pool[i]->triggerUpdate();
        if(EM120Pool[i]) EM120Pool[i]->triggerUpdate();
        if(EM122Pool[i]) EM122Pool[i]->triggerUpdate();
        if(EM220Pool[i]) EM220Pool[i]->triggerUpdate();
    }

    return;
}


void DeviceCollectionClass::triggerUpdateTCP(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(EM750Pool[i]) EM750Pool[i]->triggerUpdate();
    }

    return;
}


void DeviceCollectionClass::sendDevicesProperties(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(EM110Pool[i]) EM110Pool[i]->sendProperties();
        if(EM111Pool[i]) EM111Pool[i]->sendProperties();
        if(EM120Pool[i]) EM120Pool[i]->sendProperties();
        if(EM122Pool[i]) EM122Pool[i]->sendProperties();
        if(EM220Pool[i]) EM220Pool[i]->sendProperties();
        if(EM750Pool[i]) EM750Pool[i]->sendProperties();
    }

    return;
}



DeviceCollectionClass DeviceCollection;
