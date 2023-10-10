#pragma once
#include <ArduinoModbus.h>
#include "../EMDataDefinitions.h"



class EM111{
  public:
    EM111(int modbusId);
  
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
    void getData(em1phData_t& payload);
    int getModusId(){ return modbusId; }

    void setIdentifier(char* identifier){ this->identifier = identifier; }
    void setAsset(char* asset){ this->asset = asset; }
    void setLocation1(char* location1){ this->location1 = location1; }
    void setLocation2(char* location2){ this->location2 = location2; }

    char* getIdentifier(){ return identifier; }
    char* getAsset(){ return asset; };
    char* getLocation1(){ return location1; }
    char* getLocation2(){ return location2; }
  
    
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
    char* identifier;
    char* asset;
    char* location1;
    char* location2;

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
};
