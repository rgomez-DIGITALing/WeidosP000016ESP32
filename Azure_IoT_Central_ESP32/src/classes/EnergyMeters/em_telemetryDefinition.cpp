#include "em_telemetryDefinition.h"
#include <Arduino.h>



enum invalidDataErrors{
    VALID_DATA,
    NaN_VALUE
};


int isEMDataValid(float data){
    if(isnan(data)) return NaN_VALUE;
    return VALID_DATA;
}

char* EM1PH_DATA_TELEMETRY_NAMES[]{
    TELEMETRY_PROP_NAME_VOLTAGE_L1N,
    TELEMETRY_PROP_NAME_CURRENT_L1,
    TELEMETRY_PROP_NAME_REAL_POWER_TOTAL,
    TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL,
    TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL,
    TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL,
    TELEMETRY_PROP_NAME_FREQUENCY,
    TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL,
    TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL,
    TELEMETRY_PROP_NAME_ROT_FIELD,
    TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL
};


char* EM3PH_DATA_TELEMETRY_NAMES[] = {
    TELEMETRY_PROP_NAME_VOLTAGE_L1N,
    TELEMETRY_PROP_NAME_VOLTAGE_L2N,
    TELEMETRY_PROP_NAME_VOLTAGE_L3N,
    TELEMETRY_PROP_NAME_CURRENT_L1,
    TELEMETRY_PROP_NAME_CURRENT_L2,
    TELEMETRY_PROP_NAME_CURRENT_L3,
    TELEMETRY_PROP_NAME_REAL_POWER_L1N,
    TELEMETRY_PROP_NAME_REAL_POWER_L2N,
    TELEMETRY_PROP_NAME_REAL_POWER_L3N,
    TELEMETRY_PROP_NAME_APPARENT_POWER_L1N,
    TELEMETRY_PROP_NAME_APPARENT_POWER_L2N,
    TELEMETRY_PROP_NAME_APPARENT_POWER_L3N,
    TELEMETRY_PROP_NAME_REACTIVE_POWER_L1N,
    TELEMETRY_PROP_NAME_REACTIVE_POWER_L2N,
    TELEMETRY_PROP_NAME_REACTIVE_POWER_L3N,
    TELEMETRY_PROP_NAME_POWER_FACTOR_L1N,
    TELEMETRY_PROP_NAME_POWER_FACTOR_L2N,
    TELEMETRY_PROP_NAME_POWER_FACTOR_L3N,
    TELEMETRY_PROP_NAME_COS_PHI_L1,
    TELEMETRY_PROP_NAME_COS_PHI_L2,
    TELEMETRY_PROP_NAME_COS_PHI_L3,
    TELEMETRY_PROP_NAME_AVG_VOLTAGE_LN,
    TELEMETRY_PROP_NAME_AVG_CURRENTL,
    TELEMETRY_PROP_NAME_CURRENT_TOTAL,
    TELEMETRY_PROP_NAME_REAL_POWER_TOTAL,
    TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL,
    TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL,
    TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL,
    TELEMETRY_PROP_NAME_AVG_COS_PHI,
    TELEMETRY_PROP_NAME_FREQUENCY,
    TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL,
    TELEMETRY_PROP_NAME_VOLTAGE_L1L2,
    TELEMETRY_PROP_NAME_VOLTAGE_L2L3,
    TELEMETRY_PROP_NAME_VOLTAGE_L1L3,
    TELEMETRY_PROP_NAME_AVG_VOLTAGE_LL,
    TELEMETRY_PROP_NAME_CURRENT_NEUTRAL,
    TELEMETRY_PROP_NAME_THD_VOLTS_L1N,
    TELEMETRY_PROP_NAME_THD_VOLTS_L2N,
    TELEMETRY_PROP_NAME_THD_VOLTS_L3N,
    TELEMETRY_PROP_NAME_THD_CURRENT_L1N,
    TELEMETRY_PROP_NAME_THD_CURRENT_L2N,
    TELEMETRY_PROP_NAME_THD_CURRENT_L3N,
    TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LN,
    TELEMETRY_PROP_NAME_AVG_THD_CURRENT_LN,
    TELEMETRY_PROP_NAME_THD_VOLTS_L1L2,
    TELEMETRY_PROP_NAME_THD_VOLTS_L2L3,
    TELEMETRY_PROP_NAME_THD_VOLTS_L1L3,
    TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LL,
    TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL,
    TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL,
    TELEMETRY_PROP_NAME_REAL_ENERGY_L1N,
    TELEMETRY_PROP_NAME_REAL_ENERGY_L2N,
    TELEMETRY_PROP_NAME_REAL_ENERGY_L3N,
    TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L1,
    TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L2,
    TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L3,
    TELEMETRY_PROP_NAME_APPARENT_ENERGY_L1,
    TELEMETRY_PROP_NAME_APPARENT_ENERGY_L2,
    TELEMETRY_PROP_NAME_APPARENT_ENERGY_L3,
    TELEMETRY_PROP_NAME_ROT_FIELD
};


