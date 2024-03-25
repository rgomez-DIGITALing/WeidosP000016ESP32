#pragma once
#include "../../classes/Trigger/Trigger.h"


#define MAX_ALLOWED_DEVICES 6

class TriggerCollectionClass{
    public:
        void init();
        void configure();
        void loop(bool connectionUp);
        void setTrigger(TriggerClass& trigger);
        void setTrigger(TriggerClass* trigger);
        TriggerClass* getTrigger(int slot){ return triggers[slot]; }


    private:
        TriggerClass* triggers[MAX_ALLOWED_DEVICES];
};



extern TriggerCollectionClass TriggerCollection;
