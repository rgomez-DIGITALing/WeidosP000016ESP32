#include "DataHubCollection.h"
#include "azure_parameters.h"
#include "../collections/DataHubCollection/DataHubCollection.h"
#include "../collections/SDBackaupSenderCollection/SDBackupSenderCollection.h"
#include "../classes/PersistentData/PersistentDataClass.h"


#ifndef USING_WEB_SERVER
DataHub<WeidosManagerData_t, RING_BUFFER_SIZE> weidosDataHub;
// SDBackupSenderClass<WeidosManagerData_t> weidosBackupSender(0);


#if defined BATCH_TEST && defined EM750_TEST
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub5;

// SDBackupSenderClass<em3phManagerData_t> sdBackupSender1(1);
// SDBackupSenderClass<em3phManagerData_t> sdBackupSender2(2);
// SDBackupSenderClass<em3phManagerData_t> sdBackupSender3(3);
// SDBackupSenderClass<em3phManagerData_t> sdBackupSender4(4);
// SDBackupSenderClass<em3phManagerData_t> sdBackupSender5(5);
#endif

#if defined BATCH_TEST && defined RTU_TEST
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub5;
#endif


#if defined BATCH_TEST && defined FLOW_METER_TEST
DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<flowMeterManagerData_t, RING_BUFFER_SIZE> emDataHub2;

SDBackupSenderClass<flowMeterManagerData_t> sdBackupSender1(1);
SDBackupSenderClass<flowMeterManagerData_t> sdBackupSender2(2);
#endif


#if defined BATCH_GENERAL_ROBOT || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub5;
#endif

#if defined DEMO_COMERCIALES
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub5;
#endif


#if defined BATCH_TRANSELEVADORES_FAST
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
#endif



#ifdef BATCH_LETS_CONNECT
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
#endif

#ifdef BATCH_IT_SOPORTE
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
#endif

#ifdef BATCH_BARCELONA_SAI
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub5;
#endif


#ifdef BATCH_GAC_LETS_CONNECT
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
#endif

#ifdef BATCH_MONTACARGAS
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
#endif

#if defined HANDOVER_TEST
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub1;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub2;
DataHub<em3phManagerData_t, RING_BUFFER_SIZE> emDataHub3;
DataHub<em1phManagerData_t, RING_BUFFER_SIZE> emDataHub4;
#endif

void setDataHubCollection(){
    DataHubCollection.setDataHub(weidosDataHub);
    // SDBackupSenderCollection.setBackupSender(weidosBackupSender);

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

    // SDBackupSenderCollection.setBackupSender(sdBackupSender1, 1);
    // SDBackupSenderCollection.setBackupSender(sdBackupSender2, 2);
    // SDBackupSenderCollection.setBackupSender(sdBackupSender3, 3);
    // SDBackupSenderCollection.setBackupSender(sdBackupSender4, 4);
    // SDBackupSenderCollection.setBackupSender(sdBackupSender5, 5);
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

    #if defined DEMO_COMERCIALES
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


    #ifdef BATCH_MONTACARGAS
    DataHubCollection.setDataHub(emDataHub1, 1);
    #endif

    #ifdef HANDOVER_TEST
    DataHubCollection.setDataHub(emDataHub1, 1);
    DataHubCollection.setDataHub(emDataHub2, 2);
    DataHubCollection.setDataHub(emDataHub3, 3);
    DataHubCollection.setDataHub(emDataHub4, 4);
    #endif

    return;
}


void setDataHubsPayloadGenerators(){
    weidosDataHub.setPayloadGenerator(weidosESP32_generete_payload);
    // weidosBackupSender.setPayloadGenerator(weidosESP32_generete_payload);


    #if defined BATCH_TEST && defined FLOW_METER_TEST
    emDataHub1.setPayloadGenerator(flowMeter_generete_payload);
    emDataHub2.setPayloadGenerator(flowMeter_generete_payload);
    // sdBackupSender1.setPayloadGenerator(flowMeter_generete_payload);
    // sdBackupSender2.setPayloadGenerator(flowMeter_generete_payload);
    #endif

    #if defined BATCH_TEST && defined EM750_TEST
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_valueLine_generete_payload);

    if(PersistentDataModule.isHarmonicAnalysisActivated(1)){
        emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
        Serial.println("Harmonic is set for 1");
    } 
    if(PersistentDataModule.isHarmonicAnalysisActivated(2)){
        emDataHub2.setPayloadGenerator2(em3ph_harmonic_generete_payload);
        Serial.println("Harmonic is set for 2");
    } 
    if(PersistentDataModule.isHarmonicAnalysisActivated(3)){
        emDataHub3.setPayloadGenerator2(em3ph_harmonic_generete_payload);
        Serial.println("Harmonic is set for 3");
    } 
    if(PersistentDataModule.isHarmonicAnalysisActivated(4)){
        emDataHub4.setPayloadGenerator2(em3ph_harmonic_generete_payload);
        Serial.println("Harmonic is set for 4");
    } 
    if(PersistentDataModule.isHarmonicAnalysisActivated(5)){
        emDataHub5.setPayloadGenerator2(em3ph_harmonic_generete_payload);
        Serial.println("Harmonic is set for 5");
    }


    // sdBackupSender1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    // sdBackupSender2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    // sdBackupSender3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    // sdBackupSender4.setPayloadGenerator(em3ph_valueLine_generete_payload);
    // sdBackupSender5.setPayloadGenerator(em3ph_valueLine_generete_payload);
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

    if(PersistentDataModule.isHarmonicAnalysisActivated(1)) emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(2)) emDataHub2.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(3)) emDataHub3.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(4)) emDataHub4.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(5)) emDataHub5.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    #endif

    #if defined DEMO_COMERCIALES
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub4.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub5.setPayloadGenerator(em3ph_valueLine_generete_payload);

    if(PersistentDataModule.isHarmonicAnalysisActivated(1)) emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(2)) emDataHub2.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(3)) emDataHub3.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(4)) emDataHub4.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(5)) emDataHub5.setPayloadGenerator2(em3ph_harmonic_generete_payload);
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


    #ifdef BATCH_MONTACARGAS
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(1)) emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    #endif

    #if defined HANDOVER_TEST
    emDataHub1.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub2.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub3.setPayloadGenerator(em3ph_valueLine_generete_payload);
    emDataHub4.setPayloadGenerator(em1ph_generete_payload);

    if(PersistentDataModule.isHarmonicAnalysisActivated(1)) emDataHub1.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(2)) emDataHub2.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    if(PersistentDataModule.isHarmonicAnalysisActivated(3)) emDataHub3.setPayloadGenerator2(em3ph_harmonic_generete_payload);
    #endif

    return;
}

#endif
