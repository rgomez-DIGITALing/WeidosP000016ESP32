#include "postDevice.h"
#include "handlerFunctions.h"
#include "../pages/devicesPage.h"
#include "../../../globalDefinitions/globalConfiguration.h"
#include "../../PersistentData/PersistentDataClass.h"
#include "../../../collections/DeviceCollections/DeviceCollection.h"

#include <ESPAsyncWebServer.h>

static const char* PARAMETER_SLOT = "slot";
static const char* PARAMETER_DEVICE_TYPE = "device";
static const char* PARAMETER_SCOPE_ID = "scopeId";
static const char* PARAMETER_AZURE_ID = "azureId";
static const char* PARAMETER_AZURE_SAS_KEY = "azureSasKey";
static const char* PARAMETER_MODBUS_ADDRESS = "modbusAddress";
static const char* PARAMETER_CT_PRIMARY = "ctPrimary";
static const char* PARAMETER_CT_SECONDARY = "ctSecondary";
static const char* PARAMETER_CONVERSION_FACTOR = "conversionFactor";
static const char* PARAMETER_DIGITAL_PIN = "digitalPin";
static const char* PARAMETER_ANALOG_PIN = "analogPin";
static const char* PARAMETER_IP_ADDRESS = "ipAddress";


static const float MIN_CT_PRIMARY = 0.0f;
static const float MAX_CT_PRIMARY = 50.0f;
static const float MIN_CT_SECONDARY = 0.0f;
static const float MAX_CT_SECONDARY = 50.0f;

static const float MIN_CONVERSION_FACTOR = -9999999999999.0f;
static const float MAX_CONVERSION_FACTOR = 99999999999.0f;

static const int MAX_DIGITAL_PIN_INDEX = 1;
static const int MIN_DIGITAL_PIN_INDEX = 4;
static const int MAX_ANALOG_PIN_INDEX = 1;
static const int MIN_ANALOG_PIN_INDEX = 4;

//static const char* PARAMETER_SLOT = "slot";

enum ERROR_MESSAGE_INDEX{
    NO_ERROR,
    UNDEFINED_SLOT,
    INVALID_SLOT,

    UNDEFINED_DEVICE_TYPE,
    INVALID_DEVICE_TYPE,
    
    UNDEFINED_SCOPE_ID,
    INVALID_SCOPE_ID,
    SCOPE_ID_MAX_LENGTH_REACHED,

    UNDEFINED_AZURE_ID,
    INVALID_AZURE_ID,
    AZURE_ID_MAX_LENGTH_REACHED,
    UNDEFINED_AZURE_SAS_KEY,
    INVALID_AZURE_SAS_KEY,
    AZURE_SAS_KEY_MAX_LENGTH_REACHED,

    UNDEFINED_MODBUS_ADDRESS,
    INVALID_MODBUS_ADDRESS,

    UNDEFINED_CT_PRIMARY,
    INVALID_CT_PRIMARY,
    UNDEFINED_CT_SECONDARY,
    INVALID_CT_SECONDARY,

    UNDEFINED_CONVERSION_FACTOR,
    INVALID_CONVERSION_FACTOR,

    UNDEFINED_DIGITAL_PIN,
    INVALID_DIGITAL_PIN,
    UNDEFINED_ANALOG_PIN,
    INVALID_ANALOG_PIN
};


char* ERROR_MESSAGE[] = {
    "",
    "Undefined slot",
    "Invalid selected Slot number",
    "Undefined Device type",
    "Invalid Device type",
    "Undefined Scope ID",
    "Invalid Scope ID",
    "Scope ID reached maximum length",
    "Undefined Azure ID",
    "Invalid Azure ID",
    "Azure ID reached maximum length",
    "Undefined Azure SAS Key",
    "Invalid Azure SAS Key",
    "Azure SAS Key reached maximum length",
    "Undefined Modbus Address",
    "Invalid Modbus Address",
    "Undefined CT Primary",
    "Invalid CT Primary",
    "Undefined CT Secondary",
    "Invalid CT Secondary",
    "Undefined Conversion Factor",
    "Invalid Conversion Factor",
    "Undefined Digital Pin",
    "Invalid Digital Pin",
    "Undefined Analog Pin",
    "Invalid Analog Pin"
};

void sendErrorPage(uint8_t errorNumber){
    Serial.println(ERROR_MESSAGE[errorNumber]);
    return;
}

