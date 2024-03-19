#include "DeviceCollection.h"
#include "../../classes/PersistentData/PersistentDataClass.h"



DeviceCollectionClass::DeviceCollectionClass(){
    weidosManager = nullptr;
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        EM1PHPool[i] = nullptr;
        EM3PHPool[i] = nullptr;
        PulseMeterPool[i] = nullptr;
        AnalogMeterPool[i] = nullptr;
    }

    return;
}


void DeviceCollectionClass::init(){
    PersistentDataModule.getDeviceConfiguration(deviceList, MAX_ALLOWED_DEVICES);
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

uint8_t testList[] = {0,7,8,4,5,2};

int DeviceCollectionClass::getDeviceType(uint8_t slot){ 
    if(slot>MAX_ALLOWED_DEVICES) return 0;

    return deviceList[slot];
    // return testList[slot];
}

char* DeviceCollectionClass::getDeviceName(uint8_t slot){
    int deviceType = deviceList[slot];
    // int deviceType = testList[slot];
    char* deviceTypeName = nullptr;

    if(deviceType == 1) return "EM110";
    if(deviceType == 2) return "EM111";
    if(deviceType == 3) return "EM120";
    if(deviceType == 4) return "EM122";
    if(deviceType == 5) return "EM220";
    if(deviceType == 6) return "EM750";
    if(deviceType == 7) return "EA750";
    if(deviceType == 8) return "Pulse Meter";
    if(deviceType == 9) return "Analog Meter";
    return "None";
}

bool DeviceCollectionClass::isEnergyMeter(uint8_t slot){
    int deviceType = deviceList[slot];
    // if(deviceType<)

}


void DeviceCollectionClass::loopDevices(){
    // for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
    //     if(EM750Pool[i]){
    //         if(EM750Pool[i]->loop() != ENERGY_METER_IDLE) return;
    //     }

    //     if(EA750Pool[i]){
    //         if(EA750Pool[i]->loop() != ENERGY_METER_IDLE) return;
    //     }
    // }

    return;
}


void DeviceCollectionClass::loopDevicesNoNetwork(){
    if(weidosManager) weidosManager->loop();

    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        

        if(EM1PHPool[i]){
            if(EM1PHPool[i]->loop() != ENERGY_METER_IDLE) return;
        }

        if(EM3PHPool[i]){
            if(EM3PHPool[i]->loop() != ENERGY_METER_IDLE) return;
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

    if(EM1PHPool[slot]){
        Serial.println("Let's trigger EM1PH");
        EM1PHPool[slot]->triggerUpdate();
        return true;
    }

    if(EM3PHPool[slot]){
        Serial.println("Let's trigger EM3PH");
        EM3PHPool[slot]->triggerUpdate();
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
        if(EM1PHPool[i]) EM1PHPool[i]->sendProperties();
        if(EM3PHPool[i]) EM3PHPool[i]->sendProperties();
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


void DeviceCollectionClass::setDevice(EM110Manager* em){ 
    int slot = em->getDeviceId();
    EM1PHPool[slot] = em;
}


void DeviceCollectionClass::setDevice(EM111Manager* em){
    int slot = em->getDeviceId();
    EM1PHPool[slot] = em;
}


void DeviceCollectionClass::setDevice(EM120Manager* em){
    int slot = em->getDeviceId();
    EM3PHPool[slot] = em;
}


void DeviceCollectionClass::setDevice(EM122Manager* em){
    int slot = em->getDeviceId();
    EM3PHPool[slot] = em;
}


void DeviceCollectionClass::setDevice(EM220Manager* em){
    int slot = em->getDeviceId();
    EM3PHPool[slot] = em;
}


void DeviceCollectionClass::setDevice(EM750Manager* em){
    int slot = em->getDeviceId();
    EM3PHPool[slot] = em;
}


void DeviceCollectionClass::setDevice(EA750Manager* em){
    int slot = em->getDeviceId();
    EM3PHPool[slot] = em;
}






// void DeviceCollectionClass::setDevice(EM110Manager& em){ 
//     int slot = em.getDeviceId();
//     EM110Pool[slot] = &em;
// }


// void DeviceCollectionClass::setDevice(EM111Manager& em){
//     int slot = em.getDeviceId();
//     EM111Pool[slot] = &em;
// }


// void DeviceCollectionClass::setDevice(EM120Manager& em){
//     int slot = em.getDeviceId();
//     EM120Pool[slot] = &em;
// }


// void DeviceCollectionClass::setDevice(EM122Manager& em){
//     int slot = em.getDeviceId();
//     EM122Pool[slot] = &em;
// }


// void DeviceCollectionClass::setDevice(EM220Manager& em){
//     int slot = em.getDeviceId();
//     EM220Pool[slot] = &em;
// }


// void DeviceCollectionClass::setDevice(EM750Manager& em){
//     int slot = em.getDeviceId();
//     EM750Pool[slot] = &em;
// }


// void DeviceCollectionClass::setDevice(EA750Manager& em){
//     int slot = em.getDeviceId();
//     EA750Pool[slot] = &em;
// }


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
