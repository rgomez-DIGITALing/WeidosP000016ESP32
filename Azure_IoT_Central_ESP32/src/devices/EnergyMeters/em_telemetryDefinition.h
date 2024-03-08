#pragma once

int isEMDataValid(float data);
double getEMErrorValue(int dataError);
//static const double NO_PREV_DATA_AVAILABLE_ERROR_VALUE = (double)999999999999998;

extern const double NAN_ERROR_VALUE;
extern const double NO_PREV_DATA_AVAILABLE_ERROR_VALUE;
extern const float FLOAT_NO_PREV_DATA_AVAILABLE_ERROR_VALUE;

//General data
extern char* EM1PH_DATA_TELEMETRY_NAMES[];
extern char* EM3PH_DATA_TELEMETRY_NAMES[];

//Consumed/Delivered energy
extern char* EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[];
extern char* EM3PH_CONS_DELIV_DATA_TELEMETRY_NAMES[];

//Adjusted data
extern char* EM1PH_ADJUSTED_DATA_TELEMETRY_NAMES[];
extern char* EM3PH_ADJUSTED_DATA_TELEMETRY_NAMES[];

//Incremental data
extern char* EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[];
extern char* EM3PH_INCREMENTAL_DATA_TELEMETRY_NAMES[];
extern char* EM3PH_BASIC_LINA_INCREMENTAL_DATA_TELEMETRY_NAMES[];

//Harmonic data
extern char* EM3PH_HARMONIC_DATA_TELEMETRY_NAMES[];


//General variables
extern char* TELEMETRY_PROP_NAME_COM_ERROR;
extern char* TELEMETRY_PROP_NAME_TIMESTAMP;
extern char* TELEMETRY_PROP_NAME_DATA_SOURCE_STATUS;

extern char* TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER;
extern char* TELEMETRY_PROP_NAME_CONS_DELIV_DATA_ERROR_COUNTER;
extern char* TELEMETRY_PROP_NAME_ADJUSTED_DATA_ERROR_COUNTER;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_DATA_ERROR_COUNTER;
extern char* TELEMETRY_PROP_NAME_HARMONIC_DATA_ERROR_COUNTER;



//Normal variables
extern char* TELEMETRY_PROP_NAME_VOLTAGE_L1N;
extern char* TELEMETRY_PROP_NAME_VOLTAGE_L2N;
extern char* TELEMETRY_PROP_NAME_VOLTAGE_L3N;
extern char* TELEMETRY_PROP_NAME_AVG_VOLTAGE_LN;
extern char* TELEMETRY_PROP_NAME_VOLTAGE_L1L2;
extern char* TELEMETRY_PROP_NAME_VOLTAGE_L2L3;
extern char* TELEMETRY_PROP_NAME_VOLTAGE_L1L3;
extern char* TELEMETRY_PROP_NAME_AVG_VOLTAGE_LL;
extern char* TELEMETRY_PROP_NAME_CURRENT_L1;
extern char* TELEMETRY_PROP_NAME_CURRENT_L2;
extern char* TELEMETRY_PROP_NAME_CURRENT_L3;
extern char* TELEMETRY_PROP_NAME_CURRENT_NEUTRAL;
extern char* TELEMETRY_PROP_NAME_AVG_CURRENTL;
extern char* TELEMETRY_PROP_NAME_CURRENT_TOTAL;
extern char* TELEMETRY_PROP_NAME_REAL_POWER_L1N;
extern char* TELEMETRY_PROP_NAME_REAL_POWER_L2N;
extern char* TELEMETRY_PROP_NAME_REAL_POWER_L3N;
extern char* TELEMETRY_PROP_NAME_REAL_POWER_TOTAL;
extern char* TELEMETRY_PROP_NAME_APPARENT_POWER_L1N;
extern char* TELEMETRY_PROP_NAME_APPARENT_POWER_L2N;
extern char* TELEMETRY_PROP_NAME_APPARENT_POWER_L3N;
extern char* TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL;
extern char* TELEMETRY_PROP_NAME_REACTIVE_POWER_L1N;
extern char* TELEMETRY_PROP_NAME_REACTIVE_POWER_L2N;
extern char* TELEMETRY_PROP_NAME_REACTIVE_POWER_L3N;
extern char* TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL;
extern char* TELEMETRY_PROP_NAME_COS_PHI_L1;
extern char* TELEMETRY_PROP_NAME_COS_PHI_L2;
extern char* TELEMETRY_PROP_NAME_COS_PHI_L3;
extern char* TELEMETRY_PROP_NAME_COS_PHI_TOTAL;
// extern char* TELEMETRY_PROP_NAME_AVG_COS_PHI;
extern char* TELEMETRY_PROP_NAME_FREQUENCY;
extern char* TELEMETRY_PROP_NAME_ROT_FIELD;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_L1;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_L2;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_L3;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL;
extern char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_L1;
extern char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_L2;
extern char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_L3;
extern char* TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L1;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L2;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L3;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL;
extern char* TELEMETRY_PROP_NAME_THD_VOLTS_L1N;
extern char* TELEMETRY_PROP_NAME_THD_VOLTS_L2N;
extern char* TELEMETRY_PROP_NAME_THD_VOLTS_L3N;
extern char* TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LN;
extern char* TELEMETRY_PROP_NAME_THD_CURRENT_L1;
extern char* TELEMETRY_PROP_NAME_THD_CURRENT_L2;
extern char* TELEMETRY_PROP_NAME_THD_CURRENT_L3;
extern char* TELEMETRY_PROP_NAME_AVG_THD_CURRENT_L;
extern char* TELEMETRY_PROP_NAME_THD_VOLTS_L1L2;
extern char* TELEMETRY_PROP_NAME_THD_VOLTS_L2L3;
extern char* TELEMETRY_PROP_NAME_THD_VOLTS_L1L3;
extern char* TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LL;
extern char* TELEMETRY_PROP_NAME_POWER_FACTOR_L1N;
extern char* TELEMETRY_PROP_NAME_POWER_FACTOR_L2N;
extern char* TELEMETRY_PROP_NAME_POWER_FACTOR_L3N;
extern char* TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL;