void onDevicePost(AsyncWebServerRequest *request){
    Serial.println("POST request sent to the weidos by the user.");

    //Check Slot input
    uint8_t err = 0;
    err = checkSlot(request);
    if(err){
        sendErrorPage(err);
        return;
    }

    //Check Device Type
    err = checkDeviceType(request);
    if(err){
        sendErrorPage(err);
        return;
    }
    // uint8_t deviceType = getDeviceType(request);


    //Slot
    int slot = request->getParam(PARAMETER_SLOT)->value().toInt();
    //Device Type
    int deviceType = request->getParam(PARAMETER_DEVICE_TYPE, true)->value().toInt();
    Serial.print("The Device Type is: ");
    Serial.println(deviceType);
    // PersistentDataModule.saveDeviceType(deviceType, slot);


    err = checkDeviceParameters(request, deviceType);
    if(err){
        sendErrorPage(err);
        return;
    }
    Serial.println("All input values are OK. Let's save them on EEPROM");
    

    //Scope ID
    String scopeId = request->getParam(PARAMETER_SCOPE_ID, true)->value();
    PersistentDataModule.saveScopeId(scopeId);
    AzureIoTCollection.restoreScopeId();
    //Azure Device ID
    String azureId = request->getParam(PARAMETER_AZURE_ID, true)->value();
    AzureIoTCollection.setAzureId(azureId, slot);
    // PersistentDataModule.saveAzureId(azureId, slot);
    // AzureIoTCollection.restoreAzureId(slot);
    //Azure SAS Key
    String azureSasKey = request->getParam(PARAMETER_AZURE_SAS_KEY, true)->value();
    AzureIoTCollection.setSasKey(azureSasKey, slot);
        // PersistentDataModule.saveAzureSasKey(azureSasKey, slot);
        // AzureIoTCollection.restoreSasKey(slot);


    //Device Type
    Serial.print("Lets set in slot: ");
    Serial.print(slot);
    Serial.print("   deviceType: ");
    Serial.println(deviceType);
    // DeviceCollection.setDevice(slot, deviceType);
    DeviceCollection.setDevice(deviceType, slot);
    // PersistentDataModule.saveDeviceType(deviceType, slot);

    if(deviceType>=EM110_DEVICE_TYPE && deviceType<=EA750_DEVICE_TYPE){
        //Modbus Address
        String modbusAddressString = request->getParam(PARAMETER_MODBUS_ADDRESS, true)->value();
        int modbusAddress = modbusAddressString.toInt();
        PersistentDataModule.saveModbusAddress(modbusAddress, slot);
        //CT Primary
        String ctPrimaryString = request->getParam(PARAMETER_CT_PRIMARY, true)->value();
        int ctPrimary = ctPrimaryString.toInt();
        PersistentDataModule.saveCTPrimary(ctPrimary, slot);
        //CT Secondary
        String ctSecondaryString = request->getParam(PARAMETER_CT_SECONDARY, true)->value();
        int ctSecondary = ctSecondaryString.toInt();
        PersistentDataModule.saveCTSecondary(ctSecondary, slot);
    }

    if(deviceType==NONE_DEVICE_TYPE){
        PersistentDataModule.removeAzureId(slot);
        PersistentDataModule.removeSasKey(slot);
        PersistentDataModule.removeModbusAddress(slot);
        PersistentDataModule.removeCTPrimary(slot);
        PersistentDataModule.removeCTSecondary(slot);
        PersistentDataModule.removeDigitalPin(slot);
        PersistentDataModule.removeAnalogPin(slot);
        PersistentDataModule.removeConversion(slot);
        PersistentDataModule.removeDeviceType(slot);
        PersistentDataModule.removeIpAddress(slot);
        PersistentDataModule.removeHarmonicAnalysisActivated(slot);
    }

    if(deviceType == PULSE_METER_DEVICE_TYPE){
        String digitalPinString = request->getParam(PARAMETER_DIGITAL_PIN, true)->value();
        int digitalPin = digitalPinString.toInt();
        PersistentDataModule.saveDigitalPin(digitalPin, slot);

        String conversionFactorString = request->getParam(PARAMETER_CONVERSION_FACTOR, true)->value();
        float conversionFactor = conversionFactorString.toFloat();
        PersistentDataModule.saveConversionFactor(conversionFactor, slot);
    }

    if(deviceType == ANALOG_METER_DEVICE_TYPE){
        String analogPinString = request->getParam(PARAMETER_ANALOG_PIN, true)->value();
        int analogPin = analogPinString.toInt();
        PersistentDataModule.saveAnalogPin(analogPin, slot);

        String conversionFactorString = request->getParam(PARAMETER_CONVERSION_FACTOR, true)->value();
        float conversionFactor = conversionFactorString.toFloat();
        PersistentDataModule.saveConversionFactor(conversionFactor, slot);
    }


    if(deviceType>=EM750_DEVICE_TYPE && deviceType<=EM220TCP_DEVICE_TYPE){
        //Modbus Address
        String modbusAddressString = request->getParam(PARAMETER_MODBUS_ADDRESS, true)->value();
        int modbusAddress = modbusAddressString.toInt();
        PersistentDataModule.saveModbusAddress(modbusAddress, slot);
        //CT Primary
        String ctPrimaryString = request->getParam(PARAMETER_CT_PRIMARY, true)->value();
        int ctPrimary = ctPrimaryString.toInt();
        PersistentDataModule.saveCTPrimary(ctPrimary, slot);
        //CT Secondary
        String ctSecondaryString = request->getParam(PARAMETER_CT_SECONDARY, true)->value();
        int ctSecondary = ctSecondaryString.toInt();
        PersistentDataModule.saveCTSecondary(ctSecondary, slot);

        String ipAddressString = request->getParam(PARAMETER_IP_ADDRESS, true)->value();
        PersistentDataModule.saveIpAddress(ipAddressString, slot);
    }
    // //Modbus Address
    // String modbusAddressString = request->getParam(PARAMETER_MODBUS_ADDRESS, true)->value();
    // int modbusAddress = modbusAddressString.toInt();
    // PersistentDataModule.saveModbusAddress(modbusAddress, slot);
    // //CT Primary
    // String ctPrimaryString = request->getParam(PARAMETER_CT_PRIMARY, true)->value();
    // int ctPrimary = ctPrimaryString.toInt();
    // PersistentDataModule.saveCTPrimary(ctPrimary, slot);
    // //CT Secondary
    // String ctSecondaryString = request->getParam(PARAMETER_CT_SECONDARY, true)->value();
    // int ctSecondary = ctSecondaryString.toInt();
    // PersistentDataModule.saveCTSecondary(ctSecondary, slot);
    //Conversion Factor
    // String conversionFactorString = request->getParam(PARAMETER_CONVERSION_FACTOR, true)->value();
    // float conversionFactor = conversionFactorString.toFloat();
    // PersistentDataModule.saveConversionFactor(conversionFactor, slot);
    //IP Address
    

    // PersistentDataModule.saveConversionFactor(conversionFactor, slot);


    AsyncResponseStream *response = request->beginResponseStream("text/html");
    sendDeviceFormPage(response, slot);
    request->send(response);
}


