#include "SystemConfigurator.h"
#include "../../collections/DeviceCollections/DeviceCollection.h"
#include "../../collections/DataHubCollection/DataHubCollection.h"
#include "../../collections/TriggerCollection/TriggerCollection.h"
#include "../PersistentData/PersistentDataClass.h"
#include "../../payloadGenerators/1phPayloadGenerators.h"
#include "../../payloadGenerators/3phPayloadGenerators.h"
#include "../../payloadGenerators/payloadGenerators.h"


void SystemConfiguratorClass::configure(){
    for(int i=0; i<MAX_ALLOWED_DEVICES; i++){
        int deviceType = DeviceCollection.getDeviceType(i);
        Serial.print("[SystemConfiguratorClass::configure] deviceType: ");
        Serial.println(deviceType);
        
        if(deviceType == EM110_DEVICE_TYPE){
            DataHub<em1phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em1phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em1ph_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == EM111_DEVICE_TYPE){
            DataHub<em1phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em1phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em1ph_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == EM120_DEVICE_TYPE){
            DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em3phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em3ph_basicLine_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == EM122_DEVICE_TYPE){
            DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em3phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em3ph_basicLine_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == EM220_DEVICE_TYPE){
            DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em3phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em3ph_basicLine_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == EM750_DEVICE_TYPE){
            DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em3phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em3ph_valueLine_generete_payload);
            if(PersistentDataModule.isHarmonicAnalysisActivated(i)) dataHub->setPayloadGenerator2(em3ph_harmonic_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == EA750_DEVICE_TYPE){
            DataHub<em3phManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<em3phManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(em3ph_valueLine_generete_payload);
            if(PersistentDataModule.isHarmonicAnalysisActivated(i)) dataHub->setPayloadGenerator2(em3ph_harmonic_generete_payload);
            DataHubCollection.setDataHub(dataHub, i);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
        if(deviceType == WEIDOS_ESP32){
            DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>* dataHub = new DataHub<WeidosManagerData_t, RING_BUFFER_SIZE>;
            dataHub->setPayloadGenerator(weidosESP32_generete_payload);
            DataHubCollection.setDataHub(dataHub);
            TriggerClass* trigger = new TriggerClass(i);
            TriggerCollection.setTrigger(trigger);
        }
    }

}

SystemConfiguratorClass SystemConfigurator;


// NONE_DEVICE_TYPE,
//     EM110_DEVICE_TYPE,
//     EM111_DEVICE_TYPE,
//     EM120_DEVICE_TYPE,
//     EM122_DEVICE_TYPE,
//     EM220_DEVICE_TYPE,
//     EM750_DEVICE_TYPE,
//     EA750_DEVICE_TYPE,
//     FLOW_METER_DEVICE_TYPE,
//     PULSE_METER_DEVICE_TYPE,
//     WEIDOS_ESP32