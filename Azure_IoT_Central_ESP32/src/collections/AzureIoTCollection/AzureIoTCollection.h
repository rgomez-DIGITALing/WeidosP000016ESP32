#pragma once
#include "../../classes/AzureIoTClass/AzureIoTClass.h"
#include "../../globalDefinitions/globalConfiguration.h"

static const uint8_t MAX_NUM_AZURE_DEVICES = 6;

// static const uint8_t AZURE_DEVICE_ID_SIZE = 32;
// static const uint8_t AZURE_SAS_KEY_SIZE = 50;
// static const uint8_t AZURE_SCOPE_ID_SIZE = 50;

// extern uint8_t SCOPE_ID_MAX_LENGTH;
// extern uint8_t AZURE_ID_MAX_LENGTH;
// extern uint8_t AZURE_SAS_KEY_MAX_LENGTH;


typedef char AzureDeviceId[AZURE_ID_SIZE];
typedef char AzureSASKey[AZURE_SAS_KEY_SIZE];
typedef char ScopeId[AZURE_SCOPE_ID_SIZE];

class AzureIoTCollectionClass{
    public:
        void init();
        void configure();
        void createObjects();
        void setAzureIoTDevice(AzureIoTDevice* azureIoTDevice, int slot);
        void loop();
        void stop();
        char* getScopeId(){ return scopeId; }
        void restoreScopeId();
        void restoreAzureId(uint8_t slot);
        void restoreSasKey(uint8_t slot);

        void setAzureId(String& azureId, uint8_t slot);
        void setSasKey(String& sasKey, uint8_t slot);
        char* getAzureId(uint8_t slot){ return azureDeviceIds[slot]; };
        char* getSasKey(uint8_t slot){ return azureSasKeys[slot]; };

        AzureIoTDevice* operator[](int idx){ return AzureIoTPool[idx]; }


    private:
        AzureIoTDevice* AzureIoTPool[MAX_NUM_AZURE_DEVICES];

        AzureDeviceId azureDeviceIds[MAX_NUM_AZURE_DEVICES];
        AzureSASKey azureSasKeys[MAX_NUM_AZURE_DEVICES];
        ScopeId scopeId;

        bool scopeIdSet = false;
};

extern AzureIoTCollectionClass AzureIoTCollection;
