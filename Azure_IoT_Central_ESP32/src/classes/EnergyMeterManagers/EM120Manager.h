#pragma once


#include "../EnergyMeters/energyMeters.h"
#include "EMMDataDefinitions.h"



#define DEFAULT_MAX_TRIES 5

class EM120Manager{
  public:
    EM120Manager(int deviceId, int ctPrimary, int ctSecondary, uint8_t maxTries = DEFAULT_MAX_TRIES);
    ~EM120Manager();
    //EnergyMeterManager(EM750& em750, DataHub&<energyMeterManagerData_t> dataHub, int deviceId, uint8_t maxTries) : em750(em750), dataBuffer(dataHub), deviceId(deviceId), maxTries(maxTries){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; }
    bool sendProperties();
    EM120* getEnergyMeter(){ return em120; }

  private:
    EM120* em120;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
