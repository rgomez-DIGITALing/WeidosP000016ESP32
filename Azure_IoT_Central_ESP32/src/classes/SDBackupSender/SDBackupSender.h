#pragma once
#include <Arduino.h>

#include "../../collections/AzureIoTCollection/AzureIoTCollection.h"
#include <SDDataStorage.h>
#include "../SDFolderManager/SDFolderManager.h"


#define NUM_SD_TRIES 5

typedef enum{
    ERROR_NO_AZURE_DEVICE,
    ERROR_BEGIN,
    SUCCESS_NO_PROVISIONAL_FOLDER,
    ERROR_OPEN_FOLDER,
    ERROR_PROV_FOLDER_IS_FILE,
    SUCCESS_INIT,
} SD_backup_init_state_t;


template <class T>
class SDBackupSenderClass{
    public:
        //SDBackupSenderClass() : deviceId(99){}
        SDBackupSenderClass(int deviceId) : deviceId(deviceId){}
        SD_backup_init_state_t begin();
        void loop();

        typedef int (*payloadGenerator)(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, T& data);
        void setPayloadGenerator(payloadGenerator generatePayload){ this->generatePayload = generatePayload;}
    
  private:
      payloadGenerator generatePayload;
      int numSendTries = 0;
      int deviceId;
      T currentPayload;
      int getDataErrorCount = 0;
      int putDataErrorCount = 0;

    private:
};








template <class T>
SD_backup_init_state_t SDBackupSenderClass<T>::begin(){
    if(!AzureIoTCollection[deviceId]) return ERROR_NO_AZURE_DEVICE;

    
    char* provisionalFolderPath = SDFolderManager.setProvisionalFolderPath(deviceId);
    if(!SD.begin()) return ERROR_BEGIN;
    if(!SD.exists(provisionalFolderPath)){
        SD.end();
        return SUCCESS_NO_PROVISIONAL_FOLDER;
    }

    //Open provisional folder
    File folder;
    int numTries = 0;
    for(int i=0; i<NUM_SD_TRIES; i++){
        numTries++;
        folder = SD.open(provisionalFolderPath);
        if(folder) break;
    }

    //Check if provisional folder has been opened
    if(!folder){
        SD.end();
        Serial.println("Error opening Folder");
        return ERROR_OPEN_FOLDER;
    }

    //Check if folder is acctually a folder. Sometimes, when a folder is created, an error occures and it is created as a file.
    if(folder){
        if(!folder.isDirectory()){
            SDFolderManager.removeFile(folder.name());
            SD.end();
            return ERROR_PROV_FOLDER_IS_FILE;
        }
    }


    //Open a file (if there are any) inside folder 
    File file = folder.openNextFile();
    while(file){
        T data;

        file.close(); //Close file. File will be opened inside SDFolderManager methods.

        //Get provisional file path
        provisionalFolderPath = SDFolderManager.setProvisionalFolderPath(deviceId);
        SDFolderManager.concatenate("/");
        char* fileName = file.name();
        char* provisionalFilePath = SDFolderManager.concatenate(fileName);
        Serial.print("Moving data from: ");
        Serial.println(provisionalFolderPath);
        
        

        //Get data from provisional file path
        numTries = 0;
        bool success = false;
        for(int i=0; i<NUM_SD_TRIES; i++){
            numTries++;
            success = SDDataStorage.get(provisionalFilePath, data);
            if(success) break;
            delay(20);
        }

        //If could not get data from file, delete this file because it migth be corrupted.
        if(!success){
            getDataErrorCount++;
            Serial.println(" [ERROR] Error getting data. Let's continue with other files.");
            Serial.print("Let's remove file: ");
            Serial.println(provisionalFilePath);
            SDFolderManager.removeFile(provisionalFilePath);
            file = folder.openNextFile();
            continue;
        }
        //After getting data from file, close file.
        file.close();



        //Get pending file path
        SDFolderManager.createPendingFolder(deviceId);

        char* pendingFolderPath = SDFolderManager.setPendingFolderPath(deviceId);
        SDFolderManager.concatenate("/");
        char* pendingFilePath = SDFolderManager.concatenate(fileName);
        Serial.print("to: ");
        Serial.println(pendingFilePath);


        //Put data in pending file
        numTries = 0;
        for(int i=0; i<NUM_SD_TRIES; i++){
            numTries++;
            if(SDDataStorage.put(pendingFilePath, data)) break;
            delay(20);
        }
        //If could not put data inside pending file, continue with other files.
        if(numTries == NUM_SD_TRIES){
            putDataErrorCount++;
            Serial.println(" [ERROR] Error getting data. Let's continue with other files.");
            Serial.print("Let's remove file: ");
            Serial.println(pendingFilePath);
            file = folder.openNextFile();
            continue;
        }



        //Remove provisional file.
        provisionalFolderPath = SDFolderManager.setProvisionalFolderPath(deviceId);
        SDFolderManager.concatenate("/");
        provisionalFilePath = SDFolderManager.concatenate(fileName);
        Serial.print("Deleting provisional file: ");
        Serial.println(provisionalFilePath);
        SDFolderManager.removeFile(provisionalFilePath);


        Serial.println();
        //Open next file inside folder.
        file = folder.openNextFile();
    }

    SD.end();
    return SUCCESS_INIT;
}


template <class T>
void SDBackupSenderClass<T>::loop(){
            if(AzureIoTCollection[deviceId]->getStatus() != azure_iot_connected) return;

            char* pendingFolderPath = SDFolderManager.setPendingFolderPath(deviceId);
            if(!SD.begin()) return;
            if(!SD.exists(pendingFolderPath)){
                SD.end();
                return;
            }
            File folder = SD.open(pendingFolderPath);
            if(!folder){
                //Serial.println("Could not OPEN folder");
                SD.end();
                return;
            }


            File file = folder.openNextFile();
            if(!file){
                //Serial.println("There are no files in the folder");
                SD.end();
                return;
            }
            T msg;
            //Serial.print("[SDBackupSenderClass] file name: ");
            Serial.println(file.name());
            SDFolderManager.concatenate("/");
            pendingFolderPath = SDFolderManager.concatenate(file.name());
            file.close();
            //Serial.print("[SDBackupSenderClass] After concatenation: ");
            //Serial.println(pendingFolderPath);
            if(SDDataStorage.get(pendingFolderPath, msg)){
                //Serial.println("[SDBackupSenderClass] Data successfully recovered.");
            }else{
                Serial.println("[SDBackupSenderClass] Data could not be recovered to be sent");
            }
            msg.backup = 1;
            size_t payload_buffer_length = 0;
            uint8_t* payload_buffer = AzureIoTCollection[deviceId]->getDataBuffer2();

            generatePayload(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
            
            //int error = 0;
            int error = AzureIoTCollection[deviceId]->sendMessage(az_span_create(payload_buffer, payload_buffer_length));
            if(error){
                Serial.println("Error sending the pending telemetry");
                SD.end();
                return;
            }else{
                //Serial.println("[SDBackupSenderClass] Data has been sent");
            }

            unsigned long timestamp = msg.timestamp;
            char* filePath = SDFolderManager.setPendingFilePath(deviceId, timestamp);
            //Serial.print("[SDBackupSenderClass] Delte file of sent data: ");
            //Serial.println(filePath);
            
            if(SDFolderManager.removeFile(filePath)) Serial.println("Pending file successfully removed");
            else Serial.println("Pending file NOT removed");

           
            SD.end();
            return;
            

}