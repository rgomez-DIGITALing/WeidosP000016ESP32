#pragma once

#include "../../../devices/EnergyMeters/energyMeters.h"
#include "../EMMDataDefinitions.h"
#include "../../../globalDefinitions/globalConfiguration.h"


class EM3PHManager_BaseClass{
  public:
    EM3PHManager_BaseClass(uint8_t deviceId);
    EM3PHManager_BaseClass(uint8_t deviceId, int ctPrimary, int ctSecondary);
    
    virtual ~EM3PHManager_BaseClass(){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState_t loop();

    void setDeviceId(uint8_t id){ deviceId = id; }
    uint8_t getDeviceId() const { return deviceId; }
    EM3PH_BaseClass* getEnergyMeter(){ return em3ph; }

    virtual bool sendProperties() = 0;

    void setIdentifier(char* identifier){ this->identifier = identifier; }
    void setAsset(char* asset){ this->asset = asset; }
    void setLocation1(char* location1){ this->location1 = location1; }
    void setLocation2(char* location2){ this->location2 = location2; }

    char* getIdentifier(){ return identifier; }
    char* getAsset(){ return asset; };
    char* getLocation1(){ return location1; }
    char* getLocation2(){ return location2; }

    uint8_t getModbusId(){ return em3ph->getModbusId(); }
    int getCTPrimary(){ return ctPrimary; }
    int getCTSecondary(){ return ctSecondary; }

  protected:
    EM3PH_BaseClass* em3ph = nullptr;
    int ctPrimary = 0;
    int ctSecondary = 0;

    EnergyMeterUpdateState_t state = ENERGY_METER_IDLE;
    uint8_t maxTries = DEFAULT_MODBUS_NUMBER_TRIES;
    uint8_t numTries = 0;
    uint8_t deviceId = 0;
    bool propertiesSent = false;

    char* identifier = nullptr;
    char* asset = nullptr;
    char* location1 = nullptr;
    char* location2 = nullptr;
};
