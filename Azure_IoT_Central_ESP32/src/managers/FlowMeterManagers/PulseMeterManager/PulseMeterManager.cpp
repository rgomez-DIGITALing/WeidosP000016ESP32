#include "PulseMeterManager.h"
#include <ClockModule.h>
#include "../../../collections/DataHubCollection/DataHubCollection.h"


PulseMeterManager::PulseMeterManager(int deviceId, int interruptPin, float convertionFactor) : deviceId(deviceId){
    pulseMeter = new PulseMeter(deviceId, interruptPin, convertionFactor);
}


PulseMeterManager::~PulseMeterManager(){
  delete pulseMeter;
}

void PulseMeterManager::triggerUpdate(){ 
  if(state == FLOW_METER_BEGIN) return;  
  state = UPDATE_FLOW_METER;
  return;
}

FlowMeterUpdateState_t PulseMeterManager::loop(){
    pulseMeter->loop();
    switch(state){
      case FLOW_METER_BEGIN:
        if(pulseMeter->begin()) state = FLOW_METER_IDLE;
        break;
        
      case FLOW_METER_IDLE:
        break;

      case UPDATE_FLOW_METER:
        flowMeterManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        pulseMeter->update();
        pulseMeter->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        state = FLOW_METER_IDLE;
        break;
    }
    return state;
}
