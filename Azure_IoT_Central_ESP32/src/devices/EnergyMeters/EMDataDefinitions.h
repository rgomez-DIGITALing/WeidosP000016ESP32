#pragma once
#include <cstdint>


#define NUM_TOTAL_DATA_1PHASE 11
#define NUM_TOTAL_DATA_3PHASE 60
#define NUM_TOTAL_PERIOD_DATA_1PHASE 6
#define NUM_TOTAL_PERIOD_DATA_3PHASE 24

//static const double NO_PREV_DATA_AVAILABLE_ERROR_VALUE = (double)999999999999998;
//#define NUM_TOTAL_DATA_EM750 60


typedef enum{
  COM_OK,
  COM_BEGIN_ERROR,
  COM_BATCH_1_ERROR,
  COM_BATCH_2_ERROR,
  COM_BATCH_3_ERROR,
  COM_BATCH_4_ERROR
} COM_error_t;



enum EM1PHDataArrayIndex{
 EM1PH_VOLTAGE_L1N_INDEX,
 EM1PH_CURRENT_L1_INDEX,
 EM1PH_TOTAL_REAL_POWER_INDEX,
 EM1PH_TOTAL_APPARENT_POWER_INDEX,
 EM1PH_TOTAL_REACTIVE_POWER_INDEX,
 EM1PH_TOTAL_POWER_FACTOR_INDEX,
 EM1PH_FREQUENCY_INDEX,
 EM1PH_TOTAL_REAL_ENERGY_INDEX,
 EM1PH_TOTAL_REACTIVE_ENERGY_INDEX,
 EM1PH_ROTATION_FIELD_INDEX,
 EM1PH_TOTAL_APPARENT_ENERGY_INDEX
};




typedef struct em1phData_struct_t{
  COM_error_t comError;

  union{
      float data[NUM_TOTAL_DATA_1PHASE];

      struct{
        float voltageL1N;
        float currentL1;
        float realPowerTotal, apparentPowerTotal, reactivePowerTotal;
        float powerFactorTotal;
        float frequency;
        float realEnergyTotal, reactiveEnergyTotal;
        float rotField;
        float apparentEnergyTotal;
      };
    };

    union{
      float periodData[NUM_TOTAL_PERIOD_DATA_1PHASE];

      struct{
        float periodRealPowerTotal;
        float periodApparentPowerTotal;
        float periodReactivePowerTotal;
        float periodRealEnergyTotal;
        float periodApparentEnergyTotal;
        float periodReactiveEnergyTotal;
      };
    };
} em1phData_t;


typedef struct em3phData_struct_t{
  COM_error_t comError;

  union{
      float data[NUM_TOTAL_DATA_3PHASE];

      struct{
        float voltageL1N, voltageL2N, voltageL3N;
        float currentL1, currentL2, currentL3;
        float realPowerL1N, realPowerL2N, realPowerL3N;
        float apparentPowerL1N, apparentPowerL2N, apparentPowerL3N;
        float reactivePowerL1N, reactivePowerL2N, reactivePowerL3N;
        float powerFactorL1N, powerFactorL2N, powerFactorL3N;
        float cosPhiL1, cosPhiL2, cosPhiL3;
        float avgVoltageLN, avgCurrentL;
        float currentTotal, realPowerTotal, apparentPowerTotal, reactivePowerTotal, powerFactorTotal;
        float avgCosPhi, frequency;
        float apparentEnergyTotal;
        float voltageL1L2, voltageL2L3, voltageL1L3, avgVoltageLL;
        float currentNeutral;
        float THDVoltsL1N, THDVoltsL2N, THDVoltsL3N;
        float THDCurrentL1N, THDCurrentL2N, THDCurrentL3N;
        float avgTHDVoltsLN, avgTHDCurrentLN;
        float THDVoltsL1L2, THDVoltsL2L3, THDVoltsL1L3, avgTHDVoltsLL;
        float realEnergyTotal, reactiveEnergyTotal;
        float realEnergyL1, realEnergyL2, realEnergyL3;
        float reactiveEnergyL1, reactiveEnergyL2, reactiveEnergyL3;
        float apparentEnergyL1, apparentEnergyL2, apparentEnergyL3;
        float rotField;
      };
    };

    union{
      float periodData[NUM_TOTAL_PERIOD_DATA_3PHASE];

      struct{
        float periodRealPowerL1N;
        float periodRealPowerL2N;
        float periodRealPowerL3N;
        float periodRealPowerTotal;
        float periodApparentPowerL1N;
        float periodApparentPowerL2N;
        float periodApparentPowerL3N;
        float periodApparentPowerTotal;
        float periodReactivePowerL1N;
        float periodReactivePowerL2N;
        float periodReactivePowerL3N;
        float periodReactivePowerTotal;
        float periodRealEnergyL1N;
        float periodRealEnergyL2N;
        float periodRealEnergyL3N;
        float periodRealEnergyTotal;
        float periodApparentEnergyL1;
        float periodApparentEnergyL2;
        float periodApparentEnergyL3;
        float periodApparentEnergyTotal;
        float periodReactiveEnergyL1;
        float periodReactiveEnergyL2;
        float periodReactiveEnergyL3;
        float periodReactiveEnergyTotal;
      };
    };
} em3phData_t;



