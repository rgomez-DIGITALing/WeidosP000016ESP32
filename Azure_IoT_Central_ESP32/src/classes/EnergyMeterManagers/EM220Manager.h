#pragma once


#include "../EnergyMeters/energyMeters.h"
#include "EMMDataDefinitions.h"


#define DEFAULT_MAX_TRIES 5

class EM220Manager{
  public:
    EM220Manager(int deviceId, int ctPrimary, int ctSecondary, uint8_t maxTries = DEFAULT_MAX_TRIES);
    ~EM220Manager();
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; } 
    bool sendProperties();
    EM220* getEnergyMeter(){ return em220; }

  private:
    EM220* em220;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
