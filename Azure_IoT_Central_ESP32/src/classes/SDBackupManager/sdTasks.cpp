#include "sdTasks.h"
#include <Arduino.h>
#include <SD.h>
#include <clockModule.h>
#include "SDFolderManager.h"

#include "../../AzureDevices.h"


#include "SDGlobalVariables.h"


void createBackupFolders(){
    sdFolderManager.createFolder(SD_BACKUP_FILE_PROVISIONAL_DIRECTORY);
    sdFolderManager.createFolder(SD_BACKUP_FILE_PENDING_DIRECTORY);
}

void moveAllProvisionalDirectories(){
    char originPath[70];
    char destinationPath[70];


    for(int i=0; i<3; i++){
        if(getOriginDir(originPath, i)){
            Serial.println(originPath);
        }

        if(getDestinationDir(destinationPath, i)){
            Serial.println(destinationPath);
        }
        
        sdFolderManager.moveDirectory(originPath, destinationPath);
    }
}



bool getOriginDir(char* pathBuffer, int index){
    char* deviceId = azureDevices[index]->getDeviceId();
    if(deviceId == nullptr) return false;

    strcpy(pathBuffer, SD_BACKUP_FILE_PROVISIONAL_DIRECTORY);
    strcat(pathBuffer, "/");
    strcat(pathBuffer, deviceId);
    return true;
}


bool getDestinationDir(char* pathBuffer, int index){
    char* deviceId = azureDevices[index]->getDeviceId();
    if(deviceId == nullptr) return false;

    strcpy(pathBuffer, SD_BACKUP_FILE_PENDING_DIRECTORY);
    strcat(pathBuffer, "/");
    strcat(pathBuffer, deviceId);
    return true;
}


//bool getProvisionalFileName(char* pathBuffer, const energyMeterManagerData_t& emData){
bool getProvisionalFileName(char* pathBuffer, int deviceIndex, unsigned long timestamp, unsigned long millis){
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
    Serial.println(pathBuffer);
    strcat(pathBuffer, ".txt");

    return true;
}
