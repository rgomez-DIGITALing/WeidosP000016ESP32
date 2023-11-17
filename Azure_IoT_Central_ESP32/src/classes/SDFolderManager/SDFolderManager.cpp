#include "SDFolderManager.h"
#include <SD.h>
#include <string.h>
#include "../../collections/AzureIoTCollection/AzureIoTCollection.h"

char* INTERNAL_FOLDER = "/internal";
char* PULSE_METER_FOLDER = "/pulse";
char* ANALOG_METER_FOLDER = "/analog";



char* FILE_EXTENTION = ".bin";


char* BACKUP_FOLDER = "/data";
char* PENDING_FOLDER = "/pending";
char* PROVISIONAL_FOLDER = "/prov";





static const int MAX_FILENAME_LENGTH = 8;
#define SD_NUMBER_TRIES 5






bool SDFolderManagerClass::createFolder(char* path){
    bool result = true;
    if(!SD.begin()) return false;
    if(!SD.mkdir(path)) result = false;
    
    SD.end();
    return result;
}

int SUCCESS = 0;
int BEGIN_ERROR = 1;
int FOLDER_DO_NOT_EXIST = 2;
int COULD_NOT_OPEN_FOLDER = 3;
int IS_NOT_A_DIRECTORY = 4;

int SDFolderManagerClass::directoryExists(char* path){
    //Could not begin SD. It migth be because SD is not present.
    if(!SD.begin()) return BEGIN_ERROR;


    //Folder does not exist inside SD.
    if(!SD.exists(path)){
        SD.end();
        return FOLDER_DO_NOT_EXIST;
    }

    //If folder exists, open it to check if it folder or a file.
    File folder = SD.open(path);

    //Could not open folder or file.
    if(!folder){
        folder.close();
        SD.end();
        return COULD_NOT_OPEN_FOLDER;
    }
    
    //Check if opened folder/file is a folder
    if(!folder.isDirectory()){
        folder.close();
        SD.end();
        return IS_NOT_A_DIRECTORY;
    }

    //All checks passed.
    return SUCCESS;
}


void SDFolderManagerClass::clear(char* path){
    if(!SD.begin()) return;
        Serial.print("Lets remove folder: ");
        Serial.println(filePath);

    if(SD.remove(path)){
        Serial.println("Succesfully cleared");
    }else Serial.println("NOT Succesfully cleared");
    SD.end();
    return;
}