extern char* TELEMETRY_PROP_NAME_PHASE_CURRENT_SUM;



//Cons/Deliv variables
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_CONS_TOTAL;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_DELIV_TOTAL;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_CONS_L1;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_CONS_L2;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_CONS_L3;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_DELIV_L1;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_DELIV_L2;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_DELIV_L3;

extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_CONS_L1;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_CONS_L2;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_CONS_L3;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_DELIV_L1;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_DELIV_L2;
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_DELIV_L3;


extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_CONS_TOTAL; //1ph only
extern char* TELEMETRY_PROP_NAME_REACTIVE_ENERGY_DELIV_TOTAL; //1ph only

//Adjusted Variables
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_ADJUSTED_L1;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_ADJUSTED_L2;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_ADJUSTED_L3;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_ADJUSTED_TOTAL;

extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_CONS_TOTAL_SUM;
extern char* TELEMETRY_PROP_NAME_REAL_ENERGY_DELIV_TOTAL_SUM;


// Incremental variables
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_L1;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_L2;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_L3;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_TOTAL;

extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_ADJUSTED_L1;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_ADJUSTED_L2;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_ADJUSTED_L3;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REAL_ENERGY_ADJUSTED_TOTAL;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_APPARENT_ENERGY_L1;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_APPARENT_ENERGY_L2;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_APPARENT_ENERGY_L3;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_APPARENT_ENERGY_TOTAL;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REACTIVE_ENERGY_L1;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REACTIVE_ENERGY_L2;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REACTIVE_ENERGY_L3;
extern char* TELEMETRY_PROP_NAME_INCREMENTAL_REACTIVE_ENERGY_TOTAL;


//Harmonics variables
extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L1;

extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L2;

extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L3;

extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L4;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L4;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L4;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L4;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L4;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L4;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L4;

extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L1L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L1L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L1L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L1L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L1L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L1L2;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L1L2;

extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L2L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L2L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L2L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L2L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L2L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L2L3;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L2L3;

extern char* TELEMETRY_PROP_NAME_H_VOLTS_3_L3L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_5_L3L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_7_L3L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_9_L3L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_11_L3L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_13_L3L1;
extern char* TELEMETRY_PROP_NAME_H_VOLTS_15_L3L1;

extern char* TELEMETRY_PROP_NAME_H_CURRENT_3_L1;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_5_L1;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_7_L1;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_9_L1;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_11_L1;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_13_L1;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_15_L1;

extern char* TELEMETRY_PROP_NAME_H_CURRENT_3_L2;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_5_L2;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_7_L2;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_9_L2;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_11_L2;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_13_L2;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_15_L2;

extern char* TELEMETRY_PROP_NAME_H_CURRENT_3_L3;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_5_L3;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_7_L3;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_9_L3;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_11_L3;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_13_L3;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_15_L3;

extern char* TELEMETRY_PROP_NAME_H_CURRENT_3_L4;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_5_L4;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_7_L4;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_9_L4;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_11_L4;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_13_L4;
extern char* TELEMETRY_PROP_NAME_H_CURRENT_15_L4;
