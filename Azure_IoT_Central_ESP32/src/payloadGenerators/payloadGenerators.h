#pragma once

#include <az_core.h>
#include <az_iot.h>

#include "../managers/managers.h"
#include "1phPayloadGenerators.h"
#include "3phPayloadGenerators.h"

int flowMeter_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, flowMeterManagerData_t& data);


int weidosESP32_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, WeidosManagerData_t& data);




int em110_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM110Manager* energyMeter);
int em111_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM111Manager* energyMeter);
int em120_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM120Manager* energyMeter);
int em122_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM122Manager* energyMeter);
int em220_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM220Manager* energyMeter);
int em750_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM750Manager* emManager);
int ea750_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EA750Manager* emManager);
int em120Tcp_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM120TCPManager* emManager);
int em122Tcp_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM122TCPManager* emManager);
int em220Tcp_generete_properties(az_iot_hub_client const* hub_client, uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, EM220TCPManager* emManager);



















// int ea750_generete_properties(az_iot_hub_client const* hub_client,
//     uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, EA750* energyMeter);


// int em110_generete_properties(az_iot_hub_client const* hub_client,
//     uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, EM110* energyMeter);

    
// int em111_generete_properties(az_iot_hub_client const* hub_client,
//     uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, EM111* energyMeter);


// int em120_generete_properties(az_iot_hub_client const* hub_client,
//     uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, EM120* energyMeter);


// int em122_generete_properties(az_iot_hub_client const* hub_client,
//     uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, EM122* energyMeter);


// int em220_generete_properties(az_iot_hub_client const* hub_client,
//     uint8_t* payload_buffer,
//     size_t payload_buffer_size,
//     size_t* payload_buffer_length, EM220* energyMeter);
