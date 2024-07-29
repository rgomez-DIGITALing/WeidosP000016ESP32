#pragma once
#include <Arduino.h>
#include <SD.h>


class SDDataStorageClass{
    public:
        SDDataStorageClass(){}


        template<typename T>
        bool put(const char* filePath, T& data){
            if(!SD.begin()) return false;


            //File file =  SD.open(filePath, FILE_WRITE, true);
            File file =  SD.open(filePath, O_WRITE | O_CREAT);

            if(!file){
                SD.end();
                return false;
            } 

            int writtenBytes = file.write((uint8_t*)&data, sizeof(T));
            file.close();
            SD.end();
            if(writtenBytes != sizeof(T)){
                
                return false;
            } 

            return true;
        }

        

        template<typename T>
        bool get(const char* filePath, T& data){
            if(!SD.begin()) return false;
            //File file =  SD.open(filePath, FILE_READ, true);
            File file =  SD.open(filePath, FILE_READ);
            if(!file){
                SD.end();
                return false;
            } 
        
            int readBytes = file.read((uint8_t*)&data, sizeof(T));
            file.close();
            SD.end();

            if(readBytes != sizeof(T)) return false;

            return true;
        }
};


extern SDDataStorageClass SDDataStorage;