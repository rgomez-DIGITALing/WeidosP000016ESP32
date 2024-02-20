#pragma once
#include "../../EM1PH_Manager_BaseClass/EM1PH_Manager_BaseClass.h"


class EM111Manager : public EM1PHManager_BaseClass{
    public:
    EM111Manager(ModbusTCPClient& client, IPAddress ip, int deviceId);
    ~EM111Manager();
    bool sendProperties();
};
