#include "Trigger.h"

static const unsigned long MAX_DURATION = 5*60*1000;    //Maximum boost duration set to 5 minutes.
static const unsigned long MIN_FREQUENCY = 5000; //Minimum frequency is set to 5s.



TriggerClass::TriggerClass(uint8_t slot) : slot(slot){

}


bool TriggerClass::boost(unsigned long frequency, unsigned long duration){
    t0boost = millis();
    boostDuration = duration;
    this->frequency = frequency;
    if(frequency < MIN_FREQUENCY){
        this->frequency = MIN_FREQUENCY;
    } 
    if(duration > MAX_DURATION){
        boostDuration = MAX_DURATION;
    } 
    boosting = true;
    return true;
}


void TriggerClass::loop(){

    if(boosting){
        if(millis()-t0boost > boostDuration){
            boosting = false;
            frequency = defaultFrequency;
        }
    }

    if(millis()-prevTime > frequency){
        Serial.println("Let's trigger update!");
        DeviceCollection.triggerUpdate(slot);
        prevTime = millis();
    }
    return;
}
