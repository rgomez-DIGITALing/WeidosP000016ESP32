#pragma once


#include "../../../devices/EnergyMeters/energyMeters.h"
#include "../EMMDataDefinitions.h"




#define DEFAULT_MAX_TRIES 5

class EM110Manager{
  public:
    EM110Manager(int deviceId, int ctPrimary, int ctSecondary, uint8_t maxTries = DEFAULT_MAX_TRIES);
    ~EM110Manager();
    //EnergyMeterManager(EM750& em750, DataHub&<EM111ManagerData_t> dataHub, int deviceId, uint8_t maxTries) : em750(em750), dataBuffer(dataHub), deviceId(deviceId), maxTries(maxTries){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId() const { return deviceId; }
    bool sendProperties();
    EM110* getEnergyMeter(){ return em110; }

  private:
    EM110* em110;
    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    //DataHub*<EM111ManagerData_t> dataBuffer;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};
