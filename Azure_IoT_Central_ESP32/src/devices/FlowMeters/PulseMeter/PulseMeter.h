#pragma once

#include <Arduino.h>
#include "../fmDataDefinition.h"
#include "../fm_telemetryDefinition.h"


class PulseMeter{
    public:
        PulseMeter(int deviceId, int pinNumber, float convertionFactor);


        void init();

        /**
         * Attach the interrupt and begin time and counter.
         */
        bool begin();

        void loop();
        
        void getData(flowMeterData_t& payload);


        bool update();

    private:
        /**
         *  Interrupt Service Routine to be called upon an interrupt. It
         * adds +1 to count and totalCounts.
         */
        int deviceId;
        int interruptPin;
        void IRAM_ATTR counterISR();
        float convertionFactor;
        volatile unsigned long periodCounter;
        volatile unsigned long totalCounter;
        unsigned long _t0;
        unsigned long _tf;
        volatile bool saveInSD = false;

        flowMeterInitError_t initError;
        flowMeterError_t error;
        float totalConsumption;
        float periodConsumption;
        float averageFlow;
        unsigned long t0;
        unsigned long tf;
};
