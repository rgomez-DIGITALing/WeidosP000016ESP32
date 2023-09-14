#include "genericFunctions.h"
#include "AzureIoTClass.h"
#include <LogModule.h>
#include <az_core.h>
#include <az_iot.h>
#include <az_precondition_internal.h>

// For hmac SHA256 encryption
#include <ECCX08.h>
#include <mbedtls/base64.h>
#include <mbedtls/md.h>
#include <mbedtls/sha256.h>



/* --- Other Interface functions required by Azure IoT --- */

/*
 * See the documentation of `hmac_sha256_encryption_function_t` in AzureIoT.h for details.
 */
int eccx08_hmac_sha256(const uint8_t* key, size_t key_length, const uint8_t* payload, size_t payload_length, uint8_t* signed_payload, size_t signed_payload_size)
{
  (void)signed_payload_size;

  // HMAC-SHA256 sign the signature with the decoded device key.
  ECCX08.begin();
  ECCX08.nonce(key);
  ECCX08.beginHMAC(0xFFFF);
  ECCX08.updateHMAC(payload, payload_length);
  ECCX08.endHMAC(signed_payload);
  
  return 0;
}

/*
 * See the documentation of `base64_decode_function_t` in AzureIoT.h for details.
 */
int base64_decode(
    uint8_t* data,
    size_t data_length,
    uint8_t* decoded,
    size_t decoded_size,
    size_t* decoded_length)
{
  return mbedtls_base64_decode(decoded, decoded_size, decoded_length, data, data_length);
}

/*
 * See the documentation of `base64_encode_function_t` in AzureIoT.h for details.
 */
int base64_encode(
    uint8_t* data,
    size_t data_length,
    uint8_t* encoded,
    size_t encoded_size,
    size_t* encoded_length)
{
  return mbedtls_base64_encode(encoded, encoded_size, encoded_length, data, data_length);
}

/*
 * See the documentation of `properties_update_completed_t` in AzureIoT.h for details.
 */
void on_properties_update_completed(uint32_t request_id, az_iot_status status_code)
{
  LogInfo("Properties update request completed (id=%d, status=%d)", request_id, status_code);
}





/*
 * See the documentation of `properties_received_t` in AzureIoT.h for details.
 */
void on_properties_received(az_span properties)
{
  LogInfo("Properties update received: %.*s", az_span_size(properties), az_span_ptr(properties));

  // It is recommended not to perform work within callbacks.
  // The properties are being handled here to simplify the sample.
  //if (azure_pnp_handle_properties_update(&azure_iot, properties, properties_request_id++) != 0)
  //{
  //  LogError("Failed handling properties update.");
  //}
}



// int azure_iot_send_command_response(
    // azure_iot_t* azure_iot,
    // az_span request_id,
    // uint16_t response_status,
    // az_span payload)
// {
  // _az_PRECONDITION_NOT_NULL(azure_iot);
  // _az_PRECONDITION_VALID_SPAN(request_id, 1, false);
// 
  // az_result azrc;
  // mqtt_message_t mqtt_message;
  // size_t topic_length;
  // int packet_id;
// 
  // mqtt_message.topic = azure_iot->data_buffer;
// 
  // azrc = az_iot_hub_client_commands_response_get_publish_topic(
      // &azure_iot->iot_hub_client,
      // request_id,
      // response_status,
      // (char*)az_span_ptr(mqtt_message.topic),
      // az_span_size(mqtt_message.topic),
      // &topic_length);
  // EXIT_IF_AZ_FAILED(azrc, RESULT_ERROR, "Failed to get the commands response topic.");
// 
  // mqtt_message.topic = az_span_slice(mqtt_message.topic, 0, topic_length + 1);
  // mqtt_message.payload = payload;
  // mqtt_message.qos = mqtt_qos_at_most_once;
// 
  // packet_id = azure_iot->config->mqtt_client_interface.mqtt_client_publish(
      // azure_iot->mqtt_client_handle, &mqtt_message);
// 
  // if (packet_id < 0)
  // {
    // azure_iot->state = azure_iot_state_error;
    // LogError(
        // "Failed publishing command response (%.*s).",
        // az_span_size(request_id),
        // az_span_ptr(request_id));
    // return RESULT_ERROR;
  // }
  // else
  // {
    // return RESULT_OK;
  // }
// }
// 


/*
 * See the documentation of `command_request_received_t` in AzureIoT.h for details.
 */
void default_on_command_request_received(AzureIoTDevice* azure_iot, command_request_t command)
{
  az_span component_name = az_span_size(command.component_name) == 0 ? AZ_SPAN_FROM_STR("") : command.component_name;
  Serial.print("Command received in device: ");
  Serial.println(azure_iot->getDeviceId());

  LogInfo(
      "Command request received (id=%.*s, component=%.*s, name=%.*s)",
      az_span_size(command.request_id),
      az_span_ptr(command.request_id),
      az_span_size(component_name),
      az_span_ptr(component_name),
      az_span_size(command.command_name),
      az_span_ptr(command.command_name));

  // Here the request is being processed within the callback that delivers the command request.
  // However, for production application the recommendation is to save `command` and process it
  // outside this callback, usually inside the main thread/task/loop.
  (void)default_handle_command_request(azure_iot, command);
}



