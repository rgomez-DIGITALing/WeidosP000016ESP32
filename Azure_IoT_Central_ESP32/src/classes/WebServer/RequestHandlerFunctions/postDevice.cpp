#include "postDevice.h"
#include "handlerFunctions.h"
#include "../pages/devicesPage.h"
#include "../../../globalDefinitions/globalConfiguration.h"

#include <ESPAsyncWebServer.h>

static const char* PARAMETER_SLOT = "slot";
static const char* PARAMETER_DEVICE_TYPE = "device";
static const char* PARAMETER_AZURE_ID = "azureId";
static const char* PARAMETER_AZURE_SAS_KEY = "azureSasKey";
//static const char* PARAMETER_SLOT = "slot";

enum ERROR_MESSAGE_INDEX{
    NO_ERROR,
    UNDEFINED_SLOT,
    INVALID_SLOT,

    UNDEFINED_DEVICE_TYPE,
    INVALID_DEVICE_TYPE,
    
    UNDEFINED_AZURE_ID,
    INVALID_AZURE_ID,
    AZURE_ID_MAX_LENGTH_REACHED,
    UNDEFINED_AZURE_SAS_KEY,
    INVALID_AZURE_SAS_KEY,
    AZURE_SAS_KEY_MAX_LENGTH_REACHED
};


char* ERROR_MESSAGE[] = {
    "",
    "Undefined slot",
    "Invalid selected slot number",
    "Undefined device type",
    "Invalid device type",
    "Undefined Azure ID",
    "Invalid Azure ID",
    "Azure ID reached maximum length",
    "Undefined Azure SAS Key",
    "Invalid Azure SAS Key",
    "Azure SAS Key reached maximum length"
};

void sendErrorPage(uint8_t errorNumber){
    Serial.println(ERROR_MESSAGE[errorNumber]);
    Serial.println("Algo hi ha");
    return;
}

void onDevicePost(AsyncWebServerRequest *request){
    Serial.println("POST request sent to the weidos by the user.");

    uint8_t err = 0;
    err = checkSlot(request);
    if(err){
        sendErrorPage(err);
        return;
    }


    err = checkDeviceType(request);
    if(err){
        sendErrorPage(err);
        return;
    }
    uint8_t deviceType = getDeviceType(request);


    Serial.println("Let' schek all parameters noi=?");
    err = checkDeviceParameters(request, deviceType);
    if(err){
        sendErrorPage(err);
        return;
    }

    Serial.println("Que?");




    AsyncResponseStream *response = request->beginResponseStream("text/html");
    sendDeviceFormPage(response);
    request->send(response);

}


uint8_t getDeviceType(AsyncWebServerRequest *request){
    return request->getParam(PARAMETER_DEVICE_TYPE, true)->value().toInt();
}




uint8_t checkDeviceParameters(AsyncWebServerRequest *request, uint8_t deviceType){
    uint8_t err = 0;
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
        break;
        case EM111_DEVICE_TYPE:
        break;
        case EM120_DEVICE_TYPE:
        break;
        case EM122_DEVICE_TYPE:
        break;
        case EM220_DEVICE_TYPE:
        break;
        case EM750_DEVICE_TYPE:
        break;
        case EA750_DEVICE_TYPE:
        break;
        case FLOW_METER_DEVICE_TYPE:
        break;
        case PULSE_METER_DEVICE_TYPE:
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
    if(deviceType<1 || deviceType>MAX_DEVICE_TYPE) return INVALID_DEVICE_TYPE;
    return NO_ERROR;
};

uint8_t checkAzureId(AsyncWebServerRequest *request){
    Serial.println("Mon amur geten");
    if(!request->hasParam(PARAMETER_AZURE_ID, true)) return UNDEFINED_AZURE_ID;
    Serial.println("Je no comprende pas");
    String azureId = request->getParam(PARAMETER_AZURE_ID, true)->value();
    if(azureId.length()>AZURE_ID_MAX_LENGTH) return AZURE_ID_MAX_LENGTH_REACHED;
    Serial.println("[CheckAzureId] Azure ID:");
    Serial.print(azureId);
    
    return NO_ERROR;
}


uint8_t checkAzureSasKey(AsyncWebServerRequest *request){
    if(!request->hasParam(PARAMETER_AZURE_SAS_KEY, true)) return UNDEFINED_AZURE_SAS_KEY;
    String azureSasKey = request->getParam(PARAMETER_AZURE_SAS_KEY, true)->value();
    if(azureSasKey.length()>AZURE_SAS_KEY_MAX_LENGTH) return AZURE_SAS_KEY_MAX_LENGTH_REACHED;
    Serial.println("[CheckAzureId] Azure azureSasKey:");
    Serial.print(azureSasKey);
    
    return NO_ERROR;
}
