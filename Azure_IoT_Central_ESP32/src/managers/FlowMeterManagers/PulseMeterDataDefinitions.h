#pragma once
#include "../../devices/FlowMeters/PulseMeter/PulseMeter.h"

typedef enum FlowMeterUpdateState_enum_t{
  FLOW_METER_BEGIN,
  FLOW_METER_IDLE,
  UPDATE_FLOW_METER
} FlowMeterUpdateState_t;


typedef struct flowMeterManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  int dataSourceStatus;
  flowMeterData_t payload;
} flowMeterManagerData_t;
