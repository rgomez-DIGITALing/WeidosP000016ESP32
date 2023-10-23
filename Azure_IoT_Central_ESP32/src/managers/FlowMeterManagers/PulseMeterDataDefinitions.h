#pragma once
#include "../../devices/FlowMeters/PulseMeter/PulseMeter.h"

typedef enum PulseMeterUpdateState_enum_t{
  PULSE_METER_IDLE,
  UPDATE_PULSE_METER
} PulseMeterUpdateState_t;


typedef struct flowMeterManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  flowMeterData_t payload;
} flowMeterManagerData_t;
