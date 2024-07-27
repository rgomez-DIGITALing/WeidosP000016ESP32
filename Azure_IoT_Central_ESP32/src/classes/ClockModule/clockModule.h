#pragma once

#include <NTPClient.h>
#include <RTClib.h>



enum ClockSource{
    NONE_CLOCK,
    NTP_CLOCK,
    RTC_CLOCK
};

class ClockModuleClass{
    public:
        ClockModuleClass(NTPClient& ntpClock, RTC_DS3231& rtcClock);
        
        void begin();
        bool update();
        void loop();
        unsigned long getEpochTime();
        bool isRTCset();
        bool clockRunning() { return clockSource != NONE_CLOCK; }
        ClockSource getClockSource(){ return clockSource; }
        unsigned long getClockDifference(){ return (ntpClock.getEpochTime() - DateTime(rtcClock.now()).unixtime()); }
        String clockSourceString();
        
    private:
        bool begun = false;
        ClockSource clockSource = NONE_CLOCK;
        NTPClient& ntpClock;
        RTC_DS3231& rtcClock;
};


extern ClockModuleClass systemClock;
