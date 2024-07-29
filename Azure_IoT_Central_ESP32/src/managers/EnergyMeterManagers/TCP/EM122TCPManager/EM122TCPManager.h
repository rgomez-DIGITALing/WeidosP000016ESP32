#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EM122TCPManager : public EM3PHManager_BaseClass{
    public:
    EM122TCPManager(ModbusTCPClient& client, IPAddress ip, int deviceId);
    ~EM122TCPManager();
    bool sendProperties();
};
