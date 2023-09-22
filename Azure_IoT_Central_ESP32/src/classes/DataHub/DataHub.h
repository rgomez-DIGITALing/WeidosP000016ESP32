#pragma once

#include "../EnergyMeterManager/energyMeterManager.h"
#include "../WeidosManager/WeidosManager.h"

//#include "./classes/WeidosESP32Class/WeidosESP32Class.h"
#include <RingBuf.h>



#include "../../payloadGenerators.h"
#include <LogModule.h>
#include "../../AzureDevices.h"

#define NUM_TOTAL_DATA 60

#define ENERGY_METER_RING_BUFFER_SIZE 15
#define WEIDOS_METADATA_RING_BUFFER_SIZE 20

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




//typedef void (*payloadGenerator_function)(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, T data)
//        payloadGenerator;



template <class T, int N>
class DataHub{

    typedef int (*payloadGenerator)(uint8_t* payload_buffer, size_t payload_buffer_size, size_t* payload_buffer_length, T& data);
    
  public:
    DataHub(){};
    void loop();
    void push(T data){ dataBuffer.push(data);}
    //void push(weidosMetadata_t data){ weidosData.push(data);}
    void setPayloadGenerator(payloadGenerator generatePayload){ this->generatePayload = generatePayload;}
    
    
    //void setPayloadGenerator(payloadGenerator payloadGenerator){ generatePayload = payloadGenerator; };
    
  private:
      RingBuf<T,N> dataBuffer;
      //RingBuf<weidosMetadata_t ,RING_BUFFER_SIZE> weidosData;
      int state = GET_DATA_FROM_FIFO;
      //payloadGenerator generatePayload;
      
      payloadGenerator generatePayload;
      int numSendTries = 0;
      T currentPayload;
};


template <class T, int N>
void DataHub<T,N>::loop(){
    uint8_t deviceId = 0;
    switch(state){
        case GET_DATA_FROM_FIFO:
            //LOG("case: GET_DATA_FROM_FIFO");
            if(dataBuffer.pop(currentPayload)){
                state = MOVE_MESSAGE;
                deviceId = currentPayload.deviceId;
                numSendTries = 1;
                LogInfo("Info for device ID: %i poped", deviceId);
            }
            break;

        case MOVE_MESSAGE:
            deviceId = currentPayload.deviceId;
            LogInfo("Moving Info for device ID: %i", deviceId);
            if(azureDevices[deviceId]->getStatus() == azure_iot_connected){
                size_t payload_buffer_length = 0;
                uint8_t* payload_buffer = azureDevices[deviceId]->getDataBuffer2();

                //em750_generete_payload(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
                generatePayload(payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, currentPayload);
                
                int error = azureDevices[deviceId]->sendMessage(az_span_create(payload_buffer, payload_buffer_length));
                if(!error) state = TELEMETRY_SENT;
                else state = TELEMETRY_SEND_FAILURE;
            }else state = TELEMETRY_SEND_FAILURE;
            break;

        case TELEMETRY_SENT:
            LogInfo("Message successfully sent. Required number of tries: %i", numSendTries);
            state = GET_DATA_FROM_FIFO;
            break;

        case TELEMETRY_SEND_FAILURE:
            LogError("Failed sending telemetry. Current number of tries: %i", numSendTries++);
            
            state = MOVE_MESSAGE;
            break;

        default:
            state = GET_DATA_FROM_FIFO;
            break;
    }
}


void fillDataHubsArray();

extern DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE> weidosDataHub;
extern DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>* energyMeterDataHubs[5];