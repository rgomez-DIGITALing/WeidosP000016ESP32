#pragma once

#include "../../collections/DeviceCollections/DeviceCollection.h"



static const unsigned long DEFAULT_FREQUENCY = 60000;
//static const unsigned long DEFAULT_FREQUENCY = 10000;   //Test Rocio
static const unsigned long DEFAULT_BOOST_DURATION = 60000;


class TriggerClass{
    public:
        TriggerClass(uint8_t slot);
        void loop();
        bool boost(unsigned long frequency, unsigned long duration = DEFAULT_BOOST_DURATION);
        bool isConnectionDependent(){ return connectionDependent; }
        uint8_t getSlot(){ return slot; }
    private:
        bool connectionDependent = false;
        //bool connectionDependent = true;  //Test Rocio
        uint8_t slot = 0;
        unsigned long defaultFrequency = DEFAULT_FREQUENCY;
        unsigned long prevTime = 0;
        bool boosting = false;
        
        unsigned long frequency = DEFAULT_FREQUENCY;
        unsigned long boostFrequency = DEFAULT_FREQUENCY;
        unsigned long t0boost = 0;
        unsigned long boostDuration = DEFAULT_BOOST_DURATION;
};
