#pragma once
#include <ArduinoModbus.h>
#include "../EMDataDefinitions.h"
#include "../em_telemetryDefinition.h"



class EM1PH_BaseClass{
  public:
  EM1PH_BaseClass(){};
  EM1PH_BaseClass(IPAddress ip);
  EM1PH_BaseClass(uint8_t modbusId);
  EM1PH_BaseClass(uint8_t modbusId, IPAddress ip);

  virtual int begin() = 0;
  virtual void stop() = 0;
  virtual int update() = 0;

  void copyData(float* buffer, int bufferSize);
  void getData(em1phData_t& payload);
  void resetPrevValues(){ prevDataAvailable = false; }
  virtual void updatePreviousValues();

  // emType_t getEmType(){ return emType; }
  void setModbusId(uint8_t modbusId){ this->modbusId = modbusId; }
  uint8_t getModbusId(){ return modbusId; }

  IPAddress* getIpAddress(){ return &ipAddress; }

  protected:
    // emType_t emType = EM_NONE;
    uint8_t modbusId;
    IPAddress ipAddress;


    COM_error_t comError;
    
    float realEnergyConsTotal;
    float realEnergyDelivTotal;
    float reactiveEnergyConsTotal;
    float reactiveEnergyDelivTotal;

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

    //Incremental variables
    bool prevDataAvailable = false;
    float prevRealEnergyTotal;
    float prevApparentEnergyTotal;
    float prevReactiveEnergyTotal;
};
