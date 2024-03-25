#include "PersistentDataClass.h"

#define WIFI_SSID_SET_FLAG_INDEX                    FIRST_INDEX
#define WIFI_PASS_SET_FLAG_INDEX                    (WIFI_SSID_SET_FLAG_INDEX + FLAG_SIZE)
#define GATEWAY_DEVICE_ID_SET_FLAG_INDEX            (WIFI_PASS_SET_FLAG_INDEX + FLAG_SIZE)
//#define SCOPE_ID_SET_FLAG_INDEX                     (GATEWAY_DEVICE_ID_SET_FLAG_INDEX + FLAG_SIZE)



bool PersistentDataClass::begin(){
    E2PROM.begin();

    //WiFiSSID = "";
    //WiFiPass = "";

    // if(isWiFiSSIDSet()) restoreWiFiSSID();
    // if(isWiFiPassSet()) restoreWiFiPassword();
    // if(isScopeIdSet()) restoreScopeId();
    return true;
}

void PersistentDataClass::saveDeviceConfiguration(uint8_t deviceType, uint8_t slot){
    int index = DEVICE_CONFIGURATION_DATA_INDEX + slot;
    E2PROM.write(index, deviceType);
}

void PersistentDataClass::getDeviceConfiguration(uint8_t* devices, uint8_t numMaxDevices){
    for(int i =0; i<numMaxDevices; i++){
        devices[i] = E2PROM.read(DEVICE_CONFIGURATION_DATA_INDEX + i);
    }
    return;
}

// bool PersistentDataClass::isWiFiSSIDSet(){
//     bool wifiSsidNotSet = E2PROM.read(WIFI_SSID_SET_FLAG_INDEX);
//     return !wifiSsidNotSet;
// }

// bool PersistentDataClass::isWiFiPassSet(){
//     bool wifiPassNotSet = E2PROM.read(WIFI_PASS_SET_FLAG_INDEX);
//     return !wifiPassNotSet;
// }

// bool PersistentDataClass::isGatewayIdSet(){
//     return isDeviceIdSet(0);
// }


bool PersistentDataClass::isScopeIdSet(){
    bool scopeIdNotSet = E2PROM.read(SCOPE_ID_SET_FLAG_INDEX);
    return !(bool)scopeIdNotSet;
}

bool PersistentDataClass::isAzureIdSet(int slot){
    bool deviceIdNotSet = E2PROM.read(AZURE_DEVICE_ID_SET_FLAGS_INDEX + slot);
    return !(bool)deviceIdNotSet;
}

bool PersistentDataClass::isSasKeySet(int slot){
    bool sasKeyNotSet = E2PROM.read(AZURE_SAS_KEY_SET_FLAGS_INDEX + slot);
    return !(bool)sasKeyNotSet;
}

bool PersistentDataClass::isModbusAddressSet(int slot){
    bool modbussAddressNotSet = E2PROM.read(MODBUS_ID_SET_FLAGS_INDEX + slot);
    return !(bool)modbussAddressNotSet;
}

bool PersistentDataClass::isCTPrimarySet(int slot){
    bool ctPrimaryNotSet = E2PROM.read(CT_PRIMARY_SET_FLAGS_INDEX + slot);
    return !(bool)ctPrimaryNotSet;

}

bool PersistentDataClass::isCTSecondarySet(int slot){
    bool ctSecondaryNotSet = E2PROM.read(CT_SECONDARY_SET_FLAGS_INDEX + slot);
    return !(bool)ctSecondaryNotSet;
}

bool PersistentDataClass::isConversionSet(int slot){
    bool conversionFactorNotSet = E2PROM.read(CONVERSION_FACTOR_SET_FLAGS_INDEX + slot);
    return !(bool)conversionFactorNotSet;
}

bool PersistentDataClass::isIpAddressSet(int slot){
    bool tcpIpNotSet = E2PROM.read(MODBUS_TCP_IP_FLAGS_INDEX + slot);
    return !(bool)tcpIpNotSet;
}

bool PersistentDataClass::isDeviceTypeSet(int slot){
    bool deviceTypeNotSet = E2PROM.read(DEVICE_TYPE_SET_FLAGS_INDEX + slot);
    return !(bool)deviceTypeNotSet;
}


