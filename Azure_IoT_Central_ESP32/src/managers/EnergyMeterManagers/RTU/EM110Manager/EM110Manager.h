#pragma once
#include "../../EM1PH_Manager_BaseClass/EM1PH_Manager_BaseClass.h"


class EM110Manager : public EM1PHManager_BaseClass{
    public:
    EM110Manager(uint8_t deviceId);
    EM110Manager(uint8_t deviceId, int ctPrimary, int ctSecondary);
    ~EM110Manager();
    bool sendProperties();
};
