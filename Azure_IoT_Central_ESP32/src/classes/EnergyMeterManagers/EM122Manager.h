#pragma once


#include "../EnergyMeters/energyMeters.h"
#include "EMMDataDefinitions.h"



#define DEFAULT_MAX_TRIES 5

class EM122Manager{
  public:
    EM122Manager(int deviceId, uint8_t maxTries = DEFAULT_MAX_TRIES);
    ~EM122Manager();
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; }
    bool sendProperties();
    EM122* getEnergyMeter(){ return em122; }

  private:
    EM122* em122;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
