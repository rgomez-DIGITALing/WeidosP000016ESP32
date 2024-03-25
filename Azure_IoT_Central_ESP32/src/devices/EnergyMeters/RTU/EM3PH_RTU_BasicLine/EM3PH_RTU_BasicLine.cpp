#include "EM3PH_RTU_BasicLine.h"
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>


#define MODBUS_BAUDRATE     9600
#define MODBUS_CONFIG       SERIAL_8N1
#define MODBUS_TIMEOUT      600

#define REG_ADDRESS_BATCH_1         0
#define NUM_REGISTERS_BATCH_1       72
#define NUM_DATA_BATCH_1            NUM_REGISTERS_BATCH_1/2

#define REG_ADDRESS_BATCH_2         200
#define NUM_REGISTERS_BATCH_2       52
#define NUM_DATA_BATCH_2            NUM_REGISTERS_BATCH_2/2 

#define REG_ADDRESS_BATCH_3         334
#define NUM_REGISTERS_BATCH_3       48
#define NUM_DATA_BATCH_3            NUM_REGISTERS_BATCH_1/2



EM3PH_RTU_BasicLine::EM3PH_RTU_BasicLine(uint8_t modbusId) : EM3PH_BaseClass(modbusId){}

int EM3PH_RTU_BasicLine::begin(){
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);        //Set Weidos RS485 pins.
  ModbusRTUClient.setTimeout(MODBUS_TIMEOUT);
  
  comError = COM_OK;
  if(ModbusRTUClient.begin(MODBUS_BAUDRATE, MODBUS_CONFIG)) return 1;

  comError = COM_BEGIN_ERROR;
  return 0;  
}

void EM3PH_RTU_BasicLine::stop(){
  ModbusRTUClient.end();
  return;
}

int EM3PH_RTU_BasicLine::update(){
  int response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_1, NUM_REGISTERS_BATCH_1);    
  if(response != NUM_REGISTERS_BATCH_1)
  {
      // Serial.println("No response");
      // Serial.print("Last error: ");
      // Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_1_ERROR;
      return false;
  }
  assignData();
  

  response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_2, NUM_REGISTERS_BATCH_2);    
  if(response != NUM_REGISTERS_BATCH_2)
  {
      // Serial.println("No response");
      // Serial.print("Last error: ");
      // Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_2_ERROR;
      return false;
  }
  assignData2();


  response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_3, NUM_REGISTERS_BATCH_3);    
  if(response != NUM_REGISTERS_BATCH_3)
  {
      // Serial.println("No response");
      // Serial.print("Last error: ");
      // Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_3_ERROR;
      return false;
  }
  assignData3();
  
  computeValues();

  comError = COM_OK;
  return true;
}



void EM3PH_RTU_BasicLine::assignData(){
  voltageL1N = getNextData();
  voltageL2N = getNextData();
  voltageL3N = getNextData();

  currentL1 = getNextData();
  currentL2 = getNextData();
  currentL3 = getNextData();

  realPowerL1N = getNextData();
  realPowerL2N = getNextData();
  realPowerL3N = getNextData();

  apparentPowerL1N = getNextData();
  apparentPowerL2N = getNextData();
  apparentPowerL3N = getNextData();

  reactivePowerL1N = getNextData();
  reactivePowerL2N = getNextData();
  reactivePowerL3N = getNextData();

  powerFactorL1N = getNextData();
  powerFactorL2N = getNextData();
  powerFactorL3N = getNextData();
  cosPhiL1 = cos(getNextData() * PI/180.0);
  cosPhiL2 = cos(getNextData() * PI/180.0);
  cosPhiL3 = cos(getNextData() * PI/180.0);
  avgVoltageLN = getNextData();

  getNextData();
  avgCurrentL = getNextData();
  // currentTotal = getNextData();
  phaseCurrentSum = getNextData();
  getNextData();
  realPowerTotal = getNextData();
  getNextData();
  apparentPowerTotal = getNextData();
  getNextData();
  reactivePowerTotal = getNextData();
  powerFactorTotal = getNextData();
  getNextData();
  cosPhiTotal = cos(getNextData() * PI/180.0);
  getNextData();
  frequency = getNextData();
  return;
}

