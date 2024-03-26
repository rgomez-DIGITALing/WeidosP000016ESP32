#pragma once

#include "../../../devices/FlowMeters/AnalogMeter/AnalogMeter.h"
#include "../PulseMeterDataDefinitions.h"

class AnalogMeterManager{
    public:
        AnalogMeterManager(int deviceId, int interruptPin, float convertionFactor = 2.0f);
        ~AnalogMeterManager();
        void init(){ analogMeter->init(); }
        void begin(){ analogMeter->begin(); }
        int getDeviceId(){ return deviceId; }
        void triggerUpdate();
        FlowMeterUpdateState_t loop();
        bool sendProperties(){ return true; }
        void setDeviceId(int id){ deviceId = id; }
        int getDeviceId() const { return deviceId; }

    private:
        AnalogMeter* analogMeter;
        int deviceId;
        FlowMeterUpdateState_t state = FLOW_METER_BEGIN;

};
