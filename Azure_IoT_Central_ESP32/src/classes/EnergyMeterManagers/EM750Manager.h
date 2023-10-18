#pragma once

#include "../EnergyMeters/energyMeters.h"
#include "EMMDataDefinitions.h"


class EM750Manager{
  public:
    EM750Manager(EM750& em750, int deviceId, uint8_t maxTries) : em750(em750), deviceId(deviceId), maxTries(maxTries){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    bool sendProperties();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; }
    EM750* getEnergyMeter(){ return &em750; }

  private:
    EM750& em750;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
