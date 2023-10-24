#pragma once



typedef enum flowMeterError_enum_t{
    FM_NO_ERROR,
    FM_DEVIDE_BY_ZERO_ERROR,
    FM_VOLTAGE_ERROR
} flowMeterError_t;



typedef struct  flowMeterData_struct_t{
    flowMeterError_t error;
    float averageFlow;
    unsigned long t0;
    unsigned long tf;
    float totalConsumption;
    float periodConsumption;
} flowMeterData_t;
