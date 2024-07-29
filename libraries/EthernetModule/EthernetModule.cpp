#include "EthernetModule.h"
#include <Ethernet.h>
#include <WiFi.h>
#include "../LogModule/LogModule.h"

//uint8_t mac[] = {0, 0, 0, 0, 0, 0};

void EthernetModuleClass::init(){
    Ethernet.init(ETHERNET_CS);
    WiFi.macAddress(mac);
    mac[5] = mac[5] + 1;

    return;
}

void EthernetModuleClass::loop(){
    bool linkOn = false;
    if(Ethernet.linkStatus() != LinkON) networkUp = false;
    if(Ethernet.linkStatus() == LinkON && !networkUp){
        if(begin()){
            networkUp = true;
            LogInfo("Ethernet recovered after a failure.");
            LogInfo("Local IP: %s", Ethernet.localIP().toString().c_str());
        }
    }

    if(networkUp) Ethernet.maintain();
    linkStatusChange();

    return;
}

bool EthernetModuleClass::begin(){
    //if(ipSet(localIp) && ipSet(dns) && ipSet(gateway) && ipSet(submask)) return Ethernet.begin(mac, localIp, dns, gateway, submask);
    //if(ipSet(localIp) && ipSet(dns) && ipSet(gateway)) return Ethernet.begin(mac, localIp, dns, gateway);
    //if(ipSet(localIp) && ipSet(dns)) return Ethernet.begin(mac, localIp, dns);
    //if(ipSet(localIp)) return Ethernet.begin(mac, localIp);

    //if(localIp && dns && gateway && submask) return Ethernet.begin(mac, localIp, dns, gateway, submask);
    //if(localIp && dns && gateway) return Ethernet.begin(mac, localIp, dns, gateway);
    
    if(localIp && dns && gateway && submask){
        Ethernet.begin(mac, *localIp, *dns, *gateway, *submask);
        return true;
    }
    
    if(localIp && dns && gateway){
        Ethernet.begin(mac, *localIp, *dns, *gateway);
        return true;
    }

    if(localIp && dns){
        Ethernet.begin(mac, *localIp, *dns);
        return true;
    }
    if(localIp){
        Ethernet.begin(mac, *localIp);
        return true;
    } 
    return Ethernet.begin(mac);
}

void EthernetModuleClass::linkStatusChange(){
    if(Ethernet.linkStatus() != prevLinkStatus){
        LogInfo("Link status change: %i", Ethernet.linkStatus());
    }
    prevLinkStatus = Ethernet.linkStatus();

    return;
}


EthernetModuleClass EthernetModule;