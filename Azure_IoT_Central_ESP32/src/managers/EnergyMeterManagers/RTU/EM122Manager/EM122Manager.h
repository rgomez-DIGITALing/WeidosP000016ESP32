#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EM122Manager : public EM3PHManager_BaseClass{
    public:
    EM122Manager(uint8_t deviceId);
    ~EM122Manager();
    bool sendProperties();
};
