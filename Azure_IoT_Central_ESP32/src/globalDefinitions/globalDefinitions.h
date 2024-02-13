#pragma once
#include <Arduino.h>

enum DeviceType{
    NONE_DEVICE_TYPE,
    EM110_DEVICE_TYPE,
    EM111_DEVICE_TYPE,
    EM120_DEVICE_TYPE,
    EM122_DEVICE_TYPE,
    EM220_DEVICE_TYPE,
    EM750_DEVICE_TYPE,
    EA750_DEVICE_TYPE,
    FLOW_METER_DEVICE_TYPE,
    PULSE_METER_DEVICE_TYPE
};

extern uint8_t MAX_DEVICE_TYPE;
extern uint8_t AZURE_ID_MAX_LENGTH;
extern uint8_t AZURE_SAS_KEY_MAX_LENGTH;
