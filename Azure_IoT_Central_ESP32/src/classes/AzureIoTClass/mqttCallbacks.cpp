#include "mqttCallbacks.h"

#include "AzureIoTClass.h"
#include <Arduino.h>
#include <LogModule.h>


#define COMMAND_RESPONSE_CODE_ACCEPTED 202
#define COMMAND_RESPONSE_CODE_REJECTED 404

/*
 * See the documentation of `command_request_received_t` in AzureIoT.h for details.
 */
void default_on_command_request_received(AzureIoTDevice* azureIoTDevice, command_request_t command)
{
  az_span component_name = az_span_size(command.component_name) == 0 ? AZ_SPAN_FROM_STR("") : command.component_name;
  Serial.print("Command received in device: ");
  Serial.println(azureIoTDevice->getDeviceId());

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
  (void)default_handle_command_request(azureIoTDevice, command);
}




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
void gateway_on_command_request_received(AzureIoTDevice* azureIoTDevice, command_request_t command)
{
  az_span component_name = az_span_size(command.component_name) == 0 ? AZ_SPAN_FROM_STR("") : command.component_name;
  Serial.print("Command received in device: ");
  Serial.println(azureIoTDevice->getDeviceId());

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
  (void)gateway_handle_command_request(azureIoTDevice, command);
}








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
