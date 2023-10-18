#pragma once
#include "../../devices/EnergyMeters/energyMeters.h"


typedef struct em1phManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  em1phData_t payload;
} em1phManagerData_t;


typedef struct em3phManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  em3phData_t payload;
} em3phManagerData_t;


typedef enum EnergyMeterUpdateState_enum_t{
  ENERGY_METER_IDLE,
  UPDATE_ENERGY_METER,
  ENERGY_METER_UPDATED,
  ENERGY_METER_UPDATE_FAILED,
  PASS_MESSAGE,
  END_TASK
} EnergyMeterUpdateState_t;


