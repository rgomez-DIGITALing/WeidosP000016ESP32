#pragma once

#include <NTPClient.h>
#include <RTClib.h>



enum ClockSource{
    NONE_CLOCK,
    NTP_CLOCK,
    RTC_CLOCK
};

const static unsigned long DEFAULT_CLOCK_LOG_FREQUENCY = 5*60*1000;
const static unsigned long DEFAULT_CLOCK_UPDATE_INTERVAL = 60*1000;


class ClockModuleClass{
    public:
        ClockModuleClass(NTPClient& ntpClock, RTC_DS3231& rtcClock);
        void loop(bool networkUp);
        void begin();
        bool update();
        unsigned long getEpochTime();
        bool isRTCset();
        bool clockRunning() { return clockSource != NONE_CLOCK; }
        ClockSource getClockSource(){ return clockSource; }
        unsigned long getClockDifference(){ return (ntpClock.getEpochTime() - DateTime(rtcClock.now()).unixtime()); }
        String clockSourceString();
        const char* getClockSourceName();
        
    private:
        bool begun = false;
        ClockSource clockSource = NONE_CLOCK;
        NTPClient& ntpClock;
        RTC_DS3231& rtcClock;
        unsigned long updateInterval = DEFAULT_CLOCK_UPDATE_INTERVAL;
        unsigned long lastLogTime = 0;
        unsigned long logFrequency = DEFAULT_CLOCK_LOG_FREQUENCY;
        void logClockState();

};


extern ClockModuleClass systemClock;
