#pragma once

//#include "DataHub.h"
//#include "EM750.h"
//#include "classes/WeidosESP32Class/WeidosESP32Class.h"

#include <az_core.h>
#include <az_iot.h>

#include "classes/EnergyMeterManager/energyMeterManager.h"
#include "classes/WeidosManager/WeidosManager.h"


int em750_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, energyMeterManagerData_t& data);



int weidosESP32_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, WeidosManagerData_t& data);


int em750_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM750* energyMeter);
