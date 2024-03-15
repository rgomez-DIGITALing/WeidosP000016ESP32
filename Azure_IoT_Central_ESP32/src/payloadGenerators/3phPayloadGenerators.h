#pragma once

#include <az_core.h>
#include <az_iot.h>

#include "../managers/managers.h"


int em3ph_valueLine_generete_payload(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, em3phManagerData_t& emData);
int em3ph_basicLine_generete_payload(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, em3phManagerData_t& emData);
int em3ph_harmonic_generete_payload(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, em3phManagerData_t& emData);




int writeNormalData(az_json_writer& jw, em3phManagerData_t& emData);
int writeValueLineConsDelivData(az_json_writer& jw, em3phManagerData_t& emData);
int writeBasicLineConsDelivData(az_json_writer& jw, em3phManagerData_t& emData);
int writeAdjustedData(az_json_writer& jw, em3phManagerData_t& emData);
int writeIncrementalData(az_json_writer& jw, em3phManagerData_t& emData);
int writeHarmonicData(az_json_writer& jw, em3phManagerData_t& emData);
int writeBasicLineIncrementalData(az_json_writer& jw, em3phManagerData_t& emData);

int writeValueLineNullValues(az_json_writer& jw, em3phManagerData_t& emData);
int writeHarmonicNullValues(az_json_writer& jw, em3phManagerData_t& emData);
int writeBasicLineNullValues(az_json_writer& jw, em3phManagerData_t& emData);