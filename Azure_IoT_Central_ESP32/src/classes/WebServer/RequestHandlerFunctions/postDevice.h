#pragma once
#include <ESPAsyncWebServer.h>


uint8_t checkDeviceParameters(AsyncWebServerRequest *request, uint8_t deviceType);

uint8_t checkSlot(AsyncWebServerRequest *request);
uint8_t checkDeviceType(AsyncWebServerRequest *request);
uint8_t checkScopeId(AsyncWebServerRequest *request);
uint8_t checkAzureId(AsyncWebServerRequest *request);
uint8_t checkAzureSasKey(AsyncWebServerRequest *request);
uint8_t checkModbusAddress(AsyncWebServerRequest *request);
uint8_t checkCTPrimary(AsyncWebServerRequest *request);
uint8_t checkCTSecondary(AsyncWebServerRequest *request);
uint8_t checkConversionFactor(AsyncWebServerRequest *request);
uint8_t checkDigitalPin(AsyncWebServerRequest *request);
uint8_t checkAnalogPin(AsyncWebServerRequest *request);




uint8_t checkUserParameters(AsyncWebServerRequest *request);
uint8_t getDeviceType(AsyncWebServerRequest *request);