enum EM3PHDataArrayIndex{
  EM3PH_VOLTAGE_L1N_INDEX,
  EM3PH_VOLTAGE_L2N_INDEX,
  EM3PH_VOLTAGE_L3N_INDEX,
  EM3PH_CURRENT_L1_INDEX,
  EM3PH_CURRENT_L2_INDEX,
  EM3PH_CURRENT_L3_INDEX,
  EM3PH_REAL_POWER_L1N_INDEX,
  EM3PH_REAL_POWER_L2N_INDEX,
  EM3PH_REAL_POWER_L3N_INDEX,
  EM3PH_APPARENT_POWER_L1N_INDEX,
  EM3PH_APPARENT_POWER_L2N_INDEX,
  EM3PH_APPARENT_POWER_L3N_INDEX,
  EM3PH_REACTIVE_POWER_L1N_INDEX,
  EM3PH_REACTIVE_POWER_L2N_INDEX,
  EM3PH_REACTIVE_POWER_L3N_INDEX,
  EM3PH_POWER_FACTOR_L1N_INDEX,
  EM3PH_POWER_FACTOR_L2N_INDEX,
  EM3PH_POWER_FACTOR_L3N_INDEX,
  EM3PH_COS_PHI_L1_INDEX,
  EM3PH_COS_PHI_L2_INDEX,
  EM3PH_COS_PHI_L3_INDEX,
  EM3PH_AVG_VOLTAGE_LN_INDEX,
  EM3PH_AVG_CURRENTL_INDEX,
  EM3PH_CURRENT_TOTAL_INDEX,
  EM3PH_REAL_POWER_TOTAL_INDEX,
  EM3PH_APPARENT_POWER_TOTAL_INDEX,
  EM3PH_REACTIVE_POWER_TOTAL_INDEX,
  EM3PH_POWER_FACTOR_TOTAL_INDEX,//
  EM3PH_AVG_COS_PHI_INDEX,
  EM3PH_FREQUENCY_INDEX,
  EM3PH_APPARENT_ENERGY_TOTAL_INDEX,
  EM3PH_VOLTAGE_L1L2_INDEX,
  EM3PH_VOLTAGE_L2L3_INDEX,
  EM3PH_VOLTAGE_L1L3_INDEX,
  EM3PH_AVG_VOLTAGE_LL_INDEX,
  EM3PH_CURRENT_NEUTRAL_INDEX,
  EM3PH_THD_VOLTS_L1N_INDEX,
  EM3PH_THD_VOLTS_L2N_INDEX,
  EM3PH_THD_VOLTS_L3N_INDEX,
  EM3PH_THD_CURRENT_L1N_INDEX,
  EM3PH_THD_CURRENT_L2N_INDEX,
  EM3PH_THD_CURRENT_L3N_INDEX,
  EM3PH_AVG_THD_VOLTS_LN_INDEX,
  EM3PH_AVG_THD_CURRENT_LN_INDEX,
  EM3PH_THD_VOLTS_L1L2_INDEX,
  EM3PH_THD_VOLTS_L2L3_INDEX,
  EM3PH_THD_VOLTS_L1L3_INDEX,
  EM3PH_AVG_THD_VOLTS_LL_INDEX,
  EM3PH_REAL_ENERGY_TOTAL_INDEX,
  EM3PH_REACTIVE_ENERGY_TOTAL_INDEX,
  EM3PH_REAL_ENERGY_L1N_INDEX,
  EM3PH_REAL_ENERGY_L2N_INDEX,
  EM3PH_REAL_ENERGY_L3N_INDEX,
  EM3PH_REACTIVE_ENERGY_L1_INDEX,
  EM3PH_REACTIVE_ENERGY_L2_INDEX,
  EM3PH_REACTIVE_ENERGY_L3_INDEX,
  EM3PH_APPARENT_ENERGY_L1_INDEX,
  EM3PH_APPARENT_ENERGY_L2_INDEX,
  EM3PH_APPARENT_ENERGY_L3_INDEX,
  EM3PH_ROT_FIELD_INDEX,
  EM3PH_PERIOD_REAL_POWER_L1N,
  EM3PH_PERIOD_REAL_POWER_L2N,
  EM3PH_PERIOD_REAL_POWER_L3N,
  EM3PH_PERIOD_REAL_POWER_TOTAL,
  EM3PH_PERIOD_APPARENT_POWER_L1N,
  EM3PH_PERIOD_APPARENT_POWER_L2N,
  EM3PH_PERIOD_APPARENT_POWER_L3N,
  EM3PH_PERIOD_APPARENT_POWER_TOTAL,
  EM3PH_PERIOD_REACTIVE_POWER_L1N,
  EM3PH_PERIOD_REACTIVE_POWER_L2N,
  EM3PH_PERIOD_REACTIVE_POWER_L3N,
  EM3PH_PERIOD_REACTIVE_POWER_TOTAL,
  EM3PH_PERIOD_REAL_ENERGY_L1N,
  EM3PH_PERIOD_REAL_ENERGY_L2N,
  EM3PH_PERIOD_REAL_ENERGY_L3N,
  EM3PH_PERIOD_REAL_ENERGY_TOTAL,
  EM3PH_PERIOD_APPARENT_ENERGY_L1,
  EM3PH_PERIOD_APPARENT_ENERGY_L2,
  EM3PH_PERIOD_APPARENT_ENERGY_L3,
  EM3PH_PERIOD_APPARENT_ENERGY_TOTAL,
  EM3PH_PERIOD_REACTIVE_ENERGY_L1,
  EM3PH_PERIOD_REACTIVE_ENERGY_L2,
  EM3PH_PERIOD_REACTIVE_ENERGY_L3,
  EM3PH_PERIOD_REACTIVE_ENERGY_TOTAL
};
