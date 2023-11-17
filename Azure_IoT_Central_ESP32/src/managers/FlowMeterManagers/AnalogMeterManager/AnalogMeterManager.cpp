#include "AnalogMeterManager.h"
#include <ClockModule.h>
#include "../../../collections/DataHubCollection/DataHubCollection.h"


AnalogMeterManager::AnalogMeterManager(int deviceId, int interruptPin, float convertionFactor) : deviceId(deviceId){
    analogMeter = new AnalogMeter(deviceId, interruptPin, convertionFactor);
}


AnalogMeterManager::~AnalogMeterManager(){
  delete analogMeter;
}

void AnalogMeterManager::triggerUpdate(){ 
  if(state == FLOW_METER_BEGIN) return;  
  state = UPDATE_FLOW_METER;
  return;
}


FlowMeterUpdateState_t AnalogMeterManager::loop(){
    analogMeter->loop();

    switch(state){
      case FLOW_METER_BEGIN:
        if(analogMeter->begin()) state = FLOW_METER_IDLE;
        break;
      case FLOW_METER_IDLE:
        break;

      case UPDATE_FLOW_METER:
        flowMeterManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        msg.backup = 0;
        analogMeter->update();
        analogMeter->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        state = FLOW_METER_IDLE;
        break;
    }

    return state;
}
