#pragma once
#include <Arduino.h>
#include <E2PROM.h>
#include "../../collections/DeviceCollections/DeviceCollection.h"
#include "../../collections/AzureIoTCollection/AzureIoTCollection.h"
#include "eepromMapping.h"
static const int WIFI_SSID_SIZE = 32;
static const int WIFI_PASS_SIZE = 63;
//static const int SCOPE_ID_SIZE = 20;
//static const int WEIDOS_MODEL_ID_SIZE = 63;
//static const int GATEWAY_DEVICE_ID_SIZE = 20;
//gatewayDeviceId, GATEWAY_DEVICE_ID_SIZE




class PersistentDataClass{
    public:
        bool begin();
        
        // bool isWiFiSSIDSet();
        // bool isWiFiPassSet();
        
        // bool isGatewayIdSet();
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
        bool isHarmonicAnalysisActivated(int slot);
        
        void setHarmonicAnalysis(bool isActive, int slot);
        // char* getWiFiSSID(){ return WiFiSSID; };
        // char* getWiFiPass(){ return WiFiPass; };
        // char* getScopeId(){ return scopeId; };
        
        // void setWiFiSSID(String& ssid);
        // void setWiFiPass(String& pass);
        //void setScopeId(String& scopeId);

        // void saveConversionFactor(int CF, uint8_t slot, bool primary);
        // void getConversionFactor(int& CF, uint8_t slot, bool primary);
        
        void saveScopeId(String& scopeId);
        void saveAzureId(String& azureId, int slot);
        void saveAzureSasKey(String& sasKey, int slot);
        void saveModbusAddress(int modbusAddress, int slot);
        void saveCTPrimary(int ctPrimary, int slot);
        void saveCTSecondary(int ctSecondary, int slot);
        void saveConversionFactor(float conversionFactor, int slot);
        void saveDeviceType(uint8_t deviceType, int slot);
        


        void getAzureId(AzureDeviceId azureId, int slot);
        void getSasKey(AzureSASKey sasKey, int slot);
        void getScopeId(ScopeId scopeId);
        uint8_t getModbusAddress(int slot);
        int getCTPrimary(int slot);
        int getCTSecondary(int slot);
        float getConversionFactor(int slot);


    private:
        // void restoreWiFiSSID(){ E2PROM.get(WIFI_SSID_INDEX, WiFiSSID); };
        // void restoreWiFiPassword(){ E2PROM.get(WIFI_PASS_INDEX, WiFiPass); }
        // void restoreScopeId(){ E2PROM.get(SCOPE_ID_INDEX, scopeId); }
        
        // char WiFiSSID[WIFI_SSID_SIZE] = "";
        // char WiFiPass[WIFI_PASS_SIZE] = "";
        // char scopeId[SCOPE_ID_SIZE] = "";

//Azure parameters
        //char gatewayDeviceId[GATEWAY_DEVICE_ID_SIZE];
        //char scopeId[SCOPE_ID_SIZE];
        
        //char groupPrimaryKey[20];
        //char weidosModelId[20];
        //char em3BasicLineId[20];
        //char em1BasicLineId[20];
};


extern PersistentDataClass PersistentDataModule;