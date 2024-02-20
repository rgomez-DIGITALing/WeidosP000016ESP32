#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EM750Manager : public EM3PHManager_BaseClass{
    public:
    EM750Manager(ModbusTCPClient& client, IPAddress ip, int deviceId);
    ~EM750Manager();
    bool sendProperties();
};
