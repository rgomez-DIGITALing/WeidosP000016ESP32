#include "DataHubCollection.h"

#include "../classes/DataHubCollection/DataHubCollection.h"


DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE> weidosDataHub;

DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub0;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;


void setDataHubCollection(){
    DataHubCollection.setDataHub(weidosDataHub);

    DataHubCollection.setDataHub(emDataHub0, 0);
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);

    return;
}


void setDataHubsPayloadGenerators(){
    weidosDataHub.setPayloadGenerator(weidosESP32_generete_payload);
    emDataHub0.setPayloadGenerator(em3ph_generete_payload);
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_generete_payload);
}