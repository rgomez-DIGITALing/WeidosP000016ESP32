#pragma once

#include "../../classes/DataHub/DataHub.h"
#include "../../managers/managers.h"
#include "../../globalDefinitions/globalConfiguration.h"



#define MAX_DATA_HUBS_ALLOWED 6
#define ENERGY_METER_RING_BUFFER_SIZE 15
#define ENERGY_METER_RING_BUFFER_SIZE 1
#define WEIDOS_METADATA_RING_BUFFER_SIZE 15


typedef int (*payloadGenerator3ph)(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, em3phManagerData_t& data);

class DataHubCollectionClass{
    

    public:
        void init();
        void push(WeidosManagerData_t data);
        void push(em1phManagerData_t data, int slot);
        void push(em3phManagerData_t data, int slot);
        void push(flowMeterManagerData_t data, int slot);
        void loop();

        void setDataHub(DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>* dataHub);
        void setDataHub(DataHub<em1phManagerData_t, RING_BUFFER_SIZE>* dataHub, int slot);
        void setDataHub(DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub, int slot);
        void setDataHub(DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE>* dataHub, int slot);

        void setDataHub(DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>& dataHub);
        void setDataHub(DataHub<em1phManagerData_t, RING_BUFFER_SIZE>& dataHub, int slot);
        void setDataHub(DataHub<em3phManagerData_t, RING_BUFFER_SIZE>& dataHub, int slot);
        void setDataHub(DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE>& dataHub, int slot);
        void setPayloadGenerator2(uint8_t slot, payloadGenerator3ph generatePayload);


    private:
    DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>* weidosDataHub;
    DataHub<em1phManagerData_t, RING_BUFFER_SIZE>* em1phDataHubPool[MAX_DATA_HUBS_ALLOWED];
    DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* em3phDataHubPool[MAX_DATA_HUBS_ALLOWED];
    DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE>* flowMeterDataHubPool[MAX_DATA_HUBS_ALLOWED];
};

extern DataHubCollectionClass DataHubCollection;
