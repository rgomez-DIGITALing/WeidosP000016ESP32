#pragma once
#include "../../EM3PH_Manager_BaseClass/EM3PH_Manager_BaseClass.h"


class EM220Manager : public EM3PHManager_BaseClass{
    public:
    EM220Manager(int deviceId);
    ~EM220Manager();
    bool sendProperties();
};
