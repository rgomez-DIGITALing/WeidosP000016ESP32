#include <Arduino.h>
#include <Ethernet.h>


#define DHCP_CHECK_NONE         (0)
#define DHCP_CHECK_RENEW_FAIL   (1)
#define DHCP_CHECK_RENEW_OK     (2)
#define DHCP_CHECK_REBIND_FAIL  (3)
#define DHCP_CHECK_REBIND_OK    (4)


class EthernetModuleClass{
    public:
        void init();
        void loop();
        bool isNetworkUp(){ return networkUp; }
        void setLocalIp(IPAddress* localIp);
        void setGateway(IPAddress* gateway);
        void setSubmask(IPAddress* submask);
        void setDns(IPAddress* dns);
        
        //bool ipSet(IPAddress ip){ return ip != nullptr; }

    private:
        bool begin();
        int maintain();
        void linkStatusChange();
        char* getLinkStatusName();
        char* getMaintainResultName(int rc);

        uint8_t mac[6];
        int prevLinkStatus = Unknown;
        bool networkUp = false;
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