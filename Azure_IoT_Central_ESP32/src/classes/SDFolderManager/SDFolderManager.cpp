#include "SDFolderManager.h"
#include <SD.h>
#include <string.h>
#include "../../collections/AzureIoTCollection/AzureIoTCollection.h"

char* INTERNAL_FOLDER = "/internal";
char* PULSE_METER_FOLDER = "/pulse";
char* ANALOG_METER_FOLDER = "/analog";



char* FILE_EXTENTION = ".txt";


char* BACKUP_FOLDER = "/data";
char* PENDING_FOLDER = "/pending";
char* PROVISIONAL_FOLDER = "/prov";


#define REMOVE_FILE_NUM_TRIES 3


static const int MAX_FILENAME_LENGTH = 8;
#define SD_NUMBER_TRIES 5






bool SDFolderManagerClass::createFolder(char* path){
    // Serial.print("[createFolder]");
    bool result = true;
    if(!SD.begin()) return false;
    if(!SD.mkdir(path)) result = false;
    if(result){
        // Serial.print(path);
        // Serial.println("[createFolder] folder has been created");
    }else{
        // Serial.print(path);
        // Serial.println("[createFolder] folder has NOT been created");

    }
    SD.end();
    return result;
}

int SUCCESS = 0;
int BEGIN_ERROR = 1;
int FOLDER_DO_NOT_EXIST = 2;
int COULD_NOT_OPEN_FOLDER = 3;
int IS_NOT_A_DIRECTORY = 4;

int SDFolderManagerClass::directoryExists(char* path){
    // Serial.println();
    // Serial.println("[directoryExists]");
    // Serial.print("[directoryExists] Let's see if the following file is a folder: ");
    // Serial.println(path);
    //Could not begin SD. It migth be because SD is not present.
    if(!SD.begin()) return BEGIN_ERROR;


    //Folder does not exist inside SD.
    if(!SD.exists(path)){
        SD.end();
        return FOLDER_DO_NOT_EXIST;
    }else{
        // Serial.println("[directoryExists] Folder exists");
    }

    //If folder exists, open it to check if it folder or a file.
    File folder = SD.open(path);

    //Could not open folder or file.
    if(!folder){
        folder.close();
        SD.end();
        return COULD_NOT_OPEN_FOLDER;
    }else{
        // Serial.println("[directoryExists] Folder could be opened");
    }
    
    //Check if opened folder/file is a folder
    if(!folder.isDirectory()){
        folder.close();
        SD.end();
        return IS_NOT_A_DIRECTORY;
    }else{
        // Serial.println("[directoryExists] File is acctually a folder. Lols");
    }

    // Serial.println();
    //All checks passed.
    return SUCCESS;
}


bool SDFolderManagerClass::clear(char* path){

    bool result = false;
    for(int i=0; i<REMOVE_FILE_NUM_TRIES; i++){
        result = SD.begin();
        if(result) break;
    }
    if(!result) return false;

    for(int i=0; i<REMOVE_FILE_NUM_TRIES; i++){
        result = SD.remove(filePath); 
        if(result) break;
    }
    SD.end();
    return result;
}




bool SDFolderManagerClass::createPulseMeterFolder(){
    Serial.println("[createPulseMeterFolder] function");
    strcpy(filePath, INTERNAL_FOLDER);
    if(!createFolder(filePath)){
        // Serial.print("[createPulseMeterFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }

    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createPulseMeterFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createPulseMeterFolder] Lets clear folder");
        clear(filePath);
        return false;
    }else{
        // Serial.print(filePath);
        // Serial.println("[createPulseMeterFolder] exists and is a folder.");
    }
   
    strcat(filePath, PULSE_METER_FOLDER);
    if(!createFolder(filePath)){
        // Serial.print("[createPulseMeterFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createPulseMeterFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createPulseMeterFolder] Lets clear folder");
        clear(filePath);
        return false;
    }

   return true;
}

bool SDFolderManagerClass::createAnalogMeterFolder(){
    strcpy(filePath, INTERNAL_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }

    if(directoryExists(filePath) != SUCCESS){
        clear(filePath);
        return false;
    }
   
    strcat(filePath, ANALOG_METER_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        clear(filePath);
        return false;
    }

   return true;
}



char* SDFolderManagerClass::setPulseMeterFilePath(int slot){
    strcpy(filePath, INTERNAL_FOLDER);
    strcat(filePath, PULSE_METER_FOLDER);
    strcat(filePath, "/");
    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strncat (filePath, azureId, 8);
    //strcat(filePath, azureId);
    strcat(filePath, FILE_EXTENTION);

    return filePath;
}

char* SDFolderManagerClass::setAnalogMeterFilePath(int slot){
    strcpy(filePath, INTERNAL_FOLDER);
    strcat(filePath, ANALOG_METER_FOLDER);
    strcat(filePath, "/");
    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strncat (filePath, azureId, 8);
    strcat(filePath, FILE_EXTENTION);

    return filePath;
}



