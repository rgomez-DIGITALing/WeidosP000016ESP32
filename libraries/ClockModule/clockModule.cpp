#include "clockModule.h"
// #include <SDLogger.h>

#include <Ethernet.h>
// #include <WiFi.h>





#define REFERENCE_TIME 1683756000      //This unix time corresponds to 11/05/2023 (DD/MM/YYYY)
char clockDirectory[] = "sysLog/modules/clock";
char clockFilename[]= "clock.txt";

// SDLoggerClass clockSDLogger(clockDirectory, clockFilename);


ClockModuleClass::ClockModuleClass(NTPClient& ntpClock, RTC_DS3231& rtcClock) : ntpClock(ntpClock), rtcClock(rtcClock){}

static const char* ntpServer = "pool.ntp.org";

void ClockModuleClass::loop(bool networkUp){
    if(!begun){
        begin();
        begun = true;
    }

    if(networkUp) update();

    logClockState();

    return;
}

void ClockModuleClass::begin(){
    rtcClock.begin();
    if(isRTCset()) clockSource = RTC_CLOCK;
    ntpClock.setUpdateInterval(updateInterval);
    ntpClock.setPoolServerName(ntpServer);
    // clockSDLogger.logInfo("Clock module initialized.\n\t\t\tNTP server: %s.\n\t\t\tUpdate Interval: %i.\n\t\t\tSource clock: %s", ntpServer, updateInterval, getClockSourceName());

    return;
}



bool ClockModuleClass::update(){
    if(ntpClock.update()){
        unsigned long currentEpoch = ntpClock.getEpochTime();
        rtcClock.adjust(DateTime(currentEpoch));
        clockSource = NTP_CLOCK;
        // clockSDLogger.logInfo("Clock updated.");
        Serial.println("Clock updated!");
        ntpClock.end();
        return true;
    }
    ntpClock.end();
    return false;
}




unsigned long ClockModuleClass::getEpochTime(){
    if(clockSource == NTP_CLOCK){
        return ntpClock.getEpochTime();
    }

    if(clockSource == RTC_CLOCK){
        DateTime now = rtcClock.now();
        return now.unixtime();
    }

    return 0;
}



bool ClockModuleClass::isRTCset(){
    DateTime now = rtcClock.now();
    unsigned long unix = now.unixtime();
    
    if(unix<REFERENCE_TIME) return false;

    
    return true;
}

const char clockSourceNone[] = "None";
const char clockSourceNTP[] = "NTP";
const char clockSourceRTC[] = "RTC";

String ClockModuleClass::clockSourceString(){
    if(clockSource == NONE_CLOCK) return String("None");
    if(clockSource == NTP_CLOCK) return String("NTP");
    if(clockSource == RTC_CLOCK) return String("RTC");
    return String();
}


const char* ClockModuleClass::getClockSourceName(){
    if(clockSource == NONE_CLOCK) return clockSourceNone;
    if(clockSource == NTP_CLOCK) return  clockSourceNTP;
    if(clockSource == RTC_CLOCK) return  clockSourceRTC;
    return "Undefined";
}





void ClockModuleClass::logClockState(){
    if(millis() - lastLogTime > logFrequency){
        lastLogTime = millis();
        // clockSDLogger.logInfo("Clock source is: %s", getClockSourceName());
        // clockSDLogger.logInfo("Current epoch timestamp: %i", getEpochTime());
    }

    return;
}


// WiFiUDP udpClient;
EthernetUDP udpClient;
NTPClient ntpClock(udpClient);
RTC_DS3231 rtcClock;
ClockModuleClass systemClock( ntpClock, rtcClock);
