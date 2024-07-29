#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EM120Manager : public EM3PHManager_BaseClass{
    public:
    EM120Manager(uint8_t deviceId, int ctPrimary, int ctSecondary);
    ~EM120Manager();
    bool sendProperties();
};
