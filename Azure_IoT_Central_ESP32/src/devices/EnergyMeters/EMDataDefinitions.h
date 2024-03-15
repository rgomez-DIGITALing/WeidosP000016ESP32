#pragma once
#include <cstdint>


#define NUM_TOTAL_DATA_1PHASE 11
#define NUM_TOTAL_DATA_3PHASE 60
#define NUM_TOTAL_DATA_3PHASE 59

#define NUM_TOTAL_CONS_DELIV_DATA_1PHASE 4
#define NUM_TOTAL_CONS_DELIV_DATA_3PHASE 14

#define NUM_TOTAL_VALUE_LINE_CONS_DELIV_DATA_3PHASE 8
#define NUM_TOTAL_BASIC_LINE_CONS_DELIV_DATA_3PHASE 12
#define BASIC_LINE_CONS_DELIV_FIRST_INDEX 2

#define NUM_TOTAL_ADJUSTED_DATA_3PHASE 6

#define NUM_TOTAL_HARMONIC_DATA_3PHASE 77

#define NUM_TOTAL_INCREMENTAL_DATA_1PHASE 3
#define NUM_TOTAL_INCREMENTAL_DATA_3PHASE 12

//static const double NO_PREV_DATA_AVAILABLE_ERROR_VALUE = (double)999999999999998;
//#define NUM_TOTAL_DATA_EM750 60
typedef enum {
  EM_NONE,
  EM110_RTU,
  EM111_RTU,
  EM120_RTU,
  EM122_RTU,
  EM220_RTU,
  EM110_TCP,
  EM111_TCP,
  EM120_TCP,
  EM122_TCP,
  EM750_TCP,
  EA750_TCP
} emType_t;


typedef enum{
  COM_OK,
  COM_BEGIN_ERROR,
  COM_BATCH_1_ERROR,
  COM_BATCH_2_ERROR,
  COM_BATCH_3_ERROR,
  COM_BATCH_4_ERROR,
  COM_BATCH_5_ERROR,
  COM_BATCH_6_ERROR,
  COM_BATCH_7_ERROR,
  COM_BATCH_8_ERROR,
  COM_BATCH_9_ERROR,
  COM_BATCH_10_ERROR,
  COM_BATCH_11_ERROR,
  COM_BATCH_12_ERROR,
  COM_BATCH_13_ERROR,
  COM_BATCH_14_ERROR,
  COM_BATCH_15_ERROR,
  COM_BATCH_16_ERROR,
  COM_BATCH_17_ERROR,
} COM_error_t;



