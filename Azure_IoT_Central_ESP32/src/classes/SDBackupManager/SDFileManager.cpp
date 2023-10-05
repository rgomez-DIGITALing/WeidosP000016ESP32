#include "SDFileManager.h"
#include "SDGlobalVariables.h"

#include "../../AzureDevices.h"



bool SDFileManager::getProvisionalFileName(char* pathBuffer, int deviceIndex, unsigned long timestamp, unsigned long millis){
    Serial.print("millis: ");
    Serial.println(millis);
    millis %= 1000;
    Serial.print("Truncated millis: ");
    Serial.println(millis);

    char* deviceId = azureDevices[deviceIndex]->getDeviceId();
    if(deviceId == nullptr) return false;

    
    

    strcpy(pathBuffer, SD_BACKUP_FILE_PROVISIONAL_DIRECTORY);
    strcat(pathBuffer, "/");
    strcat(pathBuffer, deviceId);
    strcat(pathBuffer, "/");
    String timeString(timestamp);
    strcat(pathBuffer, timeString.c_str());
    strcat(pathBuffer, "-");
    String millisString(millis);
    strcat(pathBuffer, millisString.c_str());
    strcat(pathBuffer, ".txt");

    Serial.println(pathBuffer);

    return true;
}



bool SDFileManager::getPendingFileName(char* pathBuffer, int deviceIndex, unsigned long timestamp, unsigned long millis){
    Serial.print("millis: ");
    Serial.println(millis);
    millis %= 1000;
    Serial.print("Truncated millis: ");
    Serial.println(millis);

    char* deviceId = azureDevices[deviceIndex]->getDeviceId();
    if(deviceId == nullptr) return false;

    
    

    strcpy(pathBuffer, SD_BACKUP_FILE_PENDING_DIRECTORY);
    strcat(pathBuffer, "/");
    strcat(pathBuffer, deviceId);
    strcat(pathBuffer, "/");
    String timeString(timestamp);
    strcat(pathBuffer, timeString.c_str());
    strcat(pathBuffer, "-");
    String millisString(millis);
    strcat(pathBuffer, millisString.c_str());
    strcat(pathBuffer, ".txt");

    Serial.println(pathBuffer);

    return true;
}




SDFileManager sdFileManager;
