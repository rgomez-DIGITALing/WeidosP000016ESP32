#pragma once

class AzureIoTDevice;
#include "AzureIoT_definitions.h"


void default_on_command_request_received(AzureIoTDevice* azureIoTDevice, command_request_t command);
int default_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command);


void gateway_on_command_request_received(AzureIoTDevice* azureIoTDevice, command_request_t command);
int gateway_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command);
void device_on_command_request_received(AzureIoTDevice* azureIoTDevice, command_request_t command);
int device_handle_command_request(AzureIoTDevice* azureIoTDevice, command_request_t command);
