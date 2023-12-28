#pragma once

#include "../../managers/EnergyMeterManagers/EMManagers.h"
#include "../../managers/managers.h"
//#include "../EnergyMeterManagers/EMManagers.h"



#define MAX_ALLOWED_DEVICES 6


class DeviceCollectionClass{
    public:
        void init();
        void triggerUpdateRTU();
        void triggerUpdateTCP();
        void loopDevices();
        void loopDevicesNoNetwork();
        void sendDevicesProperties();
        void initFlowMeters();

        void setDevice(WeidosManager& weidos);
        void setDevice(EM110Manager& em);
        void setDevice(EM111Manager& em);
        void setDevice(EM120Manager& em);
        void setDevice(EM122Manager& em);
        void setDevice(EM220Manager& em);
        void setDevice(EM750Manager& em);
        void setDevice(EA750Manager& em);
        void setDevice(PulseMeterManager& pulseMeter);
        void setDevice(AnalogMeterManager& analogMeter);

    private:
        WeidosManager* weidosManager = nullptr;
        EM110Manager* EM110Pool[MAX_ALLOWED_DEVICES];
        EM111Manager* EM111Pool[MAX_ALLOWED_DEVICES];
        EM120Manager* EM120Pool[MAX_ALLOWED_DEVICES];
        EM122Manager* EM122Pool[MAX_ALLOWED_DEVICES];
        EM220Manager* EM220Pool[MAX_ALLOWED_DEVICES];
        EM750Manager* EM750Pool[MAX_ALLOWED_DEVICES];
        EA750Manager* EA750Pool[MAX_ALLOWED_DEVICES];
        PulseMeterManager* PulseMeterPool[MAX_ALLOWED_DEVICES];
        AnalogMeterManager* AnalogMeterPool[MAX_ALLOWED_DEVICES];
};

extern DeviceCollectionClass DeviceCollection;