uint8_t getDeviceType(AsyncWebServerRequest *request){
    return request->getParam(PARAMETER_DEVICE_TYPE, true)->value().toInt();
}




uint8_t checkDeviceParameters(AsyncWebServerRequest *request, uint8_t deviceType){
    uint8_t err = 0;


    
    err = checkScopeId(request);
    if(err){
        return err;
    }


    err = checkAzureId(request);
    if(err){
        return err;
    }

    err = checkAzureSasKey(request);
    if(err){
        return err;
    }

    

    switch (deviceType){
        case NONE_DEVICE_TYPE:
        break;
        case EM110_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM111_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM120_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM122_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM220_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM750_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EA750_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM120TCP_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM122TCP_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case EM220TCP_DEVICE_TYPE:
            err = checkModbusAddress(request);
            if(!err) err = checkCTPrimary(request);
            if(!err) err = checkCTSecondary(request);
            return 0;
        break;
        case PULSE_METER_DEVICE_TYPE:
            err = checkConversionFactor(request);
            if(!err) err = checkDigitalPin(request);
            return 0;
        break;
        case ANALOG_METER_DEVICE_TYPE:
            err = checkConversionFactor(request);
            if(!err) err = checkAnalogPin(request);
            return 0;
        break;
        case WEIDOS_ESP32:
            return 0;
        break;
    }
    return 0;
};



uint8_t checkSlot(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_SLOT, false)) return UNDEFINED_SLOT;
    int slot = request->getParam(PARAMETER_SLOT)->value().toInt();

    if(slot<0 || slot>MAX_DEVICE_TYPE) return INVALID_SLOT;
    return NO_ERROR;
};



uint8_t checkDeviceType(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_DEVICE_TYPE, true)) return UNDEFINED_DEVICE_TYPE;
    int deviceType = getDeviceType(request);
    if(deviceType<0 || deviceType>MAX_DEVICE_TYPE) return INVALID_DEVICE_TYPE;
    return NO_ERROR;
};

uint8_t checkScopeId(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_SCOPE_ID, true)) return UNDEFINED_SCOPE_ID;

    String scopeId = request->getParam(PARAMETER_SCOPE_ID, true)->value();
    if(scopeId.length()>AZURE_SCOPE_ID_SIZE) return SCOPE_ID_MAX_LENGTH_REACHED;
    Serial.print("[CheckScopeId] Scope ID:");
    Serial.println(scopeId);
    
    return NO_ERROR;
}


