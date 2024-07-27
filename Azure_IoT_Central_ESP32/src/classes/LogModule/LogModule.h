#pragma once


#define SERIAL_LOGGER_BAUD_RATE 115200
//#define DISABLE_LOGGING
/* --- Logging --- */
#ifndef DISABLE_LOGGING
typedef enum log_level_t_enum
{
  log_level_info,
  log_level_error
} log_level_t;

typedef void (*log_function_t)(log_level_t log_level, char const* const format, ...);

extern log_function_t default_logging_function;

#define set_logging_function(custom_logging_function) \
  default_logging_function = custom_logging_function;

#define Log(level, message, ...) default_logging_function(level, message, ##__VA_ARGS__)
#define LogInfo(message, ...) Log(log_level_info, message, ##__VA_ARGS__)
#define LogError(message, ...) Log(log_level_error, message, ##__VA_ARGS__)
void logging_function(log_level_t log_level, char const* const format, ...);
#else
#define set_logging_function(custom_logging_function)
#define Log(level, message, ...)
#define LogInfo(message, ...)
#define LogError(message, ...)
#endif // DISABLE_LOGGING


//void logging_function(log_level_t log_level, char const* const format, ...);
