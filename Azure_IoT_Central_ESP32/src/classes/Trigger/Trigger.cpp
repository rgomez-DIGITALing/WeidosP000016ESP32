#include "Trigger.h"

static const unsigned long MAX_DURATION = 60*60*1000;    //Maximum boost duration set to 5 minutes.
static const unsigned long MIN_FREQUENCY = 5000; //Minimum frequency is set to 5s.



TriggerClass::TriggerClass(uint8_t slot) : slot(slot){

}


bool TriggerClass::boost(unsigned long frequency, unsigned long duration){
    Serial.print("[boost] frequency: ");
    Serial.print(frequency);
    Serial.print("   -   duration: ");
    Serial.print(duration);
    t0boost = millis();
    boostDuration = duration;
    this->frequency = frequency;
    if(frequency < MIN_FREQUENCY){
        this->frequency = MIN_FREQUENCY;
    } 
    Serial.print("MAX_DURATION: ");
    Serial.println(MAX_DURATION);
    if(duration > MAX_DURATION){
        Serial.println("Duration exceeds the limit lol");
        boostDuration = MAX_DURATION;
    } 
    boosting = true;
    return true;
}


void TriggerClass::loop(){

    if(boosting){
        // Serial.println("Boosting!");
        if(millis()-t0boost > boostDuration){
            Serial.print("End of boosting after: ");
            Serial.print(millis()-t0boost);
            Serial.println(" ms");
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
