#pragma once
#include <Arduino.h>
#include <Ethernet.h>
#include <ArduinoModbus.h>

enum DeviceType{
    NONE_DEVICE_TYPE,
    EM110_DEVICE_TYPE,
    EM111_DEVICE_TYPE,
    EM120_DEVICE_TYPE,
    EM122_DEVICE_TYPE,
    EM220_DEVICE_TYPE,
    EM750_DEVICE_TYPE,
    EA750_DEVICE_TYPE,
    EM120TCP_DEVICE_TYPE,
    EM122TCP_DEVICE_TYPE,
    EM220TCP_DEVICE_TYPE,
    PULSE_METER_DEVICE_TYPE,
    ANALOG_METER_DEVICE_TYPE,
    WEIDOS_ESP32
};

#define USING_WEB_SERVER //Comment this flag if configuration is not made via Web Server but with /config files

static const uint8_t MAX_DEVICE_TYPE = WEIDOS_ESP32;

static const uint8_t AZURE_SCOPE_ID_SIZE = 50;
static const uint8_t AZURE_ID_SIZE = 25;
static const uint8_t AZURE_SAS_KEY_SIZE = 60;
static const uint8_t RING_BUFFER_SIZE = 15;
static const uint8_t DEFAULT_MODBUS_NUMBER_TRIES = 5;

static const int MQTT_CLIENT_BUFFER_SIZE = 3000;
static const int  AZ_IOT_DATA_BUFFER_SIZE = 3000;
// #define AZ_IOT_DATA_BUFFER_SIZE 50
static const int  DATA_BUFFER_SIZE = 3000;

#ifdef USING_WEB_SERVER
//Clients to be used for all Modbus TCP
extern EthernetClient ethernetClientModbus;
extern ModbusTCPClient modbusTCPClient;
#endif
