#pragma once

#include <Arduino.h>




typedef enum sd_log_level_t_enum
{
  sd_log_level_info,
  sd_log_level_error
} sd_log_level_t;


class SDLoggerClass{
    public:
        SDLoggerClass(char* directory, char* filename) : directory(directory), filename(filename){};
        int log(String line);
        int log(char* line);

        int log(sd_log_level_t log_level, char const* const format, ...);
        int log(sd_log_level_t log_level, char const* const format, va_list args);
        int logInfo(char const* const format, ...);
        int logError(char const* const format, ...);

    private:
        char* directory = nullptr;
        char* filename = nullptr;

};


//extern SDLoggerClass SDLogger;