#include "EM3PH_BaseClass.h"



EM3PH_BaseClass::EM3PH_BaseClass(uint8_t modbusId) : modbusId(modbusId){}
EM3PH_BaseClass::EM3PH_BaseClass(IPAddress ip) : modbusId(1), ipAddress(ip){}
EM3PH_BaseClass::EM3PH_BaseClass(uint8_t modbusId, IPAddress ip) : modbusId(modbusId), ipAddress(ip){}


void EM3PH_BaseClass::copyData(float* buffer, int bufferSize){
  int length = (bufferSize<NUM_TOTAL_DATA_3PHASE) ? bufferSize : NUM_TOTAL_DATA_3PHASE;


  for(int i=0; i<length; i++){
    buffer[i] = data[i];
  }
  return;
};



void EM3PH_BaseClass::getData(em3phData_t& payload){
  payload.comError = comError;
  copyData(payload.data, NUM_TOTAL_DATA_3PHASE);
  
  for(int i=0; i<NUM_TOTAL_CONS_DELIV_DATA_3PHASE; i++){
    payload.consDelivData[i] = consDelivData[i];
  }

  for(int i=0; i<NUM_TOTAL_ADJUSTED_DATA_3PHASE; i++){
    payload.adjustedData[i] = adjustedData[i];
  }

  for(int i=0; i<NUM_TOTAL_HARMONIC_DATA_3PHASE; i++){
    payload.harmonicData[i] = harmonicData[i];
  }


  if(prevDataAvailable){
    payload.incrementalRealEnergyAdjustedL1 = realEnergyAdjustedL1 - prevRealEnergyAdjustedL1;
    payload.incrementalRealEnergyAdjustedL2 = realEnergyAdjustedL2 - prevRealEnergyAdjustedL2;
    payload.incrementalRealEnergyAdjustedL3 = realEnergyAdjustedL3 - prevRealEnergyAdjustedL3;
    payload.incrementalRealEnergyAdjustedTotal = realEnergyAdjustedTotal - prevRealEnergyAdjustedTotal;

    payload.incrementalApparentEnergyL1 = apparentEnergyL1 - prevApparentEnergyL1;
    payload.incrementalApparentEnergyL2 = apparentEnergyL2 - prevApparentEnergyL2;
    payload.incrementalApparentEnergyL3 = apparentEnergyL3 - prevApparentEnergyL3;
    payload.incrementalApparentEnergyTotal = apparentEnergyTotal - prevApparentEnergyTotal;

    payload.incrementalReactiveEnergyL1 = reactiveEnergyL1 - prevReactiveEnergyL1;
    payload.incrementalReactiveEnergyL2 = reactiveEnergyL2 - prevReactiveEnergyL2;
    payload.incrementalReactiveEnergyL3 = reactiveEnergyL3 - prevReactiveEnergyL3;
    payload.incrementalReactiveEnergyTotal = reactiveEnergyTotal - prevReactiveEnergyTotal;
  }else{
    for(int i=0; i<NUM_TOTAL_INCREMENTAL_DATA_3PHASE; i++){
      payload.incrementalData[i] = FLOAT_NO_PREV_DATA_AVAILABLE_ERROR_VALUE;
    }
  }

  payload.currentTotal = currentTotal;
  payload.phaseCurrentSum = phaseCurrentSum;
  
  return;
}



void EM3PH_BaseClass::updatePreviousValues(){
  prevRealEnergyAdjustedL1 = realEnergyAdjustedL1;
  prevRealEnergyAdjustedL2 = realEnergyAdjustedL2;
  prevRealEnergyAdjustedL3 = realEnergyAdjustedL3;
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



// void EM3PH_BaseClass::skipHarmonics(){
//   for(int i=0; i<NUM_TOTAL_HARMONIC_DATA_3PHASE; i++){
//     harmonicData[i] = SKIP_DATA_VALUE;
//   }
// }