//int default_handle_command_request(azure_iot_t* azure_iot, command_request_t command)
//{
//  _az_PRECONDITION_NOT_NULL(azure_iot);
//
//  uint16_t response_code;
//
//  LogError( "Command not recognized (%.*s).", az_span_size(command.command_name), az_span_ptr(command.command_name));
//  response_code = COMMAND_RESPONSE_CODE_REJECTED;
//  
//
//  return azure_iot_send_command_response(
//      azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
//}


int default_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command){
 //_az_PRECONDITION_NOT_NULL(azure_iot);

 uint16_t response_code;

 LogError( "Command not recognized (%.*s).", az_span_size(command.command_name), az_span_ptr(command.command_name));
 response_code = COMMAND_RESPONSE_CODE_REJECTED;
 
  azure_iot_t* azure_iot = azureIoTDevice->getAzureIoT();
 return azureIoTDevice->azure_iot_send_command_response(
     azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
}



/*
 * See the documentation of `command_request_received_t` in AzureIoT.h for details.
 */
void gateway_on_command_request_received(AzureIoTDevice* azure_iot, command_request_t command)
{
  az_span component_name = az_span_size(command.component_name) == 0 ? AZ_SPAN_FROM_STR("") : command.component_name;
  Serial.print("Command received in device: ");
  Serial.println(azure_iot->getDeviceId());

  LogInfo(
      "Command request received (id=%.*s, component=%.*s, name=%.*s)",
      az_span_size(command.request_id),
      az_span_ptr(command.request_id),
      az_span_size(component_name),
      az_span_ptr(component_name),
      az_span_size(command.command_name),
      az_span_ptr(command.command_name));

  // Here the request is being processed within the callback that delivers the command request.
  // However, for production application the recommendation is to save `command` and process it
  // outside this callback, usually inside the main thread/task/loop.
  (void)gateway_handle_command_request(azure_iot, command);
}



//int default_handle_command_request(azure_iot_t* azure_iot, command_request_t command)
//{
//  _az_PRECONDITION_NOT_NULL(azure_iot);
//
//  uint16_t response_code;
//
//  LogError( "Command not recognized (%.*s).", az_span_size(command.command_name), az_span_ptr(command.command_name));
//  response_code = COMMAND_RESPONSE_CODE_REJECTED;
//  
//
//  return azure_iot_send_command_response(
//      azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
//}


static bool DO0_state = false;
static bool DO1_state = false;
static bool DO2_state = false;
static bool DO3_state = false;



static az_span COMMAND_NAME_TOGGLE_D0_0 = AZ_SPAN_FROM_STR("DO_0");
static az_span COMMAND_NAME_TOGGLE_D0_1 = AZ_SPAN_FROM_STR("DO_1");
static az_span COMMAND_NAME_TOGGLE_D0_2 = AZ_SPAN_FROM_STR("DO_2");
static az_span COMMAND_NAME_TOGGLE_D0_3 = AZ_SPAN_FROM_STR("DO_3");
static az_span COMMAND_NAME_REBOOT = AZ_SPAN_FROM_STR("reboot");

int gateway_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command){
 //_az_PRECONDITION_NOT_NULL(azure_iot);
  azure_iot_t* azure_iot = azureIoTDevice->getAzureIoT();
  uint16_t response_code;

  if (az_span_is_content_equal(command.command_name, COMMAND_NAME_TOGGLE_D0_0))
  {
    DO0_state = !DO0_state;
    digitalWrite(DO_0, DO0_state);
    LogInfo("LED 1 state: %s", (DO0_state ? "ON" : "OFF"));
    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
  }
  else if (az_span_is_content_equal(command.command_name, COMMAND_NAME_TOGGLE_D0_1))
  {
    DO1_state = !DO1_state;
    digitalWrite(DO_1, DO1_state);
    LogInfo("LED 2 state: %s", (DO1_state ? "ON" : "OFF"));
    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
  }
  else if (az_span_is_content_equal(command.command_name, COMMAND_NAME_TOGGLE_D0_2))
  {
    DO2_state = !DO2_state;
    digitalWrite(DO_2, DO2_state);
    LogInfo("LED 2 state: %s", (DO2_state ? "ON" : "OFF"));
    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
  }
  else if (az_span_is_content_equal(command.command_name, COMMAND_NAME_TOGGLE_D0_3))
  {
    DO3_state = !DO3_state;
    digitalWrite(DO_3, DO3_state);
    LogInfo("LED 2 state: %s", (DO3_state ? "ON" : "OFF"));
    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
  }
  else if (az_span_is_content_equal(command.command_name, COMMAND_NAME_REBOOT))
  {
    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
    azureIoTDevice->azure_iot_send_command_response(
      azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
    ESP.restart();
  }
  else
  {
    LogError(
        "Command not recognized (%.*s).",
        az_span_size(command.command_name),
        az_span_ptr(command.command_name));
    response_code = COMMAND_RESPONSE_CODE_REJECTED;
  }

  return azureIoTDevice->azure_iot_send_command_response(
      azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
}
