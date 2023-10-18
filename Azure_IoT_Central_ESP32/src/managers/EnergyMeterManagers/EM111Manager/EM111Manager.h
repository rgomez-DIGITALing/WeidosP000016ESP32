#pragma once


#include "../../../devices/EnergyMeters/energyMeters.h"
#include "../EMMDataDefinitions.h"



#define DEFAULT_MAX_TRIES 5

class EM111Manager{
  public:
    EM111Manager(int deviceId, uint8_t maxTries = DEFAULT_MAX_TRIES);
    ~EM111Manager();
    //EnergyMeterManager(EM750& em750, DataHub&<EM111ManagerData_t> dataHub, int deviceId, uint8_t maxTries) : em750(em750), dataBuffer(dataHub), deviceId(deviceId), maxTries(maxTries){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; }
    bool sendProperties();
    EM111* getEnergyMeter(){ return em111; }

  private:
    EM111* em111;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
