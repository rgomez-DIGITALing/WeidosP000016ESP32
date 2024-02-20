#pragma once

#include <az_core.h>
#include <az_iot.h>

#include "../managers/managers.h"


int em3ph_valueLine_generete_payload(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, em3phManagerData_t& emData);
int em3ph_basicLine_generete_payload(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, em3phManagerData_t& emData);
