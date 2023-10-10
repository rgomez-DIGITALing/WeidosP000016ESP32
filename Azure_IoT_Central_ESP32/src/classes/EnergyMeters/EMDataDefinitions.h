#pragma once
#include <cstdint>


#define NUM_TOTAL_DATA_1PHASE 11
#define NUM_TOTAL_DATA_3PHASE 60
//#define NUM_TOTAL_DATA_EM750 60


typedef enum{
  COM_OK,
  COM_BEGIN_ERROR,
  COM_BATCH_1_ERROR,
  COM_BATCH_2_ERROR,
  COM_BATCH_3_ERROR
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
  EM3PH_ROT_FIELD_INDEX
};

// typedef struct em750Data_struct_t{
//   uint8_t comState;
//   union{
//       float data[NUM_TOTAL_DATA_EM750];

//       struct{
//         float voltageL1N, voltageL2N, voltageL3N;
//         float avgVoltageLN;
//         float voltageL1L2, voltageL2L3, voltageL1L3, avgVoltageLL;
//         float currentL1, currentL2, currentL3;
//         float currentNeutral;
//         float avgCurrentL;
//         float currentTotal;
//         float realPowerL1N, realPowerL2N, realPowerL3N;
//         float realPowerTotal;
//         float apparentPowerL1N, apparentPowerL2N, apparentPowerL3N;
//         float apparentPowerTotal;
//         float reactivePowerL1N, reactivePowerL2N, reactivePowerL3N;
//         float reactivePowerTotal;
//         float cosPhiL1, cosPhiL2, cosPhiL3;
//         float avgCosPhi, frequency, rotField;
//         float realEnergyL1N, realEnergyL2N, realEnergyL3N;
//         float realEnergyTotal;
//         float apparentEnergyL1, apparentEnergyL2, apparentEnergyL3;
//         float apparentEnergyTotal;
//         float reactiveEnergyL1, reactiveEnergyL2, reactiveEnergyL3;
//         float reactiveEnergyTotal;
//         float THDVoltsL1N, THDVoltsL2N, THDVoltsL3N;
//         float avgTHDVoltsLN;
//         float THDCurrentL1N, THDCurrentL2N, THDCurrentL3N;
//         float avgTHDCurrentLN;
//         float THDVoltsL1L2, THDVoltsL2L3, THDVoltsL1L3;
//         float avgTHDVoltsLL;
//         float powerFactorL1N, powerFactorL2N, powerFactorL3N;
//         float powerFactorTotal;
//       };
//     };
// } em750Data_t;