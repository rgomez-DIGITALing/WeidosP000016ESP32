#pragma once

#include <Arduino.h>
#include <Ethernet.h>




class EthernetModuleClass{
    public:
        void init();
        void loop();
        bool begin();
        void linkStatusChange();
        bool isNetworkUp(){ return networkUp; }
        void setLocalIp(IPAddress* localIp){ this->localIp = localIp; }
        void setGateway(IPAddress* gateway){ this->gateway = gateway; }
        void setSubmask(IPAddress* submask){ this->submask = submask; }
        void setDns(IPAddress* dns){ this->dns = dns; }
        bool ipSet(IPAddress* ip){ return ip != nullptr; }

    private:
        uint8_t mac[6];
        //uint8_t* mac4;
        bool networkUp = false;
        int prevLinkStatus = Unknown;
        IPAddress* localIp = nullptr;
        IPAddress* gateway = nullptr;
        IPAddress* submask = nullptr;
        IPAddress* dns = nullptr;
        //IPAddress localIp = INADDR_NONE;
        //IPAddress gateway = INADDR_NONE;
        //IPAddress submask = INADDR_NONE;
        //IPAddress dns = INADDR_NONE;
};

extern EthernetModuleClass EthernetModule;
