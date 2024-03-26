#include "AnalogMeter.h"
#include <ClockModule.h>
#include <SDDataStorage.h>
#include "../../../classes/SDFolderManager/SDFolderManager.h"

static const unsigned long MEASURE_FREQUENCY = 100;

static const float ERROR_VOLTAGE = 2.0f;
static const float ERROR_VOLTAGE_TOLERANCE = -0.2f;

AnalogMeter::AnalogMeter(int deviceId, int pinNumber, float convertionFactor) : deviceId(deviceId),
                                        analogPin(pinNumber),
                                        convertionFactor(convertionFactor),
                                        _invalidMeasures(0),
                                        _averageFlow(0.0f),
                                        _measureCounter(0),
                                        _t0(0),
                                        _tf(0),
                                        _error(FM_NO_ERROR),
                                        prevTime(0),
                                        error(FM_NO_ERROR),
                                        totalConsumption(0.0f),
                                        periodConsumption(0.0f),
                                        averageFlow(0.0f),
                                        t0(0),
                                        tf(0)
                                        {}

void AnalogMeter::init(){
    char* filePath = SDFolderManager.setAnalogMeterFilePath(deviceId);
    Serial.print("Lets GET PulseMeter data in file: ");
    Serial.println(filePath);
    SDDataStorage.get(filePath, totalConsumption);
    Serial.print("Restored value: ");
    Serial.println(totalConsumption);
}


bool AnalogMeter::begin(){
    pinMode(analogPin, INPUT); // input from wind meters rain gauge sensor
    _t0 = systemClock.getEpochTime();
    Serial.print("Analog begin t0: ");
    Serial.println(_t0);
    if(_t0) return true;
    return false;
}


void AnalogMeter::loop(){
    if(millis()-prevTime > MEASURE_FREQUENCY){
        makeMeasure();
        prevTime = millis();
    }


    if(saveInSD){
        if(!SDFolderManager.createAnalogMeterFolder()){
            return;
        } 

        char* filePath = SDFolderManager.setAnalogMeterFilePath(deviceId);
        bool stored = SDDataStorage.put(filePath, totalConsumption);

        if(stored){
            saveTries = 0;
            saveInSD = false;
        }else{
            saveTries++;
        }

        if(saveTries == maxSaveTries){
            saveTries = 0;
            saveInSD = false;
        }
    }

    return;
}


void AnalogMeter::makeMeasure(){
    float voltage = analogRead(analogPin)*10.0f/4095.0f;
    float instantFlow = convertionFactor*voltage;
    
    if(voltage>(ERROR_VOLTAGE + ERROR_VOLTAGE_TOLERANCE)){
        _averageFlow += instantFlow;
        _measureCounter++;
        _error = FM_NO_ERROR;
    }else{
        _invalidMeasures++;
        _error = FM_VOLTAGE_ERROR;
    }
}

bool AnalogMeter::update(){
    _tf = systemClock.getEpochTime();


    if(_measureCounter != 0) _averageFlow /= (float)_measureCounter;
    else{
        _averageFlow = 0;
        _error = FM_DEVIDE_BY_ZERO_ERROR;
    }

    averageFlow = _averageFlow;
    periodConsumption = averageFlow*(_tf-_t0);
    totalConsumption += periodConsumption;
    invalidMeasures = _invalidMeasures;
    t0 = _t0;
    tf = _tf;
    error = _error;

    Serial.print("averageFlow: ");
    Serial.println(averageFlow);
    Serial.print("measureCounter: ");
    Serial.println(_measureCounter);
    Serial.print("invalidMeasures: ");
    Serial.println(invalidMeasures);


    //Reset variables
    _error = FM_NO_ERROR;
    _averageFlow = 0;
    _measureCounter = 0;
    _invalidMeasures = 0;
    _t0 = _tf;
    saveInSD = true;
    return true;
}


void AnalogMeter::getData(flowMeterData_t& payload){
    payload.totalConsumption = totalConsumption;
    payload.periodConsumption = periodConsumption;
    payload.averageFlow = averageFlow;
    payload.t0 = t0;
    payload.tf = tf;
    payload.error = error;

    
    Serial.print("totalConsumption: ");
    Serial.println(totalConsumption);
    Serial.print("periodConsumption: ");
    Serial.println(periodConsumption);
    Serial.print("averageFlow: ");
    Serial.println(averageFlow);
    Serial.print("t0: ");
    Serial.println(t0);
    Serial.print("tf: ");
    Serial.println(tf);
    Serial.print("error: ");
    Serial.println(error);
    return;
}
