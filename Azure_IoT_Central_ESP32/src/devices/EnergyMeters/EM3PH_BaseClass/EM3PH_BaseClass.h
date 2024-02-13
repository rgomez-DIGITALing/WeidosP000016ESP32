#pragma once
#include <ArduinoModbus.h>
#include "../EMDataDefinitions.h"
#include "../em_telemetryDefinition.h"



class EM3PhBaseClass{
  public:

  private:
    uint8_t id;
    char* identifier;
    char* asset;
    char* location1;
    char* location2;

    COM_error_t comError;
    bool prevDataAvailable = false;
    float prevRealPowerL1N;
    float prevRealPowerL2N;
    float prevRealPowerL3N;
    float prevRealPowerTotal;
    float prevApparentPowerL1N;
    float prevApparentPowerL2N;
    float prevApparentPowerL3N;
    float prevApparentPowerTotal;
    float prevReactivePowerL1N;
    float prevReactivePowerL2N;
    float prevReactivePowerL3N;
    float prevReactivePowerTotal;
    float prevRealEnergyL1N;
    float prevRealEnergyL2N;
    float prevRealEnergyL3N;
    float prevRealEnergyTotal;
    float prevApparentEnergyL1;
    float prevApparentEnergyL2;
    float prevApparentEnergyL3;
    float prevApparentEnergyTotal;
    float prevReactiveEnergyL1;
    float prevReactiveEnergyL2;
    float prevReactiveEnergyL3;
    float prevReactiveEnergyTotal;

    float realEnergyConsL1;
    float realEnergyConsL2;
    float realEnergyConsL3;
    float realEnergyConsTotal;
    float realEnergyDelivL1;
    float realEnergyDelivL2;
    float realEnergyDelivL3;
    float realEnergyDelivTotal;
    float realEnergySum;
    

    float reactiveEnergyConsL1;
    float reactiveEnergyConsL2;
    float reactiveEnergyConsL3;
    float reactiveEnergyDelivL1;
    float reactiveEnergyDelivL2;
    float reactiveEnergyDelivL3;
    
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
};