char* TELEMETRY_PROP_NAME_COM_STATE =  "comState";
char* TELEMETRY_PROP_NAME_TIMESTAMP =  "timestamp";
char* TELEMETRY_PROP_NAME_VOLTAGE_L1N =  "voltageL1N";
char* TELEMETRY_PROP_NAME_VOLTAGE_L2N =  "voltageL2N";
char* TELEMETRY_PROP_NAME_VOLTAGE_L3N =  "voltageL3N";
char* TELEMETRY_PROP_NAME_AVG_VOLTAGE_LN =  "avgVoltageLN";
char* TELEMETRY_PROP_NAME_VOLTAGE_L1L2 =  "voltageL1L2";
char* TELEMETRY_PROP_NAME_VOLTAGE_L2L3 =  "voltageL2L3";
char* TELEMETRY_PROP_NAME_VOLTAGE_L1L3 =  "voltageL1L3";
char* TELEMETRY_PROP_NAME_AVG_VOLTAGE_LL =  "avgVoltageLL";
char* TELEMETRY_PROP_NAME_CURRENT_L1 =  "currentL1";
char* TELEMETRY_PROP_NAME_CURRENT_L2 =  "currentL2";
char* TELEMETRY_PROP_NAME_CURRENT_L3 =  "currentL3";
char* TELEMETRY_PROP_NAME_CURRENT_NEUTRAL =  "currentNeutral";
char* TELEMETRY_PROP_NAME_AVG_CURRENTL =  "avgCurrentL";
char* TELEMETRY_PROP_NAME_CURRENT_TOTAL =  "currentTotal";
char* TELEMETRY_PROP_NAME_REAL_POWER_L1N =  "realPowerL1N";
char* TELEMETRY_PROP_NAME_REAL_POWER_L2N =  "realPowerL2N";
char* TELEMETRY_PROP_NAME_REAL_POWER_L3N =  "realPowerL3N";
char* TELEMETRY_PROP_NAME_REAL_POWER_TOTAL =  "realPowerTotal";
char* TELEMETRY_PROP_NAME_APPARENT_POWER_L1N =  "apparentPowerL1N";
char* TELEMETRY_PROP_NAME_APPARENT_POWER_L2N =  "apparentPowerL2N";
char* TELEMETRY_PROP_NAME_APPARENT_POWER_L3N =  "apparentPowerL3N";
char* TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL =  "apparentPowerTotal";
char* TELEMETRY_PROP_NAME_REACTIVE_POWER_L1N =  "reactivePowerL1N";
char* TELEMETRY_PROP_NAME_REACTIVE_POWER_L2N =  "reactivePowerL2N";
char* TELEMETRY_PROP_NAME_REACTIVE_POWER_L3N =  "reactivePowerL3N";
char* TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL =  "reactivePowerTotal";
char* TELEMETRY_PROP_NAME_COS_PHI_L1 =  "cosPhiL1";
char* TELEMETRY_PROP_NAME_COS_PHI_L2 =  "cosPhiL2";
char* TELEMETRY_PROP_NAME_COS_PHI_L3 =  "cosPhiL3";
char* TELEMETRY_PROP_NAME_AVG_COS_PHI =  "avgCosPhi";
char* TELEMETRY_PROP_NAME_FREQUENCY =  "frequency";
char* TELEMETRY_PROP_NAME_ROT_FIELD =  "rotField";
char* TELEMETRY_PROP_NAME_REAL_ENERGY_L1N =  "realEnergyL1N";
char* TELEMETRY_PROP_NAME_REAL_ENERGY_L2N =  "realEnergyL2N";
char* TELEMETRY_PROP_NAME_REAL_ENERGY_L3N =  "realEnergyL3N";
char* TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL =  "realEnergyTotal";
char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_L1 =  "apparentEnergyL1";
char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_L2 =  "apparentEnergyL2";
char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_L3 =  "apparentEnergyL3";
char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL =  "apparentEnergyTotal";
char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L1 =  "reactiveEnergyL1";
char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L2 =  "reactiveEnergyL2";
char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L3 =  "reactiveEnergyL3";
char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL =  "reactiveEnergyTotal";
char* TELEMETRY_PROP_NAME_THD_VOLTS_L1N =  "THDVoltsL1N";
char* TELEMETRY_PROP_NAME_THD_VOLTS_L2N =  "THDVoltsL2N";
char* TELEMETRY_PROP_NAME_THD_VOLTS_L3N =  "THDVoltsL3N";
char* TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LN =  "avgTHDVoltsLN";
char* TELEMETRY_PROP_NAME_THD_CURRENT_L1N =  "THDCurrentL1N";
char* TELEMETRY_PROP_NAME_THD_CURRENT_L2N =  "THDCurrentL2N";
char* TELEMETRY_PROP_NAME_THD_CURRENT_L3N =  "THDCurrentL3N";
char* TELEMETRY_PROP_NAME_AVG_THD_CURRENT_LN =  "avgTHDCurrentLN";
char* TELEMETRY_PROP_NAME_THD_VOLTS_L1L2 =  "THDVoltsL1L2";
char* TELEMETRY_PROP_NAME_THD_VOLTS_L2L3 =  "THDVoltsL2L3";
char* TELEMETRY_PROP_NAME_THD_VOLTS_L1L3 =  "THDVoltsL1L3";
char* TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LL =  "avgTHDVoltsLL";
char* TELEMETRY_PROP_NAME_POWER_FACTOR_L1N =  "powerFactorL1N";
char* TELEMETRY_PROP_NAME_POWER_FACTOR_L2N =  "powerFactorL2N";
char* TELEMETRY_PROP_NAME_POWER_FACTOR_L3N =  "powerFactorL3N";
char* TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL =  "powerFactorTotal";

char* TELEMETRY_PROP_NAME_LAST_DATA_ERROR = "lastDataError";
char* TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER = "dataErrorCounter";
