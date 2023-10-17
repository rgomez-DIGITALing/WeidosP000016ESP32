#pragma once



#include "../EnergyMeters/energyMeters.h"
#include "EMMDataDefinitions.h"





class EA750Manager{
  public:
    EA750Manager(EA750& ea750, int deviceId, uint8_t maxTries) : ea750(ea750), deviceId(deviceId), maxTries(maxTries){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    bool sendProperties();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; }
    EA750* getEnergyMeter(){ return &ea750; }

  private:
    EA750& ea750;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
