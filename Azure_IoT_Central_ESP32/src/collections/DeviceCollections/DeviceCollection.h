#pragma once

#include "../../managers/EnergyMeterManagers/EMManagers.h"
#include "../../managers/managers.h"
#include "../../globalDefinitions/globalConfiguration.h"
//#include "../EnergyMeterManagers/EMManagers.h"



#define MAX_ALLOWED_DEVICES 6

// enum DeviceType{
//     NONE,
//     EM110,
//     EM111,
//     EM120,
//     EM122,
//     EM220,
//     EM750,
//     EA750,
//     FLOW_METER,
//     PULSE_METER
// };



class DeviceCollectionClass{
    public:
        DeviceCollectionClass();
        void init();
        void createDevices();
        void createDevice(uint8_t slot);
        // void setDevice(String& deviceTypeString, uint8_t slot);
        // String getEnergyMeterName(uint8_t slot);

        bool triggerUpdate(uint8_t slot);
        void loop();
        void sendDevicesProperties();
        void initFlowMeters();

        int getDeviceType(uint8_t slot);
        char* getDeviceName(uint8_t slot);
        bool isEnergyMeter(uint8_t slot);

        void setDevice(int deviceType, uint8_t slot);
        void setDevice(WeidosManager& weidos);
        void setDevice(WeidosManager* weidos);
        void setDevice(EM110Manager* em);
        void setDevice(EM111Manager* em);
        void setDevice(EM120Manager* em);
        void setDevice(EM122Manager* em);
        void setDevice(EM220Manager* em);
        void setDevice(EM750Manager* em);
        void setDevice(EA750Manager* em);

        void setDevice(PulseMeterManager& pulseMeter);
        void setDevice(AnalogMeterManager& analogMeter);

    private:
        // void createDeviceObjects();
        // void createObject(int deviceType, int slot);

        uint8_t deviceList[MAX_ALLOWED_DEVICES];

        // WeidosManager* weidosManager = nullptr;
        WeidosManager* weidosManagerPool[MAX_ALLOWED_DEVICES];
        EM1PHManager_BaseClass* EM1PHPool[MAX_ALLOWED_DEVICES];
        EM3PHManager_BaseClass* EM3PHPool[MAX_ALLOWED_DEVICES];

        PulseMeterManager* PulseMeterPool[MAX_ALLOWED_DEVICES];
        AnalogMeterManager* AnalogMeterPool[MAX_ALLOWED_DEVICES];
};

extern DeviceCollectionClass DeviceCollection;
