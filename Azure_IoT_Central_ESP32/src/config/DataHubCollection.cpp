#include "DataHubCollection.h"
#include "azure_parameters.h"
#include "../collections/DataHubCollection/DataHubCollection.h"


DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE> weidosDataHub;


#if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS || defined BATCH_TEST 
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub5;
#endif


#ifdef BATCH_LETS_CONNECT
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
#endif

#ifdef BATCH_IT_SOPORTE
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
#endif

#ifdef BATCH_BARCELONA_SAI
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub5;
#endif

void setDataHubCollection(){
    DataHubCollection.setDataHub(weidosDataHub);


    #if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS  || defined BATCH_TEST
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    DataHubCollection.setDataHub(emDataHub5, 5);
    #endif

    #ifdef BATCH_LETS_CONNECT
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    #endif

    #ifdef BATCH_IT_SOPORTE
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    #endif

    #ifdef BATCH_BARCELONA_SAI
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    DataHubCollection.setDataHub(emDataHub5, 5);
    #endif

    
    return;
}


void setDataHubsPayloadGenerators(){
    weidosDataHub.setPayloadGenerator(weidosESP32_generete_payload);

    #if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS || defined BATCH_TEST
    emDataHub1.setPayloadGenerator(em3ph_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_generete_payload);
    #endif

    #ifdef BATCH_LETS_CONNECT
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    #endif

    #ifdef BATCH_IT_SOPORTE
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em1ph_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_generete_payload);
    #endif

    #ifdef BATCH_BARCELONA_SAI
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em1ph_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    emDataHub4.setPayloadGenerator(em1ph_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_generete_payload);
    #endif

    return;
}