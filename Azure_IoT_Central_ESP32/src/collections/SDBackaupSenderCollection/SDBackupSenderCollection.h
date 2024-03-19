#pragma once

#include "../../classes/SDBackupSender/SDBackupSender.h"
#include "../../managers/managers.h"



#define MAX_DATA_HUBS_ALLOWED 6
#define ENERGY_METER_RING_BUFFER_SIZE 15
// #define ENERGY_METER_RING_BUFFER_SIZE 1
#define WEIDOS_METADATA_RING_BUFFER_SIZE 15

class SDBackupSenderCollectionClass{
    public:
        void init();
        void loop();
        void begin();

        void setBackupSender(SDBackupSenderClass<WeidosManagerData_t>& sdBackupDataSender);
        void setBackupSender(SDBackupSenderClass<em1phManagerData_t>& sdBackupDataSender, int slot);
        void setBackupSender(SDBackupSenderClass<em3phManagerData_t>& sdBackupDataSender, int slot);
        void setBackupSender(SDBackupSenderClass<flowMeterManagerData_t>& sdBackupDataSender, int slot);
        

    private:
    SDBackupSenderClass<WeidosManagerData_t>* weidosBackupSender;
    SDBackupSenderClass<em1phManagerData_t>* em1phBackupSenderPool[MAX_DATA_HUBS_ALLOWED];
    SDBackupSenderClass<em3phManagerData_t>* em3phBackupSenderPool[MAX_DATA_HUBS_ALLOWED];
    SDBackupSenderClass<flowMeterManagerData_t>* flowMeterBackupSenderPool[MAX_DATA_HUBS_ALLOWED];
};

extern SDBackupSenderCollectionClass SDBackupSenderCollection;