#include "DataHubCollection.h"
#include "azure_parameters.h"
#include "../collections/DataHubCollection/DataHubCollection.h"
#include "../collections/SDBackaupSenderCollection/SDBackupSenderCollection.h"


DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE> weidosDataHub;


#if defined BATCH_TEST && defined EM750_TEST
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub5;
#endif

#if defined BATCH_TEST && defined RTU_TEST
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub5;
#endif


#if defined BATCH_TEST && defined FLOW_METER_TEST
DataHub<flowMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<flowMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;

SDBackupSenderClass<flowMeterManagerData_t> sdBackupSender1(1);
SDBackupSenderClass<flowMeterManagerData_t> sdBackupSender2(2);
#endif


#if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub5;
#endif

#if defined BATCH_TRANSELEVADORES_FAST
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
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


#ifdef BATCH_GAC_LETS_CONNECT
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
#endif

#ifdef BATCH_ELEVADOR
DataHub<em3phManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;

#endif

void setDataHubCollection(){
    DataHubCollection.setDataHub(weidosDataHub);

    #if defined BATCH_TEST && defined FLOW_METER_TEST
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    SDBackupSenderCollection.setBackupSender(sdBackupSender1, 1);
    SDBackupSenderCollection.setBackupSender(sdBackupSender2, 2);
    #endif

    #if defined BATCH_TEST && defined EM750_TEST
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    DataHubCollection.setDataHub(emDataHub5, 5);
    #endif

    #if defined BATCH_TEST && defined RTU_TEST
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    DataHubCollection.setDataHub(emDataHub5, 5);
    #endif


    #if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    DataHubCollection.setDataHub(emDataHub5, 5);
    #endif

    #if defined BATCH_TRANSELEVADORES_FAST
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
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

    #ifdef BATCH_GAC_LETS_CONNECT
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    #endif


    #ifdef BATCH_ELEVADOR
    DataHubCollection.setDataHub(emDataHub1, 1);
    #endif


    return;
}


void setDataHubsPayloadGenerators(){
    weidosDataHub.setPayloadGenerator(weidosESP32_generete_payload);

    #if defined BATCH_TEST && defined FLOW_METER_TEST
    emDataHub1.setPayloadGenerator(flowMeter_generete_payload);
    emDataHub2.setPayloadGenerator(flowMeter_generete_payload);
    sdBackupSender1.setPayloadGenerator(flowMeter_generete_payload);
    sdBackupSender2.setPayloadGenerator(flowMeter_generete_payload);
    #endif

    #if defined BATCH_TEST && defined EM750_TEST
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_valueLine_generete_payload);

    // emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    // emDataHub2.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    // emDataHub3.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    // emDataHub4.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    // emDataHub5.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    #endif


    #if defined BATCH_TEST && defined RTU_TEST
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em1ph_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    emDataHub4.setPayloadGenerator(em1ph_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_basicLine_generete_payload);
    #endif



    #if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_valueLine_generete_payload);

    emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    emDataHub2.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    emDataHub3.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    emDataHub4.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    emDataHub5.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    #endif

    #ifdef BATCH_TRANSELEVADORES_FAST
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    #endif


    #ifdef BATCH_LETS_CONNECT
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_basicLine_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    #endif

    #ifdef BATCH_IT_SOPORTE
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em1ph_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_basicLine_generete_payload);
    #endif

    #ifdef BATCH_BARCELONA_SAI
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em1ph_generete_payload);
    emDataHub3.setPayloadGenerator(em1ph_generete_payload);
    emDataHub4.setPayloadGenerator(em1ph_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_basicLine_generete_payload);
    #endif


    #ifdef BATCH_GAC_LETS_CONNECT
    emDataHub1.setPayloadGenerator(em1ph_generete_payload);
    emDataHub2.setPayloadGenerator(em1ph_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_basicLine_generete_payload);
    #endif


    #ifdef BATCH_ELEVADOR
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    #endif

    return;
}
