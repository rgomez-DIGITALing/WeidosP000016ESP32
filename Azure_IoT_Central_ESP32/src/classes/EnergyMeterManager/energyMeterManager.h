#pragma once


//#include "../EM750.h"
//#include "EM750.h"
#include "../EM750/EM750.h"
//#include "DataHub.h"



typedef struct energyMeterManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  em750Data_t data;
} energyMeterManagerData_t;



enum EnergyMeterUpdateState{
  ENERGY_METER_IDLE,
  UPDATE_ENERGY_METER,
  ENERGY_METER_UPDATED,
  ENERGY_METER_UPDATE_FAILED,
  PASS_MESSAGE,
  END_TASK
};



class EnergyMeterManager{
  public:
    EnergyMeterManager(EM750& em750, int deviceId, uint8_t maxTries) : em750(em750), deviceId(deviceId), maxTries(maxTries){};
    //EnergyMeterManager(EM750& em750, DataHub&<energyMeterManagerData_t> dataHub, int deviceId, uint8_t maxTries) : em750(em750), dataBuffer(dataHub), deviceId(deviceId), maxTries(maxTries){};
    void triggerUpdate(){ state = UPDATE_ENERGY_METER; }
    EnergyMeterUpdateState loop();
    bool sendProperties();
    void setDeviceId(int id){ deviceId = id; }
    int getDeviceId(){ return deviceId; }
    EM750* getEnergyMeter(){ return &em750; }

  private:
    EM750& em750;
    EnergyMeterUpdateState state = ENERGY_METER_IDLE;
    //DataHub&<energyMeterManagerData_t> dataBuffer;
    uint8_t maxTries;
    uint8_t numTries = 0;
    int deviceId;
    bool propertiesSent = false;
};


#ifdef USING_MODULAS_TRANSELEVADORES
extern EnergyMeterManager modula4;
extern EnergyMeterManager modula11;
extern EnergyMeterManager transelevador1;
extern EnergyMeterManager transelevador2;
extern EnergyMeterManager transelevador3;
#endif


//Weidos 2
#ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
extern EnergyMeterManager general;
extern EnergyMeterManager robot;
extern EnergyMeterManager aireCondicionado;
extern EnergyMeterManager aireComprimido;
extern EnergyMeterManager lineaEmpaquetado;
#endif

#ifdef BATCH_IT
extern EnergyMeterManager compresorIT1;
extern EnergyMeterManager compresorIT2;
#endif
