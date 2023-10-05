#pragma once
#include <Arduino.h>
#include <SDDataStorage.h>


class SDFileManager{
    public:
        template<typename T>
        bool storeInPendingFolder(const T& msg);
        template<typename T>
        bool storeInProvisionalFolder(const T& msg);

        bool getProvisionalFileName(char* pathBuffer, int deviceIndex, unsigned long timestamp, unsigned long millis);
        bool getPendingFileName(char* pathBuffer, int deviceIndex, unsigned long timestamp, unsigned long millis);

    private:
};



template<typename T>
bool SDFileManager::storeInPendingFolder(const T& msg){
    int deviceIndex = msg.deviceId;
    unsigned long timestamp = msg.timestamp;
    unsigned long millis = msg.millis;
    
    char filePath[70];
    getPendingFileName(filePath, deviceIndex, timestamp, millis);
    bool result = sdDataStorage.put(filePath, msg);
    return result;
}

template<typename T>
bool SDFileManager::storeInProvisionalFolder(const T& msg){
    int deviceIndex = msg.deviceId;
    unsigned long timestamp = msg.timestamp;
    unsigned long millis = msg.millis;
    
    char filePath[70];
    getProvisionalFileName(filePath, deviceIndex, timestamp, millis);
    bool result = sdDataStorage.put(filePath, msg);
    return result;
}


extern SDFileManager sdFileManager;
