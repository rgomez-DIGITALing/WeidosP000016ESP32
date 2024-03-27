#pragma once

static const uint32_t digitalPins[] = {0, DI_4, DI_5, DI_6, DI_7};
static const uint32_t analogPins[] = {0, ADI_0, ADI_1, ADI_2, ADI_3};

typedef enum flowMeterError_enum_t{
    FM_NO_ERROR,
    FM_DEVIDE_BY_ZERO_ERROR,
    FM_VOLTAGE_ERROR
} flowMeterError_t;

typedef enum flowMeterInitError_enum_t{
    FM_SD_BEGIN_ERROR,
    FM_SD_FILE_EXISTS_ERROR,
    FM_SD_FILE_OPEN_ERROR
} flowMeterInitError_t;

typedef struct  flowMeterData_struct_t{
    flowMeterError_t error;
    float averageFlow;
    unsigned long t0;
    unsigned long tf;
    float totalConsumption;
    float periodConsumption;
} flowMeterData_t;
