#include "EM1PH_BaseClass.h"



EM1PH_BaseClass::EM1PH_BaseClass(uint8_t modbusId) : modbusId(modbusId){}
EM1PH_BaseClass::EM1PH_BaseClass(IPAddress ip) : modbusId(1), ipAddress(ip){}
EM1PH_BaseClass::EM1PH_BaseClass(uint8_t modbusId, IPAddress ip) : modbusId(modbusId), ipAddress(ip){}


void EM1PH_BaseClass::copyData(float* buffer, int bufferSize){
  int length = (bufferSize<NUM_TOTAL_DATA_1PHASE) ? bufferSize : NUM_TOTAL_DATA_1PHASE;

  for(int i=0; i<length; i++){
    buffer[i] = data[i];
  }
  return;
};

void EM1PH_BaseClass::getData(em1phData_t& payload){
  payload.comError = comError;
  copyData(payload.data, NUM_TOTAL_DATA_1PHASE);

  payload.realEnergyConsTotal = realEnergyConsTotal;
  payload.realEnergyDelivTotal = realEnergyDelivTotal;
  payload.reactiveEnergyConsTotal = reactiveEnergyConsTotal;
  payload.reactiveEnergyDelivTotal = reactiveEnergyDelivTotal;

  for(int i=0; i<NUM_TOTAL_INCREMENTAL_DATA_1PHASE; i++){
      payload.incrementalData[i] = FLOAT_NO_PREV_DATA_AVAILABLE_ERROR_VALUE;
  }
  return;
}
