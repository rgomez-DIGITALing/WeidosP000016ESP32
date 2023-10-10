#pragma once
#include "../AzureIoTClass/AzureIoTClass.h"


static const int NUM_AZURE_IOT_DEVICES = 6;

class AzureIoTCollectionClass{
    public:
        void init();
        void setAzureIoTDevice(AzureIoTDevice* azureIoTDevice, int slot);
        void loop();
        void stop();

        AzureIoTDevice* operator[](int idx){ return AzureIoTPool[idx]; }


    private:
        AzureIoTDevice* AzureIoTPool[NUM_AZURE_IOT_DEVICES];
};

extern AzureIoTCollectionClass AzureIoTCollection;
