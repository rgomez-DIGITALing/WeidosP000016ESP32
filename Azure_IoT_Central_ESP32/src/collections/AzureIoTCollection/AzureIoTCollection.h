#pragma once
#include "../../classes/AzureIoTClass/AzureIoTClass.h"


static const uint8_t MAX_NUM_AZURE_DEVICES = 6;

static const uint8_t AZURE_DEVICE_ID_SIZE = 32;
static const uint8_t AZURE_SAS_KEY_SIZE = 50;
static const uint8_t AZURE_SCOPE_ID_SIZE = 50;

typedef char AzureDeviceId[AZURE_DEVICE_ID_SIZE];
typedef char AzureSASKey[AZURE_SAS_KEY_SIZE];
typedef char ScopeId[AZURE_SCOPE_ID_SIZE];

class AzureIoTCollectionClass{
    public:
        void init();
        void configure();
        void setAzureIoTDevice(AzureIoTDevice* azureIoTDevice, int slot);
        void loop();
        void stop();

        AzureIoTDevice* operator[](int idx){ return AzureIoTPool[idx]; }


    private:
        AzureIoTDevice* AzureIoTPool[MAX_NUM_AZURE_DEVICES];

        AzureDeviceId azureDeviceIds[MAX_NUM_AZURE_DEVICES];
        AzureSASKey azureSasKeys[MAX_NUM_AZURE_DEVICES];
        ScopeId scopeId;

        bool scopeIdSet = false;
};

extern AzureIoTCollectionClass AzureIoTCollection;