bool SDFolderManagerClass::createPulseMeterFolder(){
    strcpy(filePath, INTERNAL_FOLDER);
    if(!createFolder(filePath)){
        Serial.print("Could not create folder: ");
        Serial.println(filePath);
        clear(filePath);
        return false;
    }

    if(!directoryExists(filePath)){
        Serial.print("Folder does not exist: ");
        Serial.println(filePath);
        Serial.println("Lets clear folder");
        clear(filePath);
        return false;
    }
   
    strcat(filePath, PULSE_METER_FOLDER);
    if(!createFolder(filePath)){
        Serial.print("Could not create folder: ");
        Serial.println(filePath);
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
        Serial.print("Folder does not exist: ");
        Serial.println(filePath);
        Serial.println("Lets clear folder");
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

    if(!directoryExists(filePath)){
        clear(filePath);
        return false;
    }
   
    strcat(filePath, ANALOG_METER_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
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
    strcat(filePath, azureId);
    strcat(filePath, FILE_EXTENTION);

    return filePath;
}



bool SDFolderManagerClass::createProvisionalFolder(int slot){
    strcpy(filePath, BACKUP_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
        clear(filePath);
        return false;
    }


    strcat(filePath, PROVISIONAL_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
        clear(filePath);
        return false;
    }


    strcat(filePath, "/");
    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strncat(filePath, azureId, 8);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
        clear(filePath);
        return false;
    }


   return true;
}


bool SDFolderManagerClass::createPendingFolder(int slot){
    strcpy(filePath, BACKUP_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
        clear(filePath);
        return false;
    }


    strcat(filePath, PENDING_FOLDER);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
        clear(filePath);
        return false;
    }


    strcat(filePath, "/");
    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
    char* azureId = "invalid";
    if(azureDevice) azureId = azureDevice->getDeviceId();
    strncat(filePath, azureId, 8);
    if(!createFolder(filePath)){
        clear(filePath);
        return false;
    }
    if(!directoryExists(filePath)){
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
    if(!SD.begin()) return false;
    bool result = SD.remove(filePath); 
    SD.end();
    return result;
}

SDFolderManagerClass SDFolderManager;







// bool SDFolderManagerClass::createPulseMeterFolder(){
//     bool result = false;
//     if(!SD.begin()) return false;

//     if(!SD.exists(PULSE_METER_FOLDER)) result = SD.mkdir(PULSE_METER_FOLDER);
//     Serial.print("Result: ");
//     Serial.println(result);

//     File folder = SD.open(PULSE_METER_FOLDER);
//     folder.close();
//     if(!folder) return false;
//     if(!folder.isDirectory()){
//         SD.remove(PULSE_METER_FOLDER);
//         return false;
//     }
//     SD.end();
//     return true;
// }

// bool SDFolderManagerClass::createAnalogMeterFolder(){
//     if(!SD.begin()) return false;

//     if(!SD.exists(ANALOG_METER_FOLDER)) SD.mkdir(ANALOG_METER_FOLDER);
    
//     File folder = SD.open(ANALOG_METER_FOLDER);
//     folder.close();
//     if(!folder) return false;
//     if(!folder.isDirectory()){
//         SD.remove(ANALOG_METER_FOLDER);
//         return false;
//     } 

//     return true;
// }


// bool SDFolderManagerClass::createProvisionalFolder(int slot){
//     strcpy(filePath, PROVISIONAL_FOLDER);
//     strcat(filePath, "/");
//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strncat(filePath, azureId, 8);


//     if(!SD.begin()) return false;
//     bool result;
//     if(!SD.exists(filePath)) result = SD.mkdir(filePath);
//     Serial.print("Result: ");
//     Serial.println(result);
//     File folder = SD.open(filePath);
//     folder.close();
//     if(!folder){
//         Serial.println("[createProvisionalFolder] !folder");
//         return false;
//     } 
        
//     if(!folder.isDirectory()){
//         SD.remove(filePath);
//         SD.end();
//         return false;
//     } 
//     SD.end();
//     return true;
// }

// bool SDFolderManagerClass::createPendingFolder(int slot){
//     strcpy(filePath, PENDING_FOLDER);
//     strcat(filePath, "/");
//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strncat(filePath, azureId, 8);


//     if(!SD.begin()) return false;

//     if(!SD.exists(filePath)) SD.mkdir(filePath);
    
//     File folder = SD.open(filePath);
//     folder.close();
//     if(!folder){
//         Serial.println("[createPendingFolder] !folder");
//         return false;
//     }
//     if(!folder.isDirectory()){
//         SD.remove(filePath);
//         return false;
//     } 

//     return true;
// }



// char* SDFolderManagerClass::setPulseMeterFilePath(int slot){
//     strcpy(filePath, PULSE_METER_FOLDER);
//     strcat(filePath, "/");
//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strncat (filePath, azureId, 8);
//     strcat(filePath, FILE_EXTENTION);

//     return filePath;
// }

// char* SDFolderManagerClass::setAnalogMeterFilePath(int slot){
//     strcpy(filePath, ANALOG_METER_FOLDER);
//     strcat(filePath, "/");
//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strncat (filePath, azureId, 8);
//     strcat(filePath, FILE_EXTENTION);

//     return filePath;
// }






// char* SDFolderManagerClass::setProvisionalFolderPath(int slot){
//     strcpy(filePath, PROVISIONAL_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);

//     return filePath;
// }

// char* SDFolderManagerClass::setPendingFolderPath(int slot){
//     strcpy(filePath, PENDING_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);

//     return filePath;
// }



// char* SDFolderManagerClass::setProvisionalFilePath(int slot, unsigned long timestamp){
//     strcpy(filePath, PROVISIONAL_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);

//     String fileName = String(timestamp);

//     int firstIndex = fileName.length() - MAX_FILENAME_LENGTH;
//     if(firstIndex < 0) firstIndex = 0;

//     fileName = fileName.substring(firstIndex);
//     strcat(filePath, "/");
//     strcat(filePath, fileName.c_str());
//     strcat(filePath, FILE_EXTENTION);


//     return filePath;
// }


// char* SDFolderManagerClass::setPendingFilePath(int slot, unsigned long timestamp){
//     strcpy(filePath, PENDING_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);
   
//     String fileName = String(timestamp);

//     int firstIndex = fileName.length() - MAX_FILENAME_LENGTH;
//     if(firstIndex < 0) firstIndex = 0;

//     fileName = fileName.substring(firstIndex);
//     strcat(filePath, "/");
//     strcat(filePath, fileName.c_str());
//     strcat(filePath, FILE_EXTENTION);


//     return filePath;
// }




//bool SDFolderManagerClass::createPulseMeterFolder2(){
//    bool folderExists = true;
//
//    if(!SD.begin()) return false;
//
//
//    strcpy(filePath, INTERNAL_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    
//    File folder = SD.open(filePath);
//    if(!folder) return false;
//    if(!folder.isDirectory()){
//        SD.remove(filePath);
//        return false;
//    }
//    
//    if(!folderExists) return false;
//    
//
//    strcat(filePath, PULSE_METER_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    folder = SD.open(filePath);
//    if(!folder) return false;
//    if(!folder.isDirectory()){
//        SD.remove(filePath);
//        return false;
//    }
//
//    if(!folderExists) return false;
//    
//    return true;
//}
//
//bool SDFolderManagerClass::createAnalogMeterFolder2(){
//    bool folderExists = true;
//    
//    if(!SD.begin()) return false;
//
//
//    strcpy(filePath, INTERNAL_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) return false;
//
//    strcat(filePath, ANALOG_METER_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) return false;
//    
//    return true;
//}
//


// char* SDFolderManagerClass::getPulseMeterFilePath(int slot){
//     strcpy(filePath, INTERNAL_FOLDER);
//     strcat(filePath, PULSE_METER_FOLDER);
//     strcat(filePath, "/");
//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strncat (filePath, azureId, 8);
//     //strcat(filePath, azureId);
//     strcat(filePath, FILE_EXTENTION);
//     Serial.print("Let's give the followiung path: ");
//     Serial.println(filePath);
//     return filePath;
// }

// char* SDFolderManagerClass::getAnalogMeterFilePath(int slot){
//     strcpy(filePath, INTERNAL_FOLDER);
//     strcat(filePath, ANALOG_METER_FOLDER);
//     strcat(filePath, "/");
//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, azureId);
//     strcat(filePath, FILE_EXTENTION);

//     return filePath;
// }



//bool SDFolderManagerClass::createProvisionalFolder2(int slot){
//    bool folderExists = true;
//    // Serial.println("Inside create Provsional");
//    Serial.println("Let's create provisional folder");
//    if(!SD.begin()) return false;
//
//
//    strcpy(filePath, BACKUP_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) {
//        Serial.print("Error creating folder: ");
//        Serial.println(filePath);
//
//        Serial.print("exists: ");
//        Serial.println(SD.exists(filePath));
//        return false;
//        
//    }else{
//        Serial.print("Folder exists:");
//        Serial.println(filePath);
//    }
//    // Serial.println(filePath);
//
//
//    strcat(filePath, PROVISIONAL_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) {
//        Serial.print("Error creating folder: ");
//        Serial.println(filePath);
//
//        Serial.print("exists: ");
//        Serial.println(SD.exists(filePath));
//        return false;
//        
//    }else{
//        Serial.print("Folder exists:");
//        Serial.println(filePath);
//    }
//    strcat(filePath, "/");
//    // Serial.println(filePath);
//
//    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//    char* azureId = "invalid";
//    if(azureDevice) azureId = azureDevice->getDeviceId();
//    strncat(filePath, azureId, 8);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) {
//        Serial.print("Error creating folder: ");
//        Serial.println(filePath);
//
//        Serial.print("exists: ");
//        Serial.println(SD.exists(filePath));
//        return false;
//        
//    }else{
//        Serial.print("Folder exists:");
//        Serial.println(filePath);
//    }
//    // Serial.println(filePath);
//
//    // Serial.println("I've created the following folders: ");
//    // Serial.print(filePath);
//    return true;
//}
//
//bool SDFolderManagerClass::createPendingFolder2(int slot){
//    bool folderExists = true;
//
//    if(!SD.begin()) return false;
//
//
//    strcpy(filePath, BACKUP_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) return false;
//
//
//    strcat(filePath, PENDING_FOLDER);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) return false;
//
//    AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//    char* azureId = "invalid";
//    if(azureDevice) azureId = azureDevice->getDeviceId();
//    strcat(filePath, "/");
//    strncat(filePath, azureId, 8);
//    if(!SD.exists(filePath)) folderExists = SD.mkdir(filePath);
//    if(!folderExists) return false;
//    
//    // Serial.println("I've created the following folders: ");
//    // Serial.print(filePath);
//    return true;
//}
//


// char* SDFolderManagerClass::getProvisionalFolderPath(int slot){

//     strcpy(filePath, BACKUP_FOLDER);
//     strcat(filePath, PROVISIONAL_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);

//     return filePath;
// }

// char* SDFolderManagerClass::getPendingFolderPath(int slot){

//     strcpy(filePath, BACKUP_FOLDER);
//     strcat(filePath, PENDING_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);

//     return filePath;
// }



// char* SDFolderManagerClass::getProvisionalFilePath(int slot, unsigned long timestamp){
//     strcpy(filePath, BACKUP_FOLDER);
//     strcat(filePath, PROVISIONAL_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);

//     String fileName = String(timestamp);

//     int firstIndex = fileName.length() - MAX_FILENAME_LENGTH;
//     if(firstIndex < 0) firstIndex = 0;

//     fileName = fileName.substring(firstIndex);
//     strcat(filePath, "/");
//     strcat(filePath, fileName.c_str());
//     strcat(filePath, FILE_EXTENTION);
//     // Serial.print("I've gotten the following folders: ");
//     // Serial.println(filePath);

//     return filePath;
// }

// char* SDFolderManagerClass::getPendingFilePath(int slot, unsigned long timestamp){

//     strcpy(filePath, BACKUP_FOLDER);
//     strcat(filePath, PENDING_FOLDER);

//     AzureIoTDevice* azureDevice = AzureIoTCollection[slot];
//     char* azureId = "invalid";
//     if(azureDevice) azureId = azureDevice->getDeviceId();
//     strcat(filePath, "/");
//     strncat(filePath, azureId, 8);
   
//     String fileName = String(timestamp);

//     int firstIndex = fileName.length() - MAX_FILENAME_LENGTH;
//     if(firstIndex < 0) firstIndex = 0;

//     fileName = fileName.substring(firstIndex);
//     strcat(filePath, "/");
//     strcat(filePath, fileName.c_str());
//     strcat(filePath, FILE_EXTENTION);
//     // Serial.print("I've gotten the following folders: ");
//     // Serial.println(filePath);


//     return filePath;
// }




// char* SDFolderManagerClass::concatenate(char* string){ 
//     strcat(filePath, string);

//     return filePath;
// }

// bool SDFolderManagerClass::removeFile(char* filePath){
//     if(!SD.begin()) return false;
//     bool result = SD.remove(filePath); 
//     SD.end();
//     return result;
// }

// SDFolderManagerClass SDFolderManager;
