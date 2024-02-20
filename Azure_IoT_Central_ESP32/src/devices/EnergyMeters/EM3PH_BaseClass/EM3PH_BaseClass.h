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
  void updatePreviousValues();
  

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
};
