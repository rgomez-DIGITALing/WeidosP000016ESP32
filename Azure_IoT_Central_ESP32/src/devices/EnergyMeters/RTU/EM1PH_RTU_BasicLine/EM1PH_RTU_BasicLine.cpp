#include "EM1PH_RTU_BasicLine.h"


#include <ArduinoRS485.h>
#include <ArduinoModbus.h>

#define MODBUS_BAUDRATE     9600
#define MODBUS_CONFIG       SERIAL_8N1

#define MODBUS_TIMEOUT_BATCH_1      600
#define REG_ADDRESS_BATCH_1         0
#define NUM_REGISTERS_BATCH_1       80
#define NUM_DATA_BATCH_1            NUM_REGISTERS_BATCH_1/2

#define MODBUS_TIMEOUT_BATCH_2      100
#define REG_ADDRESS_BATCH_2         342
#define NUM_REGISTERS_BATCH_2       4
#define NUM_DATA_BATCH_2            NUM_REGISTERS_BATCH_2/2



// EM1PH_RTU_BasicLine::EM1PH_RTU_BasicLine(int modbusId, int ctPrimary, int ctSecondary) :  modbusId(modbusId), ctPrimary(ctPrimary), ctSecondary(ctSecondary), comError(COM_OK){
//   for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++) data[i] = 0;
// }



// EM1PH_RTU_BasicLine::EM1PH_RTU_BasicLine(){
//   for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++) data[i] = 0;
// }


EM1PH_RTU_BasicLine::EM1PH_RTU_BasicLine(uint8_t modbusId) : EM1PH_BaseClass(modbusId){
  for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++) data[i] = 0;
}


int EM1PH_RTU_BasicLine::begin(){
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);        //Set Weidos RS485 pins.
  if(ModbusRTUClient.begin(MODBUS_BAUDRATE, MODBUS_CONFIG)){
    comError = COM_OK;
    return 1;
  } 
  else{
    comError = COM_BEGIN_ERROR;
    return 0;
  }
}


void EM1PH_RTU_BasicLine::stop(){
  ModbusRTUClient.end();
  return;
}


int EM1PH_RTU_BasicLine::update(){
  ModbusRTUClient.setTimeout(MODBUS_TIMEOUT_BATCH_1);
  int response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_1, NUM_REGISTERS_BATCH_1);    
  if(response != NUM_REGISTERS_BATCH_1)
  {
      Serial.println("No response");
      Serial.print("Last error: ");
      Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_1_ERROR;
      return 0;
  }
  assignData();
  
  ModbusRTUClient.setTimeout(MODBUS_TIMEOUT_BATCH_2);
  response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_2, NUM_REGISTERS_BATCH_2);    
  if(response != NUM_REGISTERS_BATCH_2)
  {
      Serial.println("No response");
      Serial.print("Last error: ");
      Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_2_ERROR;
      return 0;
  }
  assignData2();
  

  computeValues();
  return 1;
}


// void EM1PH_RTU_BasicLine::validateData(){
//   for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++){
//     if(isnan(data[i])) data[i] = -1;
//   }
  
//   return;
// }


void EM1PH_RTU_BasicLine::assignData(){
  voltageL1N = getNextData();
  getNextData();
  getNextData();
  currentL1 = getNextData();
  getNextData();
  getNextData();
  realPowerL1N = getNextData();
  getNextData();
  getNextData();
  apparentPowerL1N = getNextData();
  getNextData();
  getNextData();
  reactivePowerL1N = getNextData();
  getNextData();
  getNextData();
  powerFactorL1N = getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  frequency = getNextData();
  realEnergyConsTotal = getNextData();
  realEnergyDelivTotal = getNextData();
  reactiveEnergyConsTotal = getNextData();
  reactiveEnergyDelivTotal = getNextData();
  return;
}


void EM1PH_RTU_BasicLine::assignData2(){
  realEnergyTotal = getNextData();
  reactiveEnergyTotal = getNextData();
  return;
}

/**
   Compute attributes that are not directly read from Modbus registers.
  */
void EM1PH_RTU_BasicLine::computeValues(){
  //apparentEnergyTotal = realEnergyTotal/powerFactorTotal;
  apparentEnergyTotal = sqrt(pow(realEnergyTotal,2) + pow(reactiveEnergyTotal,2));
  rotField = (powerFactorL1N>=0) ? rotField = 1 : rotField = -1;
  if(powerFactorL1N == 0.0f) rotField = 0;

  return;
}


float EM1PH_RTU_BasicLine::getNextData(){
    long msb = ModbusRTUClient.read();
    long lsb =  ModbusRTUClient.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData;
    return data;
}
