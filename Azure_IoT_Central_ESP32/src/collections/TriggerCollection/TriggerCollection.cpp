#include "TriggerCollection.h"




void TriggerCollectionClass::init(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        triggers[i] = nullptr;
    }

    return;
}


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



TriggerCollectionClass TriggerCollection;
