#pragma once
#include <Arduino.h>
#include <E2PROM.h>
#include "../../collections/DeviceCollections/DeviceCollection.h"
#include "../../collections/AzureIoTCollection/AzureIoTCollection.h"
#include "eepromMapping.h"

// static const int WIFI_SSID_SIZE = 32;
// static const int WIFI_PASS_SIZE = 63;
// static const int SCOPE_ID_SIZE = 20;
//static const int WEIDOS_MODEL_ID_SIZE = 63;
//static const int GATEWAY_DEVICE_ID_SIZE = 20;
//gatewayDeviceId, GATEWAY_DEVICE_ID_SIZE




class PersistentDataClass{
    public:
        bool begin();
        
        void saveDeviceConfiguration(uint8_t deviceType, uint8_t slot);
        void getDeviceConfiguration(uint8_t* devices,  uint8_t numMaxDevices);

        bool isScopeIdSet();
        bool isAzureIdSet(int slot);
        bool isSasKeySet(int slot);
        bool isModbusAddressSet(int slot);
        bool isCTPrimarySet(int slot);
        bool isCTSecondarySet(int slot);
        bool isConversionSet(int slot);
        bool isDeviceTypeSet(int slot);
        bool isIpAddressSet(int slot);
        bool isHarmonicAnalysisActivated(int slot);
        
        void setHarmonicAnalysis(bool isActive, int slot);
        
        void saveScopeId(String& scopeId);
        void saveAzureId(String& azureId, int slot);
        void saveAzureSasKey(String& sasKey, int slot);
        void saveModbusAddress(int modbusAddress, int slot);
        void saveCTPrimary(int ctPrimary, int slot);
        void saveCTSecondary(int ctSecondary, int slot);
        void saveConversionFactor(float conversionFactor, int slot);
        void saveDeviceType(uint8_t deviceType, int slot);
        void saveIpAddress(String& ipAddressString, int slot);
        


        void getScopeId(ScopeId scopeId);
        void getAzureId(AzureDeviceId azureId, int slot);
        void getSasKey(AzureSASKey sasKey, int slot);
        uint8_t getModbusAddress(int slot);
        int getCTPrimary(int slot);
        int getCTSecondary(int slot);
        float getConversionFactor(int slot);
        IPAddress getIpAddress(int slot);


    private:
        // char scopeId[SCOPE_ID_SIZE] = "";
};


extern PersistentDataClass PersistentDataModule;