bool PersistentDataClass::isHarmonicAnalysisActivated(int slot){
    bool harmonicAnalisysNotSet = E2PROM.read(HARMONIC_ACTIVATED_FLAGS_INDEX + slot);
    return !(bool)harmonicAnalisysNotSet;
}



void PersistentDataClass::setHarmonicAnalysis(bool isActive, int slot){
    int index = HARMONIC_ACTIVATED_FLAGS_INDEX + slot*FLAG_SIZE;
    if(isActive) E2PROM.write(index, 0);
    if(!isActive) E2PROM.write(index, 255);

    return;
}

// void PersistentDataClass::setWiFiSSID(String& ssid){
//     ssid.toCharArray(WiFiSSID, WIFI_SSID_SIZE);
//     E2PROM.put(WIFI_SSID_INDEX, WiFiSSID);
//     E2PROM.write(WIFI_SSID_SET_FLAG_INDEX, 0);
//     return;
// }

// void PersistentDataClass::setWiFiPass(String& pass){
//     pass.toCharArray(WiFiPass, WIFI_PASS_SIZE);
//     E2PROM.put(WIFI_PASS_INDEX, WiFiPass);
//     E2PROM.write(WIFI_PASS_SET_FLAG_INDEX, 0);
//     return;
// }



// void PersistentDataClass:: saveDeviceConfiguration(uint8_t deviceType, uint8_t slot){
//     E2PROM.write(DEVICE_CONFIGURATION_DATA_INDEX + slot, deviceType);
//     return;
// }

// void PersistentDataClass::saveConversionFactor(int CF, uint8_t slot, bool primary){
//     E2PROM.put(EM_CONVERSION_FACTOR_INDEX + 8*slot + 4*primary, CF);
//     Serial.print("Saving CF: ");
//     Serial.println(CF);
//     return;
// }

// void PersistentDataClass::getConversionFactor(int& CF, uint8_t slot, bool primary){
//     E2PROM.get(EM_CONVERSION_FACTOR_INDEX + 8*slot + 4*primary, CF);
//     Serial.print("CF get from eeprom: ");
//     Serial.println(CF);
//     if(CF == -1) CF = 5;
//     return;
// }



void PersistentDataClass::saveScopeId(String& scopeId){
    char _scopeId[AZURE_SCOPE_ID_SIZE];
    scopeId.toCharArray(_scopeId, AZURE_SCOPE_ID_SIZE);
    for(int i=0; i<AZURE_SCOPE_ID_SIZE; i++){
        E2PROM.write(SCOPE_ID_INDEX + i , _scopeId[i]);
    }
    E2PROM.write(SCOPE_ID_SET_FLAG_INDEX, 0);
    return;
}

void PersistentDataClass::saveAzureId(String& azureId, int slot){
    int index = AZURE_DEVICE_IDS_INDEX + slot*AZURE_ID_SIZE;
    char _azureId[AZURE_ID_SIZE];
    azureId.toCharArray(_azureId, AZURE_ID_SIZE);
    for(int i=0; i<AZURE_ID_SIZE; i++){
        E2PROM.write(index+i ,_azureId[i]);
    }
    E2PROM.write(AZURE_DEVICE_ID_SET_FLAGS_INDEX + slot, 0);
    return;
}

void PersistentDataClass::saveAzureSasKey(String& sasKey, int slot){
    int index = AZURE_SAS_KEYS_INDEX + slot*AZURE_SAS_KEY_SIZE;
    char _sasKey[AZURE_SAS_KEY_SIZE];
    sasKey.toCharArray(_sasKey, AZURE_SAS_KEY_SIZE);
    for(int i=0; i<AZURE_SAS_KEY_SIZE; i++){
        E2PROM.write(index+i ,_sasKey[i]);
    }
    E2PROM.write(AZURE_SAS_KEY_SET_FLAGS_INDEX + slot, 0);
    return;
}

void PersistentDataClass::saveModbusAddress(int modbusAddress, int slot){
    int index = MODBUS_IDS_INDEX + slot;
    E2PROM.write(index, modbusAddress);

    index = MODBUS_ID_SET_FLAGS_INDEX + slot;
    E2PROM.write(index, 0);
    return;
}

void PersistentDataClass::saveCTPrimary(int ctPrimary, int slot){
    int index = CT_PRIMARY_INDEX + slot*INT_SIZE;
    E2PROM.put(index, ctPrimary);
    index = CT_PRIMARY_SET_FLAGS_INDEX + slot*FLAG_SIZE;
    E2PROM.write(index, 0);
    return;
}

