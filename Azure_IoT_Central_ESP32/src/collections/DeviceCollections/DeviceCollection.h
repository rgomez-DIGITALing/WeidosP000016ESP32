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
        void beginPulseMeters();

        
        void setEnergyMeter(EM110Manager& em){ 
                int slot = em.getDeviceId();
                EM110Pool[slot] = &em;
            }
        void setEnergyMeter(EM111Manager& em){
                int slot = em.getDeviceId();
                EM111Pool[slot] = &em;
            }
        void setEnergyMeter(EM120Manager& em){
                int slot = em.getDeviceId();
                EM120Pool[slot] = &em;
            }
        void setEnergyMeter(EM122Manager& em){
                int slot = em.getDeviceId();
                EM122Pool[slot] = &em;
            }
        void setEnergyMeter(EM220Manager& em){
                int slot = em.getDeviceId();
                EM220Pool[slot] = &em;
            }
        void setEnergyMeter(EM750Manager& em){
                int slot = em.getDeviceId();
                EM750Pool[slot] = &em;
            }
        void setEnergyMeter(EA750Manager& em){
                int slot = em.getDeviceId();
                EA750Pool[slot] = &em;
            }
        void setEnergyMeter(PulseMeterManager& pulseMeter){
                int slot = pulseMeter.getDeviceId();
                PulseMeterPool[slot] = &pulseMeter;
            }

    private:
        EM110Manager* EM110Pool[MAX_ALLOWED_DEVICES];
        EM111Manager* EM111Pool[MAX_ALLOWED_DEVICES];
        EM120Manager* EM120Pool[MAX_ALLOWED_DEVICES];
        EM122Manager* EM122Pool[MAX_ALLOWED_DEVICES];
        EM220Manager* EM220Pool[MAX_ALLOWED_DEVICES];
        EM750Manager* EM750Pool[MAX_ALLOWED_DEVICES];
        EA750Manager* EA750Pool[MAX_ALLOWED_DEVICES];
        PulseMeterManager* PulseMeterPool[MAX_ALLOWED_DEVICES];
};

extern DeviceCollectionClass DeviceCollection;
