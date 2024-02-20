#pragma once
#include "../../EM1PH_Manager_BaseClass/EM1PH_Manager_BaseClass.h"


class EM110Manager : public EM1PHManager_BaseClass{
    public:
    EM110Manager(ModbusTCPClient& client, IPAddress ip, int deviceId);
    ~EM110Manager();
    bool sendProperties();
};
