#pragma once




class SDFolderManagerClass{
    public:

        bool createFolder(char* path);
        int directoryExists(char* path);
        bool createPulseMeterFolder();
        bool createAnalogMeterFolder();
        bool createPulseMeterFolder2();
        bool createAnalogMeterFolder2();
        char* setPulseMeterFilePath(int slot);
        char* setAnalogMeterFilePath(int slot);


        bool createProvisionalFolder(int slot);
        bool createPendingFolder(int slot);
        bool createProvisionalFolder2(int slot);
        bool createPendingFolder2(int slot);
        char* setProvisionalFolderPath(int slot);
        char* setPendingFolderPath(int slot);


        char* setProvisionalFilePath(int slot, unsigned long timestamp);
        char* setPendingFilePath(int slot, unsigned long timestamp);

        char* concatenate(char* string);
        bool removeFile(char* filePath);
        
    private:
        void clear(char* path);
        char filePath[100];
};

extern SDFolderManagerClass SDFolderManager;
