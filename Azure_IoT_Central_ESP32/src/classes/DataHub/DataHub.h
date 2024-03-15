#pragma once

#include <RingBuf.h>
#include <LogModule.h>
#include <SDDataStorage.h>

#include "../../payloadGenerators/payloadGenerators.h"
#include "../../collections/AzureIoTCollection/AzureIoTCollection.h"
#include "../SDFolderManager/SDFolderManager.h"


enum DataHubState{
    GET_DATA_FROM_EM_FIFO,
    GET_DATA_FROM_FIFO,
    GET_DATA_FROM_WEIDOS_FIFO,
    MOVE_MESSAGE,
    TELEMETRY_SENT,
    TELEMETRY_SEND_FAILURE,
    SD_SAVE_DATA,
    SD_INITIALIZE,
    SD_NOT_INITIALIZED,
    SD_INITIALIZATION_TIMEOUT,
    SD_OPEN_FILE,
    SD_WRITE_FILE,
    SD_CLOSE_FILE,
    WAITING
};




template <class T, int N>
class DataHub{

    typedef int (*payloadGenerator)(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, T& data);
    
  public:
    DataHub(){};
    void loop();
    void push(T data);
    int getSize(){ return dataBuffer.size();}
    void setPayloadGenerator(payloadGenerator generatePayload){ this->generatePayload = generatePayload;}
    void setPayloadGenerator2(payloadGenerator generatePayload){ this->generatePayload2 = generatePayload;}

    
  private:
      RingBuf<T,N> dataBuffer;

      int state = GET_DATA_FROM_FIFO;
      payloadGenerator generatePayload = nullptr;
      payloadGenerator generatePayload2 = nullptr;
      int numSendTries = 0;
      T currentPayload;
};




template <class T, int N>
void DataHub<T,N>::push(T data){
    bool savedInBuffer =  dataBuffer.push(data);
    // int deviceId = data.deviceId;
    // unsigned long timestamp = data.timestamp;
    
    // if(savedInBuffer){
    //     //Serial.println("Inside provisional");
    //     SDFolderManager.createProvisionalFolder(deviceId);
    //     // if(SDFolderManager.createProvisionalFolder(deviceId)) Serial.println("Folders exists. No worries.");
    //     //else Serial.println("Folders do NOT exists");
    //     char* fileName = SDFolderManager.setProvisionalFilePath(deviceId, timestamp);
    //     //Serial.print("[DataHub<T,N>::push] fielename: ");
    //     Serial.println(fileName);
    //     if(SDDataStorage.put(fileName, data)){
    //         Serial.println("Data successful PUSH in PROVISOINAL DATAHUB.");
    //     }else{
    //         Serial.println("Data PUSH failure in PROVISIONAL DATAHUB.");

    //     }
    //     return;
    // }



    // SDFolderManager.createPendingFolder(deviceId);
    // char* fileName = SDFolderManager.setPendingFilePath(deviceId, timestamp);
    // if(SDDataStorage.put(fileName, data)){
    //         Serial.println("Data successful PUSH in PENDING DATAHUB.");
    //     }else{
    //         Serial.println("Data PUSH failure in PENDING DATAHUB.");

    //     }

    return;
}




template <class T, int N>
void DataHub<T,N>::loop(){
    uint8_t deviceId = 0;
    char* filePath;
    AzureIoTDevice* azureDevice = nullptr;
    switch(state){
        case GET_DATA_FROM_FIFO:
            if(dataBuffer.pop(currentPayload)){
                state = MOVE_MESSAGE;
                deviceId = currentPayload.deviceId;
                numSendTries = 1;
                //LogInfo2(F("Info for device ID: %i poped"), deviceId);
            }
            break;

        case MOVE_MESSAGE:
        {
            deviceId = currentPayload.deviceId;
            LogInfo2(F("Moving Info for device ID: %i"), deviceId);
            azureDevice = AzureIoTCollection[deviceId];
            if(!azureDevice){
                state = TELEMETRY_SEND_FAILURE;
                break;
            }

            if(azureDevice->getStatus() != azure_iot_connected){
                state = TELEMETRY_SEND_FAILURE;
                break;
            }
            
            size_t payload_buffer_length = 0;
            uint8_t* payload_buffer = azureDevice->getDataBuffer2();
            generatePayload(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
            int error = azureDevice->sendMessage(az_span_create(payload_buffer, payload_buffer_length));
            if(error){
                state = TELEMETRY_SEND_FAILURE;
                break;
            }

            if(!generatePayload2) Serial.println("PayloadGenerator 2 is not set hehehhee");
            else{
                generatePayload2(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
                error = azureDevice->sendMessage(az_span_create(payload_buffer, payload_buffer_length));
                if(error){
                    state = TELEMETRY_SEND_FAILURE;
                    break;
                }
            }
            
            
            state = TELEMETRY_SENT;
            break;
        }

        case TELEMETRY_SENT:
            LogInfo2(F("Message successfully sent for ID: %i. Required number of tries: %i"), deviceId, numSendTries);

            // filePath = SDFolderManager.setProvisionalFilePath(currentPayload.deviceId, currentPayload.timestamp);
            // Serial.print("DataHub<T,N>::loop() Let's remove file: ");
            // Serial.println(filePath);
            // if(SDFolderManager.removeFile(filePath)){
            //     Serial.println("DataHub<T,N>::loop() File removed.");
            // }else{
            //     Serial.println("DataHub<T,N>::loop() File NOT removed.");
            // }
            state = GET_DATA_FROM_FIFO;
            break;

        case TELEMETRY_SEND_FAILURE:
            LogError2(F("Failed sending telemetry. Current number of tries: %i"), numSendTries++);
            
            state = MOVE_MESSAGE;
            break;

        default:
            state = GET_DATA_FROM_FIFO;
            break;
    }
}
