#pragma once
#include "../EMDataDefinitions.h"



class EM120{
  public:
    EM120(int modbusId, int ctPrimary, int ctSecondary);
    
    /**
     * Begin Modbus RTU Client with default Configuration (Baudrate = 9600 and config = SERIAL_8N1).
     *
     *
     * @return 0 on failure, number of values read on success
    */
    int begin();

    void stop();

    /**
     * Update attributes by requesting all registers. 
     *
     *
     * @return 0 on failure, 1 on success
     */
    bool update();
    
    void validateData();
    void copyData(float* buffer, int bufferSize);
    void getData(em3phData_t& payload);
    int getModusId(){ return modbusId; }
    int getCTPrimary(){ return ctPrimary; }
    int getCTSecondary(){ return ctSecondary; }

    void setIdentifier(char* identifier){ this->identifier = identifier; }
    void setAsset(char* asset){ this->asset = asset; }
    void setLocation1(char* location1){ this->location1 = location1; }
    void setLocation2(char* location2){ this->location2 = location2; }

    char* getIdentifier(){ return identifier; }
    char* getAsset(){ return asset; };
    char* getLocation1(){ return location1; }
    char* getLocation2(){ return location2; }
    //void printCosPhi();
    

  private:
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the first batch.
     */
    void assignData();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the second batch.
     */
    void assignData2();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the third batch.
     */
    void assignData3();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the second batch.
     */
    void computeValues();
    /**
     * Read two bytes from the Modbus Client and join them to cast it into a float variable.
     *  
     * @return Register's data.
     */
    float getNextData();


    int modbusId;
    COM_error_t comError;
    int ctPrimary = 1;
    int ctSecondary = 1;
    char* identifier;
    char* asset;
    char* location1;
    char* location2;
    
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
