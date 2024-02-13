#pragma once

#include "AzureIoT_definitions.h"
#include <MQTTClient.h>
#include <Client.h>
#include "../../config/azure_parameters.h"

enum securityType_t{
    UNDEFINED,
    SAS_TOKEN,
    X509_CERTIFICATE
};

#define AZ_IOT_DATA_BUFFER_SIZE 3000
#define DATA_BUFFER_SIZE 5000

static const int MQTT_KEEP_ALIVE = 60;
static const int MQTT_TIMEOUT = 5000;


class AzureIoTDevice{
    public:
        AzureIoTDevice() : mqttClient(nullptr), client(nullptr){};
        AzureIoTDevice(uint8_t slot, MQTTClient& mqttClient, Client& client) : slot(slot), mqttClient(&mqttClient), client(&client){};
        AzureIoTDevice(uint8_t slot, MQTTClient& mqttClient, Client* client) : slot(slot), mqttClient(&mqttClient), client(client){};
        AzureIoTDevice(uint8_t slot, MQTTClient* mqttClient, Client* client) : slot(slot), mqttClient(mqttClient), client(client){};
        void loop();
        void stop();
        void init();
        bool sendDeviceInfo(){ return deviceInfoSent; }
        void isDeviceInfoSent(bool deviceInfoSent){ this->deviceInfoSent = deviceInfoSent; }
        azure_iot_status_t getStatus(){ return azure_iot_get_status(&azure_iot); }
        void setDeviceId(char* deviceId);
        char* getDeviceId(){ return (char*)az_span_ptr(azure_iot_config.dps_registration_id); }
        void setDpsScopeId(char* scopeId);
        void setModelId(char* modelId);
        void usingCertificate(char* certificate, char* privateKey);
        void usingSasToken(char* key);
        int sendMessage(az_span message);
        int sendProperties(az_span message);
        azure_iot_t* getAzureIoT(){ return &azure_iot; }
        void setDataBuffer(uint8_t* az_iot_data_buffer){ this->az_iot_data_buffer = az_iot_data_buffer; }
        void setDataBuffer2(uint8_t* data_buffer){ this->data_buffer = data_buffer; }
        uint8_t* getDataBuffer(){ return az_iot_data_buffer; }
        uint8_t* getDataBuffer2(){ return data_buffer; }
        void setClients(MQTTClient& mqttClient, Client& client){ this->mqttClient = &mqttClient; this->client = &client;}
        void setGatewayId(char* gatewayId){ this->gatewayId = gatewayId; }
        void setOnCommandReceived(command_request_received_t onCommandRequest){ azure_iot_config.on_command_request_received = onCommandRequest; }
        void statusChange();
        int azure_iot_send_command_response(azure_iot_t* azure_iot, az_span request_id, uint16_t response_status, az_span payload);
        uint8_t getSlot(){ return slot; }
    private:
        azure_iot_status_t prevState = azure_iot_connected;
        azure_iot_t azure_iot;
        azure_iot_config_t azure_iot_config;
        uint8_t* az_iot_data_buffer;
        uint8_t* data_buffer;

        uint8_t slot = 0;
        Client* client;
        MQTTClient* mqttClient = nullptr;
        bool deviceInfoSent = false;
        securityType_t securityType;
        char* gatewayId = nullptr;
        uint32_t properties_request_id = 0;
        

        int mqtt_client_init(mqtt_client_config_t* mqtt_client_config, mqtt_client_handle_t *mqtt_client_handle);
        int mqtt_client_subscribe(mqtt_client_handle_t mqtt_client_handle, az_span topic, mqtt_qos_t qos);
        int mqtt_client_publish(mqtt_client_handle_t mqtt_client_handle, mqtt_message_t* mqtt_message);
        int mqtt_client_deinit(mqtt_client_handle_t mqtt_client_handle);
        void onMessageReceived(String &topic, String &payload);
        void azure_iot_init(azure_iot_t* azure_iot, azure_iot_config_t* azure_iot_config);
        int azure_iot_start(azure_iot_t* azure_iot);
        int azure_iot_stop(azure_iot_t* azure_iot);
        azure_iot_status_t azure_iot_get_status(azure_iot_t* azure_iot);
        void azure_iot_do_work(azure_iot_t* azure_iot);
        int azure_iot_send_telemetry(azure_iot_t* azure_iot, az_span message);
        int azure_iot_send_properties_update(azure_iot_t* azure_iot, uint32_t request_id, az_span message);
        int azure_iot_mqtt_client_connected(azure_iot_t* azure_iot);
        int azure_iot_mqtt_client_disconnected(azure_iot_t* azure_iot);
        int azure_iot_mqtt_client_subscribe_completed(azure_iot_t* azure_iot, int packet_id);
        int azure_iot_mqtt_client_publish_completed(azure_iot_t* azure_iot, int packet_id);
        int azure_iot_mqtt_client_message_received(azure_iot_t* azure_iot, mqtt_message_t* mqtt_message);
        az_span generate_dps_register_custom_property(az_span model_id, az_span data_buffer, az_span* remainder);
};
