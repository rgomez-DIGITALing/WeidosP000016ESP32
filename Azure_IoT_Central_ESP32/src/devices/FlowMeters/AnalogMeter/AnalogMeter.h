#include <Arduino.h>

#include "../fmDataDefinition.h"
#include "../fm_telemetryDefinition.h"


class AnalogMeter{
    public:
        AnalogMeter(int deviceId, int pinNumber, float convertionFactor);

        void init();
        bool begin();
        void getData(flowMeterData_t& payload);
        bool update();
        void loop();



    private:
        void makeMeasure();
        
        int deviceId;
        int analogPin;
        int _invalidMeasures;
        bool begun;
        bool saveInSD = false;

        float convertionFactor;
        float _averageFlow;
        unsigned long _measureCounter;
        unsigned long _t0;
        unsigned long _tf;
        flowMeterError_t _error;
        unsigned long prevTime;

        int invalidMeasures;
        flowMeterError_t error;
        float totalConsumption;
        float periodConsumption;
        float averageFlow;
        unsigned long t0;
        unsigned long tf;
};
