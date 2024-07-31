#include "TriggerCollection.h"
#include "../DeviceCollections/DeviceCollection.h"




void TriggerCollectionClass::init(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        triggers[i] = nullptr;
    }

    return;
}

// void TriggerCollectionClass::configure(){
//     for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
//         uint8_t deviceType = DeviceCollection.getDeviceType(i);
//         Serial.print("Trigger collection: ");
//         Serial.println(deviceType);
//         if(deviceType < 1 ||  deviceType > MAX_DEVICE_TYPE) continue;
//         triggers[i] = new TriggerClass(i);
//         Serial.print("Trigger created for ID: ");
//         Serial.println(i);
//         if(deviceType == EM750_DEVICE_TYPE || deviceType == EA750_DEVICE_TYPE) triggers[i]->setAsConnectionDependent();
//     }
// }


void TriggerCollectionClass::loop(bool connectionUp){
    //Serial.print("o");
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        if(!triggers[i]){
            // Serial.print("It doesn't exists pues: ");
            // Serial.println(i);
            continue;                  //Trigger not set in collection (Skip)
        } 
        // Serial.print("o");
        if(!triggers[i]->isConnectionDependent()){   //Case for NONE connection dependent triggers
            triggers[i]->loop();
            continue;
        }

        if(connectionUp) triggers[i]->loop();    //Case for connection dependent triggers
    }
}

void TriggerCollectionClass::setTrigger(TriggerClass& trigger){
    uint8_t slot = trigger.getSlot();
    Serial.print("Setting trigger in slot: ");
    Serial.println(slot);
    triggers[slot] = &trigger;
    return;
}


void TriggerCollectionClass::setTrigger(TriggerClass* trigger){
    uint8_t slot = trigger->getSlot();
    Serial.print("Setting trigger in slot: ");
    Serial.println(slot);
    triggers[slot] = trigger;
    return;
}



TriggerCollectionClass TriggerCollection;
