class SDFolderManager{
    public:
        SDFolderManager(){};
        void moveDirectory(const char* originDir, const char* destinationDir);
        bool createFolder(const char* folderPath);
    private:
        void moveAllFilesOneByOne(const char* originDir, const char* destinationDir);
};


extern SDFolderManager sdFolderManager;