bool SDFolderManagerClass::createProvisionalFolder(int slot){
    strcpy(filePath, BACKUP_FOLDER);
    if(!createFolder(filePath)){
        // Serial.print("[createProvisionalFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createProvisionalFolder]Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createProvisionalFolder]Lets clear folder");
        clear(filePath);
        return false;
    }else{
        // Serial.print(filePath);
        // Serial.println("[createProvisionalFolder] exists and is a folder.");
    }


    strcat(filePath, PROVISIONAL_FOLDER);
    if(!createFolder(filePath)){
        // Serial.print("[createProvisionalFolder]Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createProvisionalFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createProvisionalFolder] Lets clear folder");
        clear(filePath);
        return false;
    }else{
        // Serial.print(filePath);
        // Serial.println("[createProvisionalFolder] exists and is a folder.");
    }


    strcat(filePath, "/");
    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strncat(filePath, azureId, 8);
    if(!createFolder(filePath)){
        // Serial.print("[createProvisionalFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createProvisionalFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createProvisionalFolder] Lets clear folder");
        clear(filePath);
        return false;
    }else{
        // Serial.print(filePath);
        // Serial.println("[createProvisionalFolder] exists and is a folder.");
    }


   return true;
}


bool SDFolderManagerClass::createPendingFolder(int slot){
    strcpy(filePath, BACKUP_FOLDER);
    if(!createFolder(filePath)){
        // Serial.print("[createPendingFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createPendingFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createPendingFolder] Lets clear folder");
        clear(filePath);
        return false;
    }


    strcat(filePath, PENDING_FOLDER);
    if(!createFolder(filePath)){
        // Serial.print("[createPendingFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createPendingFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createPendingFolder] Lets clear folder");
        clear(filePath);
        return false;
    }


    strcat(filePath, "/");
    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strncat(filePath, azureId, 8);
    if(!createFolder(filePath)){
        // Serial.print("[createPendingFolder] Could not create folder: ");
        // Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(directoryExists(filePath) != SUCCESS){
        // Serial.print("[createPendingFolder] Folder does not exist: ");
        // Serial.println(filePath);
        // Serial.println("[createPendingFolder] Lets clear folder");
        clear(filePath);
        return false;
    }


   return true;
}


char* SDFolderManagerClass::setProvisionalFolderPath(int slot){

    strcpy(filePath, BACKUP_FOLDER);
    strcat(filePath, PROVISIONAL_FOLDER);

    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strcat(filePath, "/");
    strncat(filePath, azureId, 8);

    return filePath;
}

char* SDFolderManagerClass::setPendingFolderPath(int slot){

    strcpy(filePath, BACKUP_FOLDER);
    strcat(filePath, PENDING_FOLDER);

    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strcat(filePath, "/");
    strncat(filePath, azureId, 8);

    return filePath;
}



char* SDFolderManagerClass::setProvisionalFilePath(int slot, unsigned long timestamp){
    strcpy(filePath, BACKUP_FOLDER);
    strcat(filePath, PROVISIONAL_FOLDER);

    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strcat(filePath, "/");
    strncat(filePath, azureId, 8);

    String fileName = String(timestamp);

    int firstIndex = fileName.length() - MAX_FILENAME_LENGTH;
    if(firstIndex < 0) firstIndex = 0;

    fileName = fileName.substring(firstIndex);
    strcat(filePath, "/");
    strcat(filePath, fileName.c_str());
    strcat(filePath, FILE_EXTENTION);
    // Serial.print("I've gotten the following folders: ");
    // Serial.println(filePath);

    return filePath;
}

char* SDFolderManagerClass::setPendingFilePath(int slot, unsigned long timestamp){

    strcpy(filePath, BACKUP_FOLDER);
    strcat(filePath, PENDING_FOLDER);

    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strcat(filePath, "/");
    strncat(filePath, azureId, 8);
   
    String fileName = String(timestamp);

    int firstIndex = fileName.length() - MAX_FILENAME_LENGTH;
    if(firstIndex < 0) firstIndex = 0;

    fileName = fileName.substring(firstIndex);
    strcat(filePath, "/");
    strcat(filePath, fileName.c_str());
    strcat(filePath, FILE_EXTENTION);
    // Serial.print("I've gotten the following folders: ");
    // Serial.println(filePath);


    return filePath;
}




char* SDFolderManagerClass::concatenate(char* string){ 
    strcat(filePath, string);

    return filePath;
}

bool SDFolderManagerClass::removeFile(char* filePath){
    bool result = false;
    for(int i=0; i<REMOVE_FILE_NUM_TRIES; i++){
        result = SD.begin();
        if(result) break;
        Serial.print("let's retry 1: ");
        Serial.println(i);
    }
    if(!result) return false;

    for(int i=0; i<REMOVE_FILE_NUM_TRIES; i++){
        result = SD.remove(filePath);
        if(result) break;
        Serial.print("let's retry 2: ");
        Serial.println(i);
    }
    SD.end();
    return result;
}

SDFolderManagerClass SDFolderManager;
