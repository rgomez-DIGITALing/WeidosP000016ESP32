#pragma once

#include "SDFolderManager.h"
#include "SDFileManager.h"



void createBackupFolders();
void moveAllProvisionalDirectories();

bool getDestinationDir(char* pathBuffer, int index);
bool getOriginDir(char* pathBuffer, int index);