void PersistentDataClass::saveCTSecondary(int ctSecondary, int slot){
    int index = CT_SECONDARY_INDEX + slot*INT_SIZE;
    E2PROM.put(index, ctSecondary);
    index = CT_SECONDARY_SET_FLAGS_INDEX + slot*FLAG_SIZE;
    E2PROM.write(index, 0);
    return;
}


void PersistentDataClass::saveConversionFactor(float conversionFactor, int slot){
    int index = CONVERSION_FACTOR_INDEX + slot*FLOAT_SIZE;
    E2PROM.put(index, conversionFactor);
    index = CONVERSION_FACTOR_SET_FLAGS_INDEX + slot*FLAG_SIZE;
    E2PROM.write(index, 0);
    return;
}

void PersistentDataClass::saveDeviceType(uint8_t deviceType, int slot){
    int index = DEVICE_CONFIGURATION_DATA_INDEX + slot*UINT8_T_SIZE;
    E2PROM.write(index, deviceType);
    index = DEVICE_TYPE_SET_FLAGS_INDEX + slot*FLAG_SIZE;
    E2PROM.write(index, 0);
    return;
}

void PersistentDataClass::saveIpAddress(String& ipAddressString, int slot){
    int index = MODBUS_TCP_IPS_INDEX + slot*IP_ADDRESS_SIZE;
    IPAddress ip;
    ip.fromString(ipAddressString);
    E2PROM.put(index, ip);

    index = MODBUS_TCP_IP_FLAGS_INDEX + slot*FLAG_SIZE;
    E2PROM.write(index, 0);
    return;
}





void PersistentDataClass::getScopeId(ScopeId scopeId){
    // if(!isScopeIdSet()){
    //     scopeId[0] = 'a';
    //     scopeId[1] = '\0';
    //     Serial.println("It is not set veus? Hhahahahah");
    //     return;
    // }

    for(int i = 0; i<AZURE_SCOPE_ID_SIZE; i++){
        char c = E2PROM.read(SCOPE_ID_INDEX + i);
        scopeId[i] = c;
        // Serial.print(c);
    }

    return;
}

void PersistentDataClass::getAzureId(AzureDeviceId azureId, int slot){
    int index = AZURE_DEVICE_IDS_INDEX + slot*AZURE_ID_SIZE;
    //E2PROM.get(index, deviceId);
    for(int i = 0; i<AZURE_ID_SIZE; i++){
        char c = E2PROM.read(index + i);
        azureId[i] = c;
        // Serial.print(c);
    }

    return;
}

void PersistentDataClass::getSasKey(AzureSASKey sasKey, int slot){
    int index = AZURE_SAS_KEYS_INDEX + slot*AZURE_SAS_KEY_SIZE;
    
    for(int i = 0; i<AZURE_SAS_KEY_SIZE; i++){
        char c = E2PROM.read(index + i);
        sasKey[i] = c;
        // Serial.print(c);
    }

    return;
}

uint8_t PersistentDataClass::getModbusAddress(int slot){
    int index = MODBUS_IDS_INDEX + slot;

    return (uint8_t)E2PROM.read(index);
}


int PersistentDataClass::getCTPrimary(int slot){
    int index = CT_PRIMARY_INDEX + slot*INT_SIZE;
    int ctPrimary = 0;
    E2PROM.get(index, ctPrimary);
    return ctPrimary;
}


int PersistentDataClass::getCTSecondary(int slot){
    int index = CT_SECONDARY_INDEX + slot*INT_SIZE;
    int ctSecondary = 0;
    E2PROM.get(index, ctSecondary);
    return ctSecondary;
}



float PersistentDataClass::getConversionFactor(int slot){
    int index = CONVERSION_FACTOR_INDEX + slot*FLOAT_SIZE;
    float conversionFactor = 0.0f;
    E2PROM.get(index, conversionFactor);
    return conversionFactor;
}


IPAddress PersistentDataClass::getIpAddress(int slot){
    int index = MODBUS_TCP_IPS_INDEX + slot*IP_ADDRESS_SIZE;
    IPAddress ip;
    E2PROM.get(index, ip);

    return ip;
}

PersistentDataClass PersistentDataModule;
