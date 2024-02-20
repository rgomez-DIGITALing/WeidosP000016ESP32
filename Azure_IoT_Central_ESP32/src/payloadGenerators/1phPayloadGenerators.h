#pragma once

#include <az_core.h>
#include <az_iot.h>

#include "../managers/managers.h"


int em1ph_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, em1phManagerData_t& emData);