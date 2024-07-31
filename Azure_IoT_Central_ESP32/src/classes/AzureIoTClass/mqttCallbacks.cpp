#include "mqttCallbacks.h"

#include "AzureIoTClass.h"
#include <Arduino.h>
#include <LogModule.h>
#include "../../collections/TriggerCollection/TriggerCollection.h"
#include "../../collections/DataHubCollection/DataHubCollection.h"
#include "../PersistentData/PersistentDataClass.h"
#include "../../payloadGenerators/3phPayloadGenerators.h"

#define COMMAND_RESPONSE_CODE_ACCEPTED 202
#define COMMAND_RESPONSE_CODE_REJECTED 404
bool jsonGetUint32(az_json_reader* json_reader, char* key, uint32_t& value);
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





void device_on_command_request_received(AzureIoTDevice* azureIoTDevice, command_request_t command){
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
  (void)device_handle_command_request(azureIoTDevice, command);
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
static az_span COMMAND_NAME_BOOST = AZ_SPAN_FROM_STR("changeTelemetryInterval");
static az_span COMMAND_NAME_CHANGE_TELEMETRY_INTERVAL = AZ_SPAN_FROM_STR("changeTelemetryInterval");
static az_span COMMAND_NAME_HARMONIC_ON = AZ_SPAN_FROM_STR("harmonicOn");
static az_span COMMAND_NAME_HARMONIC_OFF = AZ_SPAN_FROM_STR("harmonicOff");


int default_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command){
 uint16_t response_code;

 LogError( "Command not recognized (%.*s).", az_span_size(command.command_name), az_span_ptr(command.command_name));
 response_code = COMMAND_RESPONSE_CODE_REJECTED;
 
  azure_iot_t* azure_iot = azureIoTDevice->getAzureIoT();
 return azureIoTDevice->azure_iot_send_command_response(
     azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
}




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
  else if (az_span_is_content_equal(command.command_name, COMMAND_NAME_CHANGE_TELEMETRY_INTERVAL))
  {
    Serial.println("BOOST command has been recieved");
    Serial.print("Payload: ");
    Serial.println((char*)az_span_ptr(command.payload));

    az_json_reader out_json_reader;

    az_json_reader_init(&out_json_reader, command.payload, NULL);
  
    uint8_t slot = azureIoTDevice->getSlot();
    uint32_t frequency = 0;
    jsonGetUint32(&out_json_reader, "frequency", frequency);

    if(jsonGetUint32(&out_json_reader, "frequency", frequency)){
      Serial.print("Frequency out funciton: ");
      Serial.println(frequency);
    }

    uint32_t duration = 0;
    jsonGetUint32(&out_json_reader, "duration", duration);

    if(jsonGetUint32(&out_json_reader, "duration", duration)){
      Serial.print("Frequency out funciton: ");
      Serial.println(frequency);
    }



    if(frequency && duration){
      TriggerClass* trigger = TriggerCollection.getTrigger(slot);
      if(trigger) trigger->boost(frequency, duration);
    }
    else if(frequency){
      TriggerClass* trigger = TriggerCollection.getTrigger(slot);
      if(trigger) trigger->boost(frequency);
    }



    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
    azureIoTDevice->azure_iot_send_command_response(
      azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
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




int device_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command){
 //_az_PRECONDITION_NOT_NULL(azure_iot);
  azure_iot_t* azure_iot = azureIoTDevice->getAzureIoT();
  uint16_t response_code;
  uint8_t slot = azureIoTDevice->getSlot();

  if(az_span_is_content_equal(command.command_name, COMMAND_NAME_HARMONIC_ON)){
    DataHubCollection.setPayloadGenerator2(slot, em3ph_harmonic_generete_payload);
    PersistentDataModule.setHarmonicAnalysis(true, slot);
  } 
  else if(az_span_is_content_equal(command.command_name, COMMAND_NAME_HARMONIC_OFF)){
    DataHubCollection.setPayloadGenerator2(slot, nullptr);
    PersistentDataModule.setHarmonicAnalysis(false, slot);
  }
  else if (az_span_is_content_equal(command.command_name, COMMAND_NAME_CHANGE_TELEMETRY_INTERVAL))
  {
    Serial.println("BOOST command has been recieved");
    Serial.print("Payload: ");
    Serial.println((char*)az_span_ptr(command.payload));

    az_json_reader out_json_reader;

    uint32_t frequency = 0;
    az_json_reader_init(&out_json_reader, command.payload, NULL);
    jsonGetUint32(&out_json_reader, "telemetryInterval", frequency);
 

    uint32_t duration = 0;
    az_json_reader_init(&out_json_reader, command.payload, NULL);
    jsonGetUint32(&out_json_reader, "durationTelemetryInterval", duration);
    


    if(frequency && duration){
      Serial.println("Frequency and duration given");
      TriggerClass* trigger = TriggerCollection.getTrigger(slot);
      if(trigger) trigger->boost(frequency, duration);
    }
    else if(frequency){
      Serial.println("ONLY Frequency given");
      TriggerClass* trigger = TriggerCollection.getTrigger(slot);
      if(trigger) trigger->boost(frequency);
    }



    response_code = COMMAND_RESPONSE_CODE_ACCEPTED;
    azureIoTDevice->azure_iot_send_command_response(
      azure_iot, command.request_id, response_code, AZ_SPAN_EMPTY);
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





bool jsonGetUint32(az_json_reader* json_reader, char* key, uint32_t& value){
  az_json_token token = json_reader->token;
  Serial.print("Searching for key: ");
  Serial.println(key);
  bool keyReached = false;

  while(az_json_reader_next_token(json_reader) == AZ_OK){
    az_json_token token = json_reader->token;

    if(az_json_token_is_text_equal(&token, az_span_create_from_str(key))){
      Serial.println("Key found!!");
      keyReached = true;
      continue;
    }

    if(keyReached){
      if((token.kind == AZ_JSON_TOKEN_NUMBER)){
        az_json_token_get_uint32(&token, &value);
        Serial.print("Getting value: ");
        Serial.println(value);
        return true;
      }
    }
  }


  return false;
}
