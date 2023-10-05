#include "SDFolderManager.h"
#include <Arduino.h>
#include <SD.h>

#include "../EnergyMeterManager/energyMeterManager.h"


SDFolderManager sdFolderManager;

#define SD_BACKUP_TEMP_FILE "temp.txt"


bool SDFolderManager::createFolder(const char* folderPath){

  if(!SD.begin()) return false;
    
    char filePath[50];
    strcpy(filePath, folderPath);
    strcat(filePath, "/");
    strcat(filePath, SD_BACKUP_TEMP_FILE);
    File file = SD.open(filePath, FILE_WRITE, true);
    
    if(!file){
      SD.end();
      return false; 
    }
    SD.remove(filePath);
    SD.end();
    return true;
}



void SDFolderManager::moveDirectory(const char* originDir, const char* destinationDir){

    if(originDir == nullptr) return;
    if(destinationDir == nullptr) return;
    Serial.println("Let's goo!");
    if(!SD.begin(0x2106u)){
        Serial.println(F("SD could not begin."));
        return;
    }
    
    if(!SD.exists(originDir)){
      Serial.println(F("Origin path doesn't exists."));
      SD.end();
      return;
    }
    
    if(!SD.exists(destinationDir)){
      Serial.println(F("Destionation path doesn't exist. Therefore, it is easy for us to rename hehehehe."));
      bool success = SD.rename(originDir, destinationDir);
      SD.end();
      if(success) Serial.println("Folder successfully renamed.");
      else Serial.println("Folder NOT renamed.");

      return;
    }

    Serial.println(F("Destination path already exists. Therefore, we have to loop files one by one."));
    moveAllFilesOneByOne(originDir, destinationDir);


    SD.end();

    return;
}


void SDFolderManager::moveAllFilesOneByOne(const char* originDir, const char* destinationDir){
  if(!SD.begin()) return;

  File currentDir = SD.open(originDir, FILE_WRITE, true);
  if(currentDir.isDirectory()){
    Serial.println(F("You have just opened a directory."));

    File currentFile = currentDir.openNextFile();
    
    while(currentFile){
      Serial.print("Current file is: ");
      Serial.println(currentFile.name());
      String orgnPath = String(originDir) + String("/") + String(currentFile.name());
      Serial.print("Origin path is: ");
      Serial.println(orgnPath);
      
      String destPath = String(destinationDir) + String("/") + String(currentFile.name());
      Serial.print("Destination path is: ");
      Serial.println(destPath);
      Serial.println();

      SD.rename(orgnPath, destPath);
      currentFile = currentDir.openNextFile();
    }
  }

  SD.end();
  return;
}



// bool saveEMDataInFile(const char* path, SDBackupData_t* message){
//     energyMeterManagerData_t* energyMeterData = (energyMeterManagerData_t*) message->data;
//     Serial.println(F("Saving Energy Meter data in file."));

//     return true;
// }