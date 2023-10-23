#include "PulseMeterManager.h"
#include <ClockModule.h>
#include "../../collections/DataHubCollection/DataHubCollection.h"


PulseMeterManager::PulseMeterManager(int deviceId, int interruptPin, float convertionFactor) : deviceId(deviceId){
    pulseMeter = new PulseMeter(deviceId, interruptPin, convertionFactor);
}


PulseMeterManager::~PulseMeterManager(){
  delete pulseMeter;
}



PulseMeterUpdateState_t PulseMeterManager::loop(){
    switch(state){
      case PULSE_METER_IDLE:
        break;

      case UPDATE_PULSE_METER:
        flowMeterManagerData_t msg;
        msg.deviceId = deviceId;
        msg.timestamp = systemClock.getEpochTime();
        pulseMeter->update();
        pulseMeter->getData(msg.payload);
        LogInfo("Pushing data for device ID: %i", deviceId);
        DataHubCollection.push(msg, deviceId);
        state = PULSE_METER_IDLE;
        break;
    }
    return state;
}
