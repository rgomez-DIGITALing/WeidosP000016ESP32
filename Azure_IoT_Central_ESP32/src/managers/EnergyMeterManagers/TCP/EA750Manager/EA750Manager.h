#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EA750Manager : public EM3PHManager_BaseClass{
    public:
    EA750Manager(ModbusTCPClient& client, IPAddress ip, int deviceId);
    ~EA750Manager();
    bool sendProperties();
};
