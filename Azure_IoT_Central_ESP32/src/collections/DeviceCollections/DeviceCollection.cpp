#include "DeviceCollection.h"



void DeviceCollectionClass::init(){
    weidosManager = nullptr;
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        EM110Pool[i] = nullptr;
        EM111Pool[i] = nullptr;
        EM120Pool[i] = nullptr;
        EM122Pool[i] = nullptr;
        EM220Pool[i] = nullptr;
        EM750Pool[i] = nullptr;
        EA750Pool[i] = nullptr;
        PulseMeterPool[i] = nullptr;
        AnalogMeterPool[i] = nullptr;
    }

    return;
}


void DeviceCollectionClass::loopDevices(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(EM750Pool[i]){
            if(EM750Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EA750Pool[i]){
            if(EA750Pool[i]->loop() != ENERGY_METER_IDLE) return;
        }
    }

    return;
}


void DeviceCollectionClass::loopDevicesNoNetwork(){
    if(weidosManager) weidosManager->loop();

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

        if(PulseMeterPool[i]) PulseMeterPool[i]->loop();
        if(AnalogMeterPool[i]) AnalogMeterPool[i]->loop();
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
        if(PulseMeterPool[i]) PulseMeterPool[i]->triggerUpdate();
        if(AnalogMeterPool[i]) AnalogMeterPool[i]->triggerUpdate();
    }

    return;
}


void DeviceCollectionClass::triggerUpdateTCP(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(EM750Pool[i]) EM750Pool[i]->triggerUpdate();
        if(EA750Pool[i]) EA750Pool[i]->triggerUpdate();
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
        if(EA750Pool[i]) EA750Pool[i]->sendProperties();
        if(PulseMeterPool[i]) PulseMeterPool[i]->sendProperties();
        if(AnalogMeterPool[i]) AnalogMeterPool[i]->sendProperties();
    }

    return;
}


void DeviceCollectionClass::initFlowMeters(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        
        if(PulseMeterPool[i]) PulseMeterPool[i]->init();
        //if(AnalogMeterPool[i]) AnalogMeterPool[i]->init();
    }

    return;
}


void DeviceCollectionClass::setDevice(WeidosManager& weidos){ 
    weidosManager = &weidos;
}

void DeviceCollectionClass::setDevice(EM110Manager& em){ 
    int slot = em.getDeviceId();
    EM110Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(EM111Manager& em){
    int slot = em.getDeviceId();
    EM111Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(EM120Manager& em){
    int slot = em.getDeviceId();
    EM120Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(EM122Manager& em){
    int slot = em.getDeviceId();
    EM122Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(EM220Manager& em){
    int slot = em.getDeviceId();
    EM220Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(EM750Manager& em){
    int slot = em.getDeviceId();
    EM750Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(EA750Manager& em){
    int slot = em.getDeviceId();
    EA750Pool[slot] = &em;
}


void DeviceCollectionClass::setDevice(PulseMeterManager& pulseMeter){
    int slot = pulseMeter.getDeviceId();
    PulseMeterPool[slot] = &pulseMeter;
}


void DeviceCollectionClass::setDevice(AnalogMeterManager& analogMeter){
    int slot = analogMeter.getDeviceId();
    AnalogMeterPool[slot] = &analogMeter;
}



DeviceCollectionClass DeviceCollection;
