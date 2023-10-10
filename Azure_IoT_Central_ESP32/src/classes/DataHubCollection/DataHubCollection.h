#pragma once
#include "../DataHub/DataHub.h"
#include "../WeidosManager/WeidosManager.h"
#include "../EnergyMeterManagers/EMManagers.h"


#define MAX_DATA_HUBS_ALLOWED 6
#define ENERGY_METER_RING_BUFFER_SIZE 15
#define WEIDOS_METADATA_RING_BUFFER_SIZE 20

class DataHubCollectionClass{
    public:
        void init();
        void push(WeidosManagerData_t data);
        void push(em1phManagerData_t data, int slot);
        void push(em3phManagerData_t data, int slot);
        void loop();

        void setDataHub(DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE>& dataHub);
        void setDataHub(DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>& dataHub, int slot);
        void setDataHub(DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>& dataHub, int slot);
        

    private:
    DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE>* weidosDataHub;
    DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>* em1phDataHubPool[MAX_DATA_HUBS_ALLOWED];
    DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>* em3phDataHubPool[MAX_DATA_HUBS_ALLOWED];
};

extern DataHubCollectionClass DataHubCollection;
