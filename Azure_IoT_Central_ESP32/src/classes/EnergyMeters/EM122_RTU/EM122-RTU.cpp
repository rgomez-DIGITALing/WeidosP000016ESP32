#include "EM122-RTU.h"
#include <ArduinoRS485.h>
#include <ArduinoModbus.h>



#define MODBUS_ADDRESS      1
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



EM122::EM122(int modbusId) :  modbusId(modbusId), comError(COM_OK){
  for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++) data[i] = 0;
}

int EM122::begin(){
  RS485.setPins(RS485_TX, RS485_DE, RS485_RE);        //Set Weidos RS485 pins.
  ModbusRTUClient.setTimeout(MODBUS_TIMEOUT);
  
  comError = COM_OK;
  if(ModbusRTUClient.begin(MODBUS_BAUDRATE, MODBUS_CONFIG)) return 1;

  comError = COM_BEGIN_ERROR;
  return 0;  
}

void EM122::stop(){
  ModbusRTUClient.end();
  return;
}

bool EM122::update(){
  

  int response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_1, NUM_REGISTERS_BATCH_1);    
  if(response != NUM_REGISTERS_BATCH_1)
  {
      Serial.println("No response");
      Serial.print("Last error: ");
      Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_1_ERROR;
      return false;
  }
  assignData();
  

  response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_2, NUM_REGISTERS_BATCH_2);    
  if(response != NUM_REGISTERS_BATCH_2)
  {
      Serial.println("No response");
      Serial.print("Last error: ");
      Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_2_ERROR;
      return false;
  }
  assignData2();


  response = ModbusRTUClient.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_3, NUM_REGISTERS_BATCH_3);    
  if(response != NUM_REGISTERS_BATCH_3)
  {
      Serial.println("No response");
      Serial.print("Last error: ");
      Serial.println(ModbusRTUClient.lastError());
      comError = COM_BATCH_3_ERROR;
      return false;
  }
  assignData3();
  
  computeValues();

  comError = COM_OK;
  return true;
}


void EM122::validateData(){
  for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++){
    if(isnan(data[i])) data[i] = -1;
  }
  
  return;
}


void EM122::copyData(float* buffer, int bufferSize){
  int length = (bufferSize<NUM_TOTAL_DATA_3PHASE) ? bufferSize : NUM_TOTAL_DATA_3PHASE;


  for(int i=0; i<length; i++){
    buffer[i] = data[i];
  }
  return;
};

void EM122::getData(em3phData_t& payload){
  payload.comError = comError;
  copyData(payload.data, NUM_TOTAL_DATA_3PHASE);
  return;
}


void EM122::assignData(){
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
  currentTotal = getNextData();
  getNextData();
  realPowerTotal = getNextData();
  getNextData();
  apparentPowerTotal = getNextData();
  getNextData();
  reactivePowerTotal = abs(getNextData());
  powerFactorTotal = getNextData();
  getNextData();
  avgCosPhi = cos(getNextData() * PI/180.0);
  getNextData();
  frequency = getNextData();
  return;
}

void EM122::assignData2(){
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
  THDCurrentL1N = getNextData();
  THDCurrentL2N = getNextData();
  THDCurrentL3N = getNextData();
  getNextData();
  avgTHDVoltsLN = getNextData();
  avgTHDCurrentLN = getNextData();
  return;
}

void EM122::assignData3(){
  THDVoltsL1L2 = getNextData(); 
  THDVoltsL2L3 = getNextData(); 
  THDVoltsL1L3 = getNextData(); 
  avgTHDVoltsLL = getNextData();
  realEnergyTotal = getNextData();
  reactiveEnergyTotal = getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  realEnergyL1 = getNextData();
  realEnergyL2 = getNextData();
  realEnergyL3 = getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  getNextData();
  reactiveEnergyL1 = getNextData();
  reactiveEnergyL2 = getNextData();
  reactiveEnergyL3 = getNextData();
  return;
}

void EM122::computeValues(){
  apparentEnergyL1 = sqrt(pow(realEnergyL1,2)+pow(reactiveEnergyL1,2));
  apparentEnergyL2 = sqrt(pow(realEnergyL2,2)+pow(reactiveEnergyL2,2));
  apparentEnergyL3 = sqrt(pow(realEnergyL3,2)+pow(reactiveEnergyL3,2));
  apparentEnergyTotal = apparentEnergyL1 + apparentEnergyL2 + apparentEnergyL3;
  rotField = (powerFactorTotal>0) ? rotField = 1 : rotField = -1 ;
  powerFactorTotal = abs(powerFactorTotal);
  return;
}

float EM122::getNextData(){
    long msb = ModbusRTUClient.read();
    long lsb =  ModbusRTUClient.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData; 
    return data;
}
