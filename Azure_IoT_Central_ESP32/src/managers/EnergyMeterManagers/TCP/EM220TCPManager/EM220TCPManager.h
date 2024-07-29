#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EM220TCPManager : public EM3PHManager_BaseClass{
    public:
    EM220TCPManager(ModbusTCPClient& client, IPAddress ip, int deviceId);
    ~EM220TCPManager();
    bool sendProperties();
};
