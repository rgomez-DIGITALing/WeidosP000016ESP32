#include "DeviceCollection.h"




DeviceCollectionClass::DeviceCollectionClass(){
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


void DeviceCollectionClass::init(){
    // PersistentDataModule.getDeviceConfiguration(deviceList, MAX_ALLOWED_DEVICES);
    // createDeviceObjects();
    return;
}



// void DeviceCollectionClass::setDevice(String& deviceType, uint8_t slot){
//     //DeviceType deviceType;
//     int deviceTypeId = NONE_DEVICE_TYPE;

//     if(deviceType.equals("EM110")) deviceTypeId = EM110_DEVICE_TYPE;
//     if(deviceType.equals("EM111")) deviceTypeId = EM111_DEVICE_TYPE;
//     if(deviceType.equals("EM120")) deviceTypeId = EM120_DEVICE_TYPE;
//     if(deviceType.equals("EM122")) deviceTypeId = EM122_DEVICE_TYPE;
//     if(deviceType.equals("EM220")) deviceTypeId = EM220_DEVICE_TYPE;
//     if(deviceType.equals("FlowMeter")) deviceTypeId = FLOW_METER_DEVICE_TYPE;
//     if(deviceType.equals("PulseMeter")) deviceTypeId = PULSE_METER_DEVICE_TYPE;

//     deviceList[slot] = deviceTypeId;
//     PersistentDataModule.saveDeviceConfiguration(deviceTypeId, slot);
// }



// String DeviceCollectionClass::getEnergyMeterName(uint8_t slot){
//     if(deviceList[slot] == EM110_DEVICE_TYPE) return String("EM110");
//     if(deviceList[slot] == EM111_DEVICE_TYPE) return String("EM111");
//     if(deviceList[slot] == EM120_DEVICE_TYPE) return String("EM120");
//     if(deviceList[slot] == EM122_DEVICE_TYPE) return String("EM122");
//     if(deviceList[slot] == EM220_DEVICE_TYPE) return String("EM220");
//     return String("None");
// }






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


bool DeviceCollectionClass::triggerUpdate(uint8_t slot){
    if(slot == 0) {
        if(weidosManager) weidosManager->triggerUpdate();
        return true;
    }

    if(EA750Pool[slot]){
        EA750Pool[slot]->triggerUpdate();
        return true;
    }

    if(EM750Pool[slot]){
        EM750Pool[slot]->triggerUpdate();
        return true;
    }

    if(EM110Pool[slot]){
        EM110Pool[slot]->triggerUpdate();
        return true;
    }
    if(EM111Pool[slot]){
            EM111Pool[slot]->triggerUpdate();
        return true;
    }
    if(EM120Pool[slot]){
        EM120Pool[slot]->triggerUpdate();
        return true;
    }
    if(EM122Pool[slot]){
        EM122Pool[slot]->triggerUpdate();
        return true;
    }
    if(EM220Pool[slot]){
        EM220Pool[slot]->triggerUpdate();
        return true;
    }
    if(PulseMeterPool[slot]){
        PulseMeterPool[slot]->triggerUpdate();
        return true;
    }
    if(AnalogMeterPool[slot]){
        AnalogMeterPool[slot]->triggerUpdate();
        return true;
    }

    return false;
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







// void DeviceCollectionClass::createDeviceObjects(){
//     for(int i = 0; i<MAX_ALLOWED_DEVICES; i++){
//         createObject(deviceList[i], i);
//     }
// }

// void DeviceCollectionClass::createObject(int deviceType, int slot){
//     int ctPrimary;
//     int ctSecondary;
//     PersistentDataModule.getConversionFactor(ctPrimary, slot, true);
//     PersistentDataModule.getConversionFactor(ctSecondary, slot, false);
    

//     if(deviceType == NONE_DEVICE_TYPE) return;
//     if(deviceType == EM110_DEVICE_TYPE) EM110Pool[slot] = new EM110Manager(slot, ctPrimary, ctSecondary);
//     if(deviceType == EM111_DEVICE_TYPE) EM111Pool[slot] = new EM111Manager(slot);
//     if(deviceType == EM120_DEVICE_TYPE) EM120Pool[slot] = new EM120Manager(slot, ctPrimary, ctSecondary);
//     if(deviceType == EM122_DEVICE_TYPE) EM122Pool[slot] = new EM122Manager(slot);
//     if(deviceType == EM220_DEVICE_TYPE) EM220Pool[slot] = new EM220Manager(slot, ctPrimary, ctSecondary);
    
//     AzureDeviceCollection.createAzureDevice(slot);

//     return;
// }



DeviceCollectionClass DeviceCollection;
