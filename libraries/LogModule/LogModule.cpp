#include <LogModule.h>
#include <clockModule.h>

/* --- Logging --- */
#ifndef DISABLE_LOGGING
log_function_t default_logging_function = NULL;
//#endif // DISABLE_LOGGING

void logging_function(log_level_t log_level, char const* const format, ...)
{
  unsigned long unix = systemClock.getEpochTime();
  DateTime now = DateTime(unix);

  Serial.print(now.year());
  Serial.print("/");
  Serial.print(now.month() + 1);
  Serial.print("/");
  Serial.print(now.day());
  Serial.print(" ");



  if (now.hour() < 10)
  {
    Serial.print(0);
  }

  Serial.print(now.hour());
  Serial.print(":");

  if (now.minute() < 10)
  {
    Serial.print(0);
  }

  Serial.print(now.minute());
  Serial.print(":");

  if (now.second() < 10)
  {
    Serial.print(0);
  }

  Serial.print(now.second());

  Serial.print(log_level == log_level_info ? " [INFO] " : " [ERROR] ");

  char message[256];
  va_list ap;
  va_start(ap, format);
  int message_length = vsnprintf(message, 256, format, ap);
  va_end(ap);

  if (message_length < 0)
  {
    Serial.println("Failed encoding log message (!)");
  }
  else
  {
    Serial.println(message);
  }
}





log_function_2_t default_logging_function_2 = NULL;
//#endif // DISABLE_LOGGING

void logging_function_2(log_level_t log_level, const __FlashStringHelper* const format, ...)
{
  unsigned long unix = systemClock.getEpochTime();
  DateTime now = DateTime(unix);

  Serial.print(now.year());
  Serial.print("/");
  Serial.print(now.month() + 1);
  Serial.print("/");
  Serial.print(now.day());
  Serial.print(" ");



  if (now.hour() < 10)
  {
    Serial.print(0);
  }

  Serial.print(now.hour());
  Serial.print(":");

  if (now.minute() < 10)
  {
    Serial.print(0);
  }

  Serial.print(now.minute());
  Serial.print(":");

  if (now.second() < 10)
  {
    Serial.print(0);
  }

  Serial.print(now.second());

  Serial.print(log_level == log_level_info ? " [INFO] " : " [ERROR] ");

  char message[256];
  va_list ap;
  // va_start(ap, format);
  // int message_length = vsnprintf(message, 256, format, ap);
  // va_end(ap);

  String formatString = String(format);
  va_start(ap, formatString.c_str());
  int message_length = vsnprintf(message, 256, formatString.c_str(), ap);
  va_end(ap);

  if (message_length < 0)
  {
    Serial.println("Failed encoding log message (!)");
  }
  else
  {
    Serial.println(message);
  }
}

#endif // DISABLE_LOGGING