uint8_t checkAzureId(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_AZURE_ID, true)) return UNDEFINED_AZURE_ID;

    String azureId = request->getParam(PARAMETER_AZURE_ID, true)->value();
    if(azureId.length()>AZURE_ID_SIZE) return AZURE_ID_MAX_LENGTH_REACHED;
    Serial.print("[CheckAzureId] Azure ID:");
    Serial.println(azureId);
    
    return NO_ERROR;
}


uint8_t checkAzureSasKey(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_AZURE_SAS_KEY, true)) return UNDEFINED_AZURE_SAS_KEY;
    String azureSasKey = request->getParam(PARAMETER_AZURE_SAS_KEY, true)->value();
    if(azureSasKey.length()>AZURE_SAS_KEY_SIZE) return AZURE_SAS_KEY_MAX_LENGTH_REACHED;
    Serial.print("[CheckAzureId] Azure azureSasKey:");
    Serial.println(azureSasKey);
    
    return NO_ERROR;
}


uint8_t checkModbusAddress(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_MODBUS_ADDRESS, true)) return UNDEFINED_MODBUS_ADDRESS;
    String modbusAddressString = request->getParam(PARAMETER_MODBUS_ADDRESS, true)->value();
    int modbusAddress = modbusAddressString.toInt();
    Serial.print("[CheckModbusAddress] Modbus Address:");
    Serial.println(modbusAddress);
    if(modbusAddress<0 || modbusAddress>255) return INVALID_MODBUS_ADDRESS;
    
    
    return NO_ERROR;
}


uint8_t checkCTPrimary(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_CT_PRIMARY, true)) return UNDEFINED_CT_PRIMARY;
    String ctPrimaryString = request->getParam(PARAMETER_CT_PRIMARY, true)->value();
    float ctPrimary = ctPrimaryString.toFloat();
    Serial.print("[CheckModbusAddress] CT Primary:");
    Serial.println(ctPrimary);
    if(ctPrimary<MIN_CT_PRIMARY || ctPrimary>MAX_CT_PRIMARY) return INVALID_CT_PRIMARY;
    
    
    return NO_ERROR;
}

uint8_t checkCTSecondary(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_CT_SECONDARY, true)) return UNDEFINED_CT_SECONDARY;
    String ctSecondaryString = request->getParam(PARAMETER_CT_SECONDARY, true)->value();
    float ctSecondary = ctSecondaryString.toFloat();
    Serial.print("[CheckModbusAddress] CT Secondary:");
    Serial.println(ctSecondary);
    if(ctSecondary<MIN_CT_SECONDARY || ctSecondary>MAX_CT_SECONDARY) return INVALID_CT_SECONDARY;
    
    
    return NO_ERROR;
}


uint8_t checkConversionFactor(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_CONVERSION_FACTOR, true)) return UNDEFINED_CONVERSION_FACTOR;
    String conversionFactorString = request->getParam(PARAMETER_CONVERSION_FACTOR, true)->value();
    float conversionFactor = conversionFactorString.toFloat();
    Serial.print("[CheckConversionFactor] conversionFactor: ");
    Serial.println(conversionFactor);
    if(conversionFactor<MIN_CONVERSION_FACTOR || conversionFactor>MAX_CONVERSION_FACTOR) return INVALID_CONVERSION_FACTOR;
    
    
    return NO_ERROR;
}

uint8_t checkDigitalPin(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_DIGITAL_PIN, true)) return UNDEFINED_DIGITAL_PIN;
    String digitalPinString = request->getParam(PARAMETER_DIGITAL_PIN, true)->value();
    int digitalPin = digitalPinString.toInt();
    Serial.print("[checkDigitalPin] digitalPin: ");
    Serial.println(digitalPin);
    if(digitalPin<MIN_DIGITAL_PIN_INDEX || digitalPin>MAX_DIGITAL_PIN_INDEX) return INVALID_DIGITAL_PIN;
    
    
    return NO_ERROR;
}


uint8_t checkAnalogPin(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_ANALOG_PIN, true)) return UNDEFINED_ANALOG_PIN;
    String analogPinString = request->getParam(PARAMETER_ANALOG_PIN, true)->value();
    int analogPin = analogPinString.toInt();
    Serial.print("[checkAnalogPin] analogPin: ");
    Serial.println(analogPin);
    if(analogPin<MIN_ANALOG_PIN_INDEX || analogPin>MAX_ANALOG_PIN_INDEX) return INVALID_ANALOG_PIN;
    
    
    return NO_ERROR;
}
