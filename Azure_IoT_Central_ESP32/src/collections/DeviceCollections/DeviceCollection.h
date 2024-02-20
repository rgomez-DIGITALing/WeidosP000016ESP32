#pragma once

#include "../../managers/EnergyMeterManagers/EMManagers.h"
#include "../../managers/managers.h"
#include "../../globalDefinitions/globalConfiguration.h"
//#include "../EnergyMeterManagers/EMManagers.h"



#define MAX_ALLOWED_DEVICES 6

// enum DeviceType{
//     NONE_DEVICE_TYPE,
//     EM110_DEVICE_TYPE,
//     EM111_DEVICE_TYPE,
//     EM120_DEVICE_TYPE,
//     EM122_DEVICE_TYPE,
//     EM220_DEVICE_TYPE,
//     FLOW_METER_DEVICE_TYPE,
//     PULSE_METER_DEVICE_TYPE
// };



class DeviceCollectionClass{
    public:
        DeviceCollectionClass();
        void init();
        // void setDevice(String& deviceTypeString, uint8_t slot);
        // String getEnergyMeterName(uint8_t slot);

        bool triggerUpdate(uint8_t slot);
        void loopDevices();
        void loopDevicesNoNetwork();
        void sendDevicesProperties();
        void initFlowMeters();

        void setDevice(WeidosManager& weidos);
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

        WeidosManager* weidosManager = nullptr;
        EM1PHManager_BaseClass* EM1PHPool[MAX_ALLOWED_DEVICES];
        EM3PHManager_BaseClass* EM3PHPool[MAX_ALLOWED_DEVICES];

        PulseMeterManager* PulseMeterPool[MAX_ALLOWED_DEVICES];
        AnalogMeterManager* AnalogMeterPool[MAX_ALLOWED_DEVICES];
};

extern DeviceCollectionClass DeviceCollection;
