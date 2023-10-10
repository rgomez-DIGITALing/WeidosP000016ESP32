#pragma once

//#include "DataHub.h"
//#include "EM750.h"
//#include "classes/WeidosESP32Class/WeidosESP32Class.h"

#include <az_core.h>
#include <az_iot.h>

//#include "classes/EnergyMeterManager/energyMeterManager.h"
#include "classes/WeidosManager/WeidosManager.h"
#include "classes/EnergyMeterManagers/EMManagers.h"


// int em750_generete_payload(uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, energyMeterManagerData_t& data);


int em1ph_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, em1phManagerData_t& data);


int em3ph_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, em3phManagerData_t& data);
    

int weidosESP32_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, WeidosManagerData_t& data);


int em750_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM750* energyMeter);


int em110_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM110* energyMeter);

    
int em111_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM111* energyMeter);


int em120_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM120* energyMeter);


int em122_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM122* energyMeter);


int em220_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM220* energyMeter);
