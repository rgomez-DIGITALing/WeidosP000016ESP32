#pragma once

#include "../../devices/FlowMeters/PulseMeter/PulseMeter.h"
#include "PulseMeterDataDefinitions.h"

class PulseMeterManager{
    public:
        PulseMeterManager(int deviceId, int interruptPin, float convertionFactor = 2.0f);
        ~PulseMeterManager();
        void begin(){ pulseMeter->begin(); }
        int getDeviceId(){ return deviceId; }
        void triggerUpdate(){ state = UPDATE_PULSE_METER; }
        PulseMeterUpdateState_t loop();
        bool sendProperties(){ return true; }
        void setDeviceId(int id){ deviceId = id; }
        int getDeviceId() const { return deviceId; }
        //EA750* getEnergyMeter(){ return &ea750; }

    private:
        PulseMeter* pulseMeter;
        int deviceId;
        PulseMeterUpdateState_t state = PULSE_METER_IDLE;

};
