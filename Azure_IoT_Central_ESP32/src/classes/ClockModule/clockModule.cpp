#include "clockModule.h"
#include <Ethernet.h>
//#include <WiFi.h>
#include "../LogModule/LogModule.h"


//WiFiUDP udpClient;
EthernetUDP udpClient;
NTPClient ntpClock(udpClient);
RTC_DS3231 rtcClock;
ClockModuleClass systemClock( ntpClock, rtcClock);


#define REFERENCE_TIME 1683756000      //This unix time corresponds to 11/05/2023 (DD/MM/YYYY)


ClockModuleClass::ClockModuleClass(NTPClient& ntpClock, RTC_DS3231& rtcClock) : ntpClock(ntpClock), rtcClock(rtcClock){}

static const unsigned long DEFAULT_UPDATE_INTERVAL =  60*60*1000; //In ms
static const char* ntpServer = "pool.ntp.org";

void ClockModuleClass::loop(){
    if(!begun){
        begin();
        begun = true;
    }

    update();
    return;
}

void ClockModuleClass::begin(){
    rtcClock.begin();
    if(isRTCset()) clockSource = RTC_CLOCK;
    ntpClock.begin();

    ntpClock.setUpdateInterval(DEFAULT_UPDATE_INTERVAL);
    ntpClock.setPoolServerName(ntpServer);

    return;
}



bool ClockModuleClass::update(){
    if(ntpClock.update()){
        LogInfo("NTP clock updated!");
        unsigned long currentEpoch = ntpClock.getEpochTime();
        rtcClock.adjust(DateTime(currentEpoch));
        clockSource = NTP_CLOCK;
        return true;
    }
    
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


String ClockModuleClass::clockSourceString(){
    if(clockSource == NONE_CLOCK) return String("None");
    if(clockSource == NTP_CLOCK) return String("NTP");
    if(clockSource == RTC_CLOCK) return String("RTC");
    return String();
}