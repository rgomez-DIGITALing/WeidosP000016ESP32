#include "EthernetModule.h"
#include <Ethernet.h>
#include <WiFi.h>
#include <LogModule.h>
#include <SDLogger.h>


char ethDirectory[] = "sysLog/modules/ethernet";
char ethFilename[]= "ethernet.txt";

// SDLoggerClass ethernetSDLogger(ethDirectory, ethFilename);

uint8_t mac[] = {0, 0, 0, 0, 0, 0};
static const unsigned long ETH_DEFAULT_TIMEOUT = 10000;   //In Ethernet library this is set to 60s (60000)
static const unsigned long ETH_RESPONSE_TIMEOUT = 4000;   //In Ethernet library this is set to 4s (4000)

void EthernetModuleClass::init(){
    Ethernet.init(ETHERNET_CS);
    WiFi.macAddress(mac);
    mac[5] = mac[5] + 1;
    // ethernetSDLogger.logInfo("Initializing Ethernet module with mac address: %i;%i;%i;%i;%i;%i", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void EthernetModuleClass::loop(){
    linkStatusChange();
    
    if(Ethernet.linkStatus() != LinkON && networkUp){
        // ethernetSDLogger.logError("Ethernet disconnected. Link status not ON");
        networkUp = false;
        return;
    }

    if(Ethernet.linkStatus() == LinkON && !networkUp) begin();
    
    if(networkUp) maintain();


    return;
}

bool EthernetModuleClass::begin(){
    networkUp = true;

    if(localIp && dns && gateway && submask){
        Ethernet.begin(mac, *localIp, *dns, *gateway, *submask);
        // ethernetSDLogger.logInfo("Ethernet started with static IP: %s, DNS IP: %s, Gateway IP: %s and submask: %s", localIp->toString().c_str(), dns->toString().c_str(), gateway->toString().c_str(), submask->toString().c_str());
        
        return true;
    }
    
    if(localIp && dns && gateway){
        Ethernet.begin(mac, *localIp, *dns, *gateway);
        // ethernetSDLogger.logInfo("Ethernet started with static IP: %s, DNS IP: %s and Gateway IP: %s", localIp->toString().c_str(), dns->toString().c_str(), gateway->toString().c_str());
        return true;
    }

    if(localIp && dns){
        Ethernet.begin(mac, *localIp, *dns);
        // ethernetSDLogger.logInfo("Ethernet started with static IP: %s and DNS: %s", localIp->toString().c_str(), dns->toString().c_str());
        return true;
    }
    
    if(localIp){
        Ethernet.begin(mac, *localIp);
        // ethernetSDLogger.logInfo("Ethernet started with static IP: %s.", localIp->toString().c_str());
        return true;
    }

    if(Ethernet.begin(mac, ETH_DEFAULT_TIMEOUT, ETH_RESPONSE_TIMEOUT)){
        // ethernetSDLogger.logInfo("DHCP Ethernet begin successfull. Given IP: %s", Ethernet.localIP().toString().c_str());
        return true;
    }else{
        // ethernetSDLogger.logError("DHCP Ethernet begin NOT successfull.");
        networkUp = false;
        return false;
    }

     
}

void EthernetModuleClass::linkStatusChange(){

    if(Ethernet.linkStatus() != prevLinkStatus){
        LogInfo("Link status change: %i", Ethernet.linkStatus());
        // ethernetSDLogger.logInfo("Link status change: %s", getLinkStatusName());
    }

    prevLinkStatus = Ethernet.linkStatus();
    return;
}


void EthernetModuleClass::setLocalIp(IPAddress* localIp){ 
    this->localIp = localIp;
    // ethernetSDLogger.logInfo("Local IP Address set to %s", localIp->toString().c_str());
}

void EthernetModuleClass::setGateway(IPAddress* gateway){
    this->gateway = gateway;
    // ethernetSDLogger.logInfo("Gateway IP Address set to %s", gateway->toString().c_str());
}

void EthernetModuleClass::setSubmask(IPAddress* submask){ 
    this->submask = submask;
    // ethernetSDLogger.logInfo("Submask set to %s", submask->toString().c_str());
}

void EthernetModuleClass::setDns(IPAddress* dns){ 
    this->dns = dns;
    // ethernetSDLogger.logInfo("DNS set to %s", dns->toString().c_str());

}


char LINK_UNKNOWN[] = "Unknown";
char LINK_ON[] = "LinkON";
char LINK_OFF[] = "LinkOFF";
char UNDEFINED_STATE[] = "Undefined state";

char* EthernetModuleClass::getLinkStatusName(){
    int linkStatus = Ethernet.linkStatus();
    if(linkStatus == Unknown) return LINK_UNKNOWN;
    if(linkStatus == LinkON) return LINK_ON;
    if(linkStatus == LinkOFF) return LINK_OFF;

    return UNDEFINED_STATE;
}

char RENEW_OK[] = "RENEW OK";
char REBIND_OK[] = "REBIND OK";
char RENEW_FAIL[] = "RENEW FAIL";
char REBIND_FAIL[] = "REBIND_FAIL";


char* EthernetModuleClass::getMaintainResultName(int rc){
    if(rc == DHCP_CHECK_RENEW_OK) return RENEW_OK;
    if(rc == DHCP_CHECK_REBIND_OK) return REBIND_OK;
    if(rc == DHCP_CHECK_RENEW_FAIL) return RENEW_FAIL;
    if(rc == DHCP_CHECK_REBIND_FAIL) return REBIND_FAIL;

    return UNDEFINED_STATE;
}



int EthernetModuleClass::maintain(){
    int rc = Ethernet.maintain();

    if(rc == DHCP_CHECK_RENEW_FAIL || rc == DHCP_CHECK_REBIND_FAIL) {
        // ethernetSDLogger.logError("Maintain resul: %s", getMaintainResultName(rc));
        return rc;
    }

    // if(rc != DHCP_CHECK_NONE) ethernetSDLogger.logInfo("Maintain resul: %s", getMaintainResultName(rc));

    return rc;
}


EthernetModuleClass EthernetModule;
