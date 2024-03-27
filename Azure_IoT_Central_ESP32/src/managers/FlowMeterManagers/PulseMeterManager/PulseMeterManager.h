#pragma once

#include "../../../devices/FlowMeters/PulseMeter/PulseMeter.h"
#include "../PulseMeterDataDefinitions.h"

class PulseMeterManager{
    public:
        PulseMeterManager(int deviceId, int interruptPin, float convertionFactor = 1.0f);
        ~PulseMeterManager();
        void init(){ pulseMeter->init(); }
        void begin(){ pulseMeter->begin(); }
        int getDeviceId(){ return deviceId; }
        void triggerUpdate();
        FlowMeterUpdateState_t loop();
        bool sendProperties(){ return true; }
        void setDeviceId(int id){ deviceId = id; }
        int getDeviceId() const { return deviceId; }
        //EA750* getEnergyMeter(){ return &ea750; }

    private:
        PulseMeter* pulseMeter;
        int deviceId;
        FlowMeterUpdateState_t state = FLOW_METER_BEGIN;

};
