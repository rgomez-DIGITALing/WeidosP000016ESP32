#pragma once
#include <ArduinoModbus.h>
#include "../EMDataDefinitions.h"
#include "../em_telemetryDefinition.h"



class EM3PH_BaseClass{
  public:
  EM3PH_BaseClass(){};
  EM3PH_BaseClass(IPAddress ip);
  EM3PH_BaseClass(uint8_t modbusId);
  EM3PH_BaseClass(uint8_t modbusId, IPAddress ip);
  
  virtual int begin() = 0;
  virtual void stop() = 0;
  virtual int update() = 0;

  void copyData(float* buffer, int bufferSize);
  void getData(em3phData_t& payload);
  void resetPrevValues(){ prevDataAvailable = false; }
  virtual void updatePreviousValues();
  virtual void setSkipVariables() = 0;
  

  void setModbusId(uint8_t id){ this->modbusId = modbusId; }
  uint8_t getModbusId(){ return modbusId; }

  IPAddress* getIpAddress(){ return &ipAddress; }

  // IPAddress* getIpAddress(){ return &ipAddress; }

  protected:
    uint8_t modbusId = 0;
    IPAddress ipAddress;

    COM_error_t comError = COM_OK;
    
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
        float cosPhiTotal, frequency;
        // float avgCosPhi, frequency;
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
        float currentTotal; //Variable for the Value Line ONLY!
        float phaseCurrentSum; //Variable for the Basic Line ONLY!
      };
    };
    
    // float currentTotal; //Variable for the Value Line ONLY!
    // float phaseCurrentSum; //Variable for the Basic Line ONLY!

//Cons/Deliv variables
    union{
      float consDelivData[NUM_TOTAL_CONS_DELIV_DATA_3PHASE];

      struct{
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

    //Adjusted variables
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


    //Incremental variables
    bool prevDataAvailable = false;

    float prevRealEnergyAdjustedL1;
    float prevRealEnergyAdjustedL2;
    float prevRealEnergyAdjustedL3;
    float prevRealEnergyAdjustedTotal;
    float prevApparentEnergyL1;
    float prevApparentEnergyL2;
    float prevApparentEnergyL3;
    float prevApparentEnergyTotal;
    float prevReactiveEnergyL1;
    float prevReactiveEnergyL2;
    float prevReactiveEnergyL3;
    float prevReactiveEnergyTotal;



    //Harmonic variables
    union{
      float harmonicData[NUM_TOTAL_HARMONIC_DATA_3PHASE];

      struct{
        float HVolts3L1;
        float HVolts5L1;
        float HVolts7L1;
        float HVolts9L1;
        float HVolts11L1;
        float HVolts13L1;
        float HVolts15L1;

        float HVolts3L2;
        float HVolts5L2;
        float HVolts7L2;
        float HVolts9L2;
        float HVolts11L2;
        float HVolts13L2;
        float HVolts15L2;

        float HVolts3L3;
        float HVolts5L3;
        float HVolts7L3;
        float HVolts9L3;
        float HVolts11L3;
        float HVolts13L3;
        float HVolts15L3;

        float HVolts3L4;
        float HVolts5L4;
        float HVolts7L4;
        float HVolts9L4;
        float HVolts11L4;
        float HVolts13L4;
        float HVolts15L4;


        float HVolts3L1L2;
        float HVolts5L1L2;
        float HVolts7L1L2;
        float HVolts9L1L2;
        float HVolts11L1L2;
        float HVolts13L1L2;
        float HVolts15L1L2;


        float HVolts3L2L3;
        float HVolts5L2L3;
        float HVolts7L2L3;
        float HVolts9L2L3;
        float HVolts11L2L3;
        float HVolts13L2L3;
        float HVolts15L2L3;

        float HVolts3L3L1;
        float HVolts5L3L1;
        float HVolts7L3L1;
        float HVolts9L3L1;
        float HVolts11L3L1;
        float HVolts13L3L1;
        float HVolts15L3L1;




        float HCurrent3L1;
        float HCurrent5L1;
        float HCurrent7L1;
        float HCurrent9L1;
        float HCurrent11L1;
        float HCurrent13L1;
        float HCurrent15L1;

        float HCurrent3L2;
        float HCurrent5L2;
        float HCurrent7L2;
        float HCurrent9L2;
        float HCurrent11L2;
        float HCurrent13L2;
        float HCurrent15L2;

        float HCurrent3L3;
        float HCurrent5L3;
        float HCurrent7L3;
        float HCurrent9L3;
        float HCurrent11L3;
        float HCurrent13L3;
        float HCurrent15L3;

        float HCurrent3L4;
        float HCurrent5L4;
        float HCurrent7L4;
        float HCurrent9L4;
        float HCurrent11L4;
        float HCurrent13L4;
        float HCurrent15L4;
      };
    };
};
