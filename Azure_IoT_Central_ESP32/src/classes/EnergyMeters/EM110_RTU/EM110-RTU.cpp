#include "EM110-RTU.h"
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>



#define MODBUS_ADDRESS      1
#define MODBUS_BAUDRATE     9600
#define MODBUS_CONFIG       SERIAL_8N1
#define MODBUS_TIMEOUT      5000

#define REG_ADDRESS_BATCH_1         0
#define NUM_REGISTERS_BATCH_1       72
#define NUM_DATA_BATCH_1            NUM_REGISTERS_BATCH_1/2

#define REG_ADDRESS_BATCH_2         342
#define NUM_REGISTERS_BATCH_2       4
#define NUM_DATA_BATCH_2            NUM_REGISTERS_BATCH_2/2



EM110::EM110(int modbusId, int ctPrimary, int ctSecondary) :  modbusId(modbusId), ctPrimary(ctPrimary), ctSecondary(ctSecondary), comError(COM_OK){
  for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++) data[i] = 0;
}

int EM110::begin(){
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);        //Set Weidos RS485 pins.
  ModbusRTUClient.setTimeout(MODBUS_TIMEOUT);
  if(ModbusRTUClient.begin(MODBUS_BAUDRATE, MODBUS_CONFIG)){
    comError = COM_OK;
    return 1;
  } 
  else{
    comError = COM_BEGIN_ERROR;
    return 0;
  }
}

void EM110::stop(){
  ModbusRTUClient.end();
  return;
}

bool EM110::update(){
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


void EM110::validateData(){
  for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++){
    if(isnan(data[i])) data[i] = -1;
  }
  
  return;
}


void EM110::copyData(float* buffer, int bufferSize){
  int length = (bufferSize<NUM_TOTAL_DATA_1PHASE) ? bufferSize : NUM_TOTAL_DATA_1PHASE;


  for(int i=0; i<length; i++){
    buffer[i] = data[i];
  }
  return;
};

void EM110::getData(em1phData_t& payload){
  payload.comError = comError;
  copyData(payload.data, NUM_TOTAL_DATA_1PHASE);
  return;
}



void EM110::assignData(){
  voltageL1N = getNextData();
  getNextData();
  getNextData();
  currentL1 = getNextData();
  getNextData();
  getNextData();
  realPowerTotal = getNextData();
  getNextData();
  getNextData();
  apparentPowerTotal = getNextData();
  getNextData();
  getNextData();
  reactivePowerTotal = getNextData();
  getNextData();
  getNextData();
  powerFactorTotal = getNextData();
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
  return;
}

void EM110::assignData2(){
  realEnergyTotal = getNextData();
  reactiveEnergyTotal = getNextData();
  return;
}

/**
   Compute attributes that are not directly read from Modbus registers.
  */
void EM110::computeValues(){
  //apparentEnergyTotal = realEnergyTotal/powerFactorTotal;
  apparentEnergyTotal = sqrt(pow(realEnergyTotal,2) + pow(reactiveEnergyTotal,2));
  rotField = (powerFactorTotal>=0) ? rotField = 1 : rotField = -1;
  powerFactorTotal = abs(powerFactorTotal);
  return;
}

float EM110::getNextData(){
    long msb = ModbusRTUClient.read();
    long lsb =  ModbusRTUClient.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData; 
    return data;
}