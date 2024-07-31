#include <SDLogger.h>
#include <SD.h>
#include <clockModule.h>




enum SDLoggerError{
    NO_ERROR,
    SD_BEGIN_ERROR,
    UNDEFINED_FILENAME,
    UNDEFINED_DIRECTORY,
    FILE_FAILED_OPENING,
    DIRECTORY_FAILED_CREATING,
    UNDEFINED_DATA_WRITER
};



int SDLoggerClass::log(String line){
    Serial.println("String");
    if(!SD.begin()) return SD_BEGIN_ERROR;
    if(!filename) return UNDEFINED_FILENAME;
    if(!directory) return UNDEFINED_DIRECTORY;

    if(!SD.exists(directory)){
        if(!SD.mkdir(directory)) return DIRECTORY_FAILED_CREATING;
    }
    
    String filepath = String(directory) + "/" + filename;


    File file = SD.open(filepath.c_str(), FILE_WRITE);
    
    if(!file) return FILE_FAILED_OPENING;
    file.println(line);
    file.close();

    return NO_ERROR;
}


int SDLoggerClass::log(char* line){
    Serial.println("char*");
    if(!SD.begin()) return SD_BEGIN_ERROR;
    if(!filename) return UNDEFINED_FILENAME;
    if(!directory) return UNDEFINED_DIRECTORY;

    if(!SD.exists(directory)){
        if(!SD.mkdir(directory)) return DIRECTORY_FAILED_CREATING;
    }
    
    String filepath = String(directory) + "/" + filename;

    File file = SD.open(filepath.c_str(), FILE_WRITE);

    if(!file) return FILE_FAILED_OPENING;
    file.println(line);
    file.close();

    return NO_ERROR;
}




int SDLoggerClass::log(sd_log_level_t log_level, char const* const format, ...)
{
    va_list args;
    va_start(args, format);
    int result = log(log_level, format, args);
    va_end(args);
    return result;
}



int SDLoggerClass::log(sd_log_level_t log_level, char const* const format, va_list args)
{
  if(!SD.begin()) return SD_BEGIN_ERROR;
  if(!filename) return UNDEFINED_FILENAME;
  if(!directory) return UNDEFINED_DIRECTORY;
  if(!SD.exists(directory)){
      if(!SD.mkdir(directory)) return DIRECTORY_FAILED_CREATING;
  }
  
  String filepath = String(directory) + "/" + filename;
  File file = SD.open(filepath.c_str(), FILE_WRITE);
  if(!file) return FILE_FAILED_OPENING;

  unsigned long unix = systemClock.getEpochTime();
  DateTime now = DateTime(unix);

  file.print(now.year());
  file.print("/");
  file.print(now.month());
  file.print("/");
  file.print(now.day());
  file.print(" ");



  if (now.hour() < 10)
  {
    file.print(0);
  }

  file.print(now.hour());
  file.print(":");

  if (now.minute() < 10)
  {
    file.print(0);
  }

  file.print(now.minute());
  file.print(":");

  if (now.second() < 10)
  {
    file.print(0);
  }

  file.print(now.second());

  file.print(log_level == sd_log_level_info ? " [INFO] " : " [ERROR] ");

  char message[256];
  //va_list ap;
  //va_start(ap, format);
  int message_length = vsnprintf(message, 256, format, args);
  //va_end(ap);

  if (message_length < 0)
  {
    Serial.println("Failed encoding log message (!)");
  }
  else
  {
    file.println(message);
    //Serial.println(message);
  }
  file.close();
}


int SDLoggerClass::logInfo(char const* const format, ...){
    va_list args;
    va_start(args, format);
    int result = log(sd_log_level_info, format, args);
    va_end(args);
    return result;
}

int SDLoggerClass::logError(char const* const format, ...){
    va_list args;
    va_start(args, format);
    int result = log(sd_log_level_error, format, args);
    va_end(args);
    return result;
}

//SDLoggerClass SDLogger;
