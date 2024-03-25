#pragma once
#include "../../devices/WeidosESP32Class/WeidosESP32Class.h"



enum WeidosState{
  WEIDOS_IDLE,
  WEIDOS_GET_DATA,
};



typedef struct WeidosManagerData_struct_t{
  int deviceId;
  unsigned long timestamp;
  int dataSourceStatus;
  weidosMetadata_t payload;
} WeidosManagerData_t;


class WeidosManager{
    public:
        WeidosManager(int deviceId);
        WeidosManager(WeidosESP32Class& weidos, int deviceId) : weidos(&weidos), deviceId(deviceId){}
        void triggerUpdate(){ state = WEIDOS_GET_DATA; }
        WeidosState loop();
        uint8_t getDeviceId() const { return deviceId; }
    private:
        WeidosESP32Class* weidos;
        WeidosState state = WEIDOS_IDLE;
        int deviceId;
};

extern WeidosManager weidosESP32Manager;