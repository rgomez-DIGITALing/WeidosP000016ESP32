#include "PulseMeter.h"
#include <ClockModule.h>
#include <FunctionalInterrupt.h>
#include <functional>


PulseMeter::PulseMeter(int deviceId, int pinNumber, float convertionFactor) : deviceId(deviceId),
                                        interruptPin(pinNumber),
                                        convertionFactor(convertionFactor),
                                        periodCounter(0),
                                        totalCounter(0),
                                        _t0(0),
                                        _tf(0),
                                        error(FM_NO_ERROR),
                                        totalConsumption(0.0f),
                                        periodConsumption(0.0f),
                                        averageFlow(0.0f),
                                        t0(0),
                                        tf(0){}



bool PulseMeter::begin(){
    pinMode(interruptPin, INPUT_PULLUP); // input from wind meters rain gauge sensor
    _t0 = systemClock.getEpochTime();
    attachInterrupt(digitalPinToInterrupt(interruptPin), std::bind(&PulseMeter::counterISR,this), FALLING);
    if(_t0) return true;
    return false;
}


void PulseMeter::getData(flowMeterData_t& payload){
    payload.totalConsumption = totalConsumption;
    payload.periodConsumption = periodConsumption;
    payload.averageFlow = averageFlow;
    payload.t0 = t0;
    payload.tf = tf;
    payload.error = error;

    return;
}


bool PulseMeter::update(){
    _tf = systemClock.getEpochTime();
    totalConsumption = convertionFactor*totalCounter;
    periodConsumption = convertionFactor*periodCounter;

    error = FM_NO_ERROR;

    if((_tf-_t0) != 0) averageFlow = 60.0f*(periodConsumption/(float)(_tf-_t0));
    else{
        averageFlow = 0;
        error = FM_DEVIDE_BY_ZERO_ERROR;
    }
    t0 = _t0;
    tf = _tf;

    periodCounter = 0;
    _t0 = systemClock.getEpochTime();
    return true;
}


void IRAM_ATTR PulseMeter::counterISR(){
    periodCounter++;
    totalCounter++;
}