typedef struct em1phData_struct_t{
  COM_error_t comError;

  union{
      float data[NUM_TOTAL_DATA_1PHASE];

      struct{
        float voltageL1N;
        float currentL1;
        float realPowerL1N, apparentPowerL1N, reactivePowerL1N;
        float powerFactorL1N;
        float frequency;
        float realEnergyTotal, reactiveEnergyTotal;
        float rotField;
        float apparentEnergyTotal;
      };
    };

  union{
      float consDelivData[NUM_TOTAL_CONS_DELIV_DATA_1PHASE];

      struct{
        float realEnergyConsTotal;
        float realEnergyDelivTotal;
        float reactiveEnergyConsTotal;
        float reactiveEnergyDelivTotal;
      };
    };

    union{
      float incrementalData[NUM_TOTAL_INCREMENTAL_DATA_1PHASE];

      struct{
        float incrementalRealEnergyTotal;
        float incrementalApparentEnergyTotal;
        float incrementalReactiveEnergyTotal;
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
        float realPowerTotal, apparentPowerTotal, reactivePowerTotal, powerFactorTotal;
        float avgCosPhi, frequency;
        float apparentEnergyTotal;
        float voltageL1L2, voltageL2L3, voltageL1L3, avgVoltageLL;
        float currentNeutral;
        float THDVoltsL1N, THDVoltsL2N, THDVoltsL3N, THDVoltsL4N;
        float THDCurrentL1, THDCurrentL2, THDCurrentL3, THDCurrentL4;
        float avgTHDVoltsLN, avgTHDCurrentL;
        float THDVoltsL1L2, THDVoltsL2L3, THDVoltsL1L3, avgTHDVoltsLL;
        float realEnergyTotal, reactiveEnergyTotal;
        float realEnergyL1, realEnergyL2, realEnergyL3;
        float reactiveEnergyL1, reactiveEnergyL2, reactiveEnergyL3;
        float apparentEnergyL1, apparentEnergyL2, apparentEnergyL3;
        float rotField;
      };
    };

  float currentTotal; //Variable for the Value Line ONLY
  float phaseCurrentSum;  //Variable for the Basic Line ONLY!
//Cons/Deliv data
    union{
      float consDelivData[NUM_TOTAL_CONS_DELIV_DATA_3PHASE];

      struct{
        //Data via Modbus
        float realEnergyConsTotal;
        float realEnergyDelivTotal;
        float realEnergyConsL1;
        float realEnergyConsL2;
        float realEnergyConsL3;
        float realEnergyDelivL1;
        float realEnergyDelivL2;
        float realEnergyDelivL3;
        float reactiveEnergyConsL1;
        float reactiveEnergyConsL2;
        float reactiveEnergyConsL3;
        float reactiveEnergyDelivL1;
        float reactiveEnergyDelivL2;
        float reactiveEnergyDelivL3;
      };
    };

//Adjusted data
    union{
      float adjustedData[NUM_TOTAL_ADJUSTED_DATA_3PHASE];

      struct{
        float realEnergyAdjustedL1;
        float realEnergyAdjustedL2;
        float realEnergyAdjustedL3;
        float realEnergyAdjustedTotal;
        float realEnergyConsTotalSum;
        float realEnergyDelivTotalSum;
      };
    };

  union{
      float incrementalData[NUM_TOTAL_INCREMENTAL_DATA_3PHASE];

      struct{
        float incrementalRealEnergyAdjustedL1;
        float incrementalRealEnergyAdjustedL2;
        float incrementalRealEnergyAdjustedL3;
        float incrementalRealEnergyAdjustedTotal;
        float incrementalApparentEnergyL1;
        float incrementalApparentEnergyL2;
        float incrementalApparentEnergyL3;
        float incrementalApparentEnergyTotal;
        float incrementalReactiveEnergyL1;
        float incrementalReactiveEnergyL2;
        float incrementalReactiveEnergyL3;
        float incrementalReactiveEnergyTotal;
      };
    };



  union{
    float harmonicData[NUM_TOTAL_HARMONIC_DATA_3PHASE];

    struct{
      float THDVolts3L1;
      float THDVolts5L1;
      float THDVolts7L1;
      float THDVolts9L1;
      float THDVolts11L1;
      float THDVolts13L1;
      float THDVolts15L1;

      float THDVolts3L2;
      float THDVolts5L2;
      float THDVolts7L2;
      float THDVolts9L2;
      float THDVolts11L2;
      float THDVolts13L2;
      float THDVolts15L2;

      float THDVolts3L3;
      float THDVolts5L3;
      float THDVolts7L3;
      float THDVolts9L3;
      float THDVolts11L3;
      float THDVolts13L3;
      float THDVolts15L3;

      float THDVolts3L4;
      float THDVolts5L4;
      float THDVolts7L4;
      float THDVolts9L4;
      float THDVolts11L4;
      float THDVolts13L4;
      float THDVolts15L4;

      float THDVolts3L1L2;
      float THDVolts5L1L2;
      float THDVolts7L1L2;
      float THDVolts9L1L2;
      float THDVolts11L1L2;
      float THDVolts13L1L2;
      float THDVolts15L1L2;

      float THDVolts3L2L3;
      float THDVolts5L2L3;
      float THDVolts7L2L3;
      float THDVolts9L2L3;
      float THDVolts11L2L3;
      float THDVolts13L2L3;
      float THDVolts15L2L3;

      float THDVolts3L3L1;
      float THDVolts5L3L1;
      float THDVolts7L3L1;
      float THDVolts9L3L1;
      float THDVolts11L3L1;
      float THDVolts13L3L1;
      float THDVolts15L3L1;



      float THDCurrent3L1;
      float THDCurrent5L1;
      float THDCurrent7L1;
      float THDCurrent9L1;
      float THDCurrent11L1;
      float THDCurrent13L1;
      float THDCurrent15L1;

      float THDCurrent3L2;
      float THDCurrent5L2;
      float THDCurrent7L2;
      float THDCurrent9L2;
      float THDCurrent11L2;
      float THDCurrent13L2;
      float THDCurrent15L2;

      float THDCurrent3L3;
      float THDCurrent5L3;
      float THDCurrent7L3;
      float THDCurrent9L3;
      float THDCurrent11L3;
      float THDCurrent13L3;
      float THDCurrent15L3;

      float THDCurrent3L4;
      float THDCurrent5L4;
      float THDCurrent7L4;
      float THDCurrent9L4;
      float THDCurrent11L4;
      float THDCurrent13L4;
      float THDCurrent15L4;
    };
  };
    
} em3phData_t;