void EM3PH_RTU_BasicLine::assignData2(){
  voltageL1L2 = getNextData();
  voltageL2L3 = getNextData();
  voltageL1L3 = getNextData();
  avgVoltageLL = getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  currentNeutral = getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  THDVoltsL1N = getNextData();
  THDVoltsL2N = getNextData();
  THDVoltsL3N = getNextData();
  THDCurrentL1 = getNextData();
  THDCurrentL2 = getNextData();
  THDCurrentL3 = getNextData();
  getNextData();
  avgTHDVoltsLN = getNextData();
  avgTHDCurrentL = getNextData();
  return;
}

void EM3PH_RTU_BasicLine::assignData3(){
  THDVoltsL1L2 = getNextData();
  THDVoltsL2L3 = getNextData();
  THDVoltsL1L3 = getNextData();

  avgTHDVoltsLL = getNextData();
  realEnergyTotal = getNextData();
  reactiveEnergyTotal = getNextData();
  
  realEnergyConsL1 = getNextData();
  realEnergyConsL2 = getNextData();
  realEnergyConsL3 = getNextData();
  realEnergyDelivL1 = getNextData();
  realEnergyDelivL2 = getNextData();
  realEnergyDelivL3 = getNextData();

  realEnergyL1 = getNextData();
  realEnergyL2 = getNextData();
  realEnergyL3 = getNextData();


  reactiveEnergyConsL1 = getNextData();
  reactiveEnergyConsL2 = getNextData();
  reactiveEnergyConsL3 = getNextData();
  reactiveEnergyDelivL1 = getNextData();
  reactiveEnergyDelivL2 = getNextData();
  reactiveEnergyDelivL3 = getNextData();

  reactiveEnergyL1 = getNextData();
  reactiveEnergyL2 = getNextData();
  reactiveEnergyL3 = getNextData();
  return;
}

void EM3PH_RTU_BasicLine::computeValues(){
  apparentEnergyL1 = sqrt(pow(realEnergyL1,2)+pow(reactiveEnergyL1,2));
  apparentEnergyL2 = sqrt(pow(realEnergyL2,2)+pow(reactiveEnergyL2,2));
  apparentEnergyL3 = sqrt(pow(realEnergyL3,2)+pow(reactiveEnergyL3,2));
  apparentEnergyTotal = apparentEnergyL1 + apparentEnergyL2 + apparentEnergyL3;
  rotField = (powerFactorTotal>0) ? rotField = 1 : rotField = -1 ;
  if(powerFactorTotal == 0.0f) rotField = 0;

  realEnergyConsTotalSum = realEnergyConsL1 + realEnergyConsL2 + realEnergyConsL3;
  realEnergyDelivTotalSum = realEnergyDelivL1 + realEnergyDelivL2 + realEnergyDelivL3;
  
  realEnergyAdjustedL1 = realEnergyL1;
  realEnergyAdjustedL2 = realEnergyL2;
  realEnergyAdjustedL3 = realEnergyL3;
  realEnergyAdjustedTotal = realEnergyTotal;


  return;
}

float EM3PH_RTU_BasicLine::getNextData(){
    long msb = ModbusRTUClient.read();
    long lsb =  ModbusRTUClient.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData;
    return data;
}


void EM3PH_RTU_BasicLine::updatePreviousValues(){
  prevRealEnergyAdjustedL1 = realEnergyL1;
  prevRealEnergyAdjustedL2 = realEnergyL2;
  prevRealEnergyAdjustedL3 = realEnergyL3;
  prevRealEnergyAdjustedTotal = realEnergyAdjustedTotal;
  prevApparentEnergyL1 = apparentEnergyL1;
  prevApparentEnergyL2 = apparentEnergyL2;
  prevApparentEnergyL3 = apparentEnergyL3;
  prevApparentEnergyTotal = apparentEnergyTotal;
  prevReactiveEnergyL1 = reactiveEnergyL1;
  prevReactiveEnergyL2 = reactiveEnergyL2;
  prevReactiveEnergyL3 = reactiveEnergyL3;
  prevReactiveEnergyTotal = reactiveEnergyTotal;

  

  prevDataAvailable = true;
}


void EM3PH_RTU_BasicLine::setSkipVariables(){
    realEnergyConsTotal = SKIP_DATA_VALUE;
    realEnergyDelivTotal = SKIP_DATA_VALUE;
    currentTotal = SKIP_DATA_VALUE;
    
    return;
}
