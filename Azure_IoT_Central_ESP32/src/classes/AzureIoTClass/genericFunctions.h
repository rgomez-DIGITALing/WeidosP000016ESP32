#pragma once

#include <Arduino.h>
#include <az_iot.h>
#include "AzureIoT_definitions.h"
//#include "../AzureIoTClass/AzureIoTClass.h"
/* --- Other Interface functions required by Azure IoT --- */



/*
 * See the documentation of `hmac_sha256_encryption_function_t` in AzureIoT.h for details.
 */
int eccx08_hmac_sha256(const uint8_t* key, size_t key_length, const uint8_t* payload, size_t payload_length, uint8_t* signed_payload, size_t signed_payload_size);

/*
 * See the documentation of `base64_decode_function_t` in AzureIoT.h for details.
 */
int base64_decode(
    uint8_t* data,
    size_t data_length,
    uint8_t* decoded,
    size_t decoded_size,
    size_t* decoded_length);

/*
 * See the documentation of `base64_encode_function_t` in AzureIoT.h for details.
 */
int base64_encode(
    uint8_t* data,
    size_t data_length,
    uint8_t* encoded,
    size_t encoded_size,
    size_t* encoded_length);

/*
 * See the documentation of `properties_update_completed_t` in AzureIoT.h for details.
 */
void on_properties_update_completed(uint32_t request_id, az_iot_status status_code);


/*
 * See the documentation of `properties_received_t` in AzureIoT.h for details.
 */
void on_properties_received(az_span properties);


//int azure_iot_send_command_response(azure_iot_t* azure_iot, az_span request_id, uint16_t response_status, az_span payload);


/*
 * See the documentation of `command_request_received_t` in AzureIoT.h for details.
 */
//void default_on_command_request_received(azure_iot_t* azure_iot, command_request_t command);
void default_on_command_request_received(AzureIoTDevice* azure_iot, command_request_t command);



//int default_handle_command_request(azure_iot_t* azure_iot, command_request_t command_request);
int default_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command_request);


/*
 * See the documentation of `command_request_received_t` in AzureIoT.h for details.
 */
void gateway_on_command_request_received(AzureIoTDevice* azure_iot, command_request_t command);
int gateway_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command);