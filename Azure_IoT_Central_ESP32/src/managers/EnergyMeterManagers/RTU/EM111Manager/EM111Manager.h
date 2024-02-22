#pragma once
#include "../../EM1PH_Manager_BaseClass/EM1PH_Manager_BaseClass.h"


class EM111Manager : public EM1PHManager_BaseClass{
    public:
    EM111Manager(uint8_t deviceId);
    ~EM111Manager();
    bool sendProperties();
};
