#pragma once

#include "WebServer.h"
#include <Arduino.h>
#include <WiFi.h>


// #include "../PersistentData/PersistentDataClass.h"
// #include "../../collections/DeviceCollectionS/DeviceCollection.h"
// #include "../../collections/AzureIoTCollection/AzureIoTCollection.h"


#include "./html/pages.h"
#include "pages/devicesPage.h"
#include "RequestHandlerFunctions/handlerFunctions.h"
// #include <E2PROM.h>
// #include "config.h"

#include <Arduino.h>


//SSID and password for the Access Point generated WiFi for user configuration inputs.
static const IPAddress AP_IP(192, 168, 6, 1);
static const IPAddress AP_MASK(255, 255, 255, 0);

#define CONFIG_AP_SSID "WeidosESP32WiFi"
#define CONFIG_AP_PASS "Detmold1"           //Last char is a one (do not confuse with an L)

const char *AP_SSID = CONFIG_AP_SSID;
const char *AP_PASSWORD = CONFIG_AP_PASS;  



bool WebServerClass::setAP(){
  if(WiFi.softAP(AP_SSID, AP_PASSWORD)){
    WiFi.softAPConfig(AP_IP, INADDR_NONE, AP_MASK);
    Serial.print("Access Point set with SSID: ");
    Serial.print(AP_SSID);
    Serial.print(" and password: ");
    Serial.println(AP_PASSWORD);

    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
    return true;
  }else{
    Serial.println("Access Point has not been set.");
    return false;
  }
}





//Simulated values for the current WiFi parameters. 
//In the final application, those will be variables that are linked to the actual state.
String ssid = "IoT_Hub";
String pass = "Detmold";
String wifiProcessor(const String& var){
  if(var == "SSID"){
    //char* ssid = PersistentDataModule.getWiFiSSID();
    return String(ssid);
  }
  
  if(var == "password"){
    //char* pass = PersistentDataModule.getWiFiPass();
    return String(pass);
  }
  
  return String();
}



void WebServerClass::setServer()
{
  //* Set each endpoint and its callback function---
    AsyncWebServer* server = new AsyncWebServer(80);
    
    server->on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", wifiForm, wifiProcessor);
    });


  server->on("/devices", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      AsyncResponseStream *response = request->beginResponseStream("text/html");
      sendDevicesPage(response);
      request->send(response);
      //request->send_P(200, "text/html", homePage);
    });

  
  server->on("/deviceForm", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      AsyncResponseStream *response = request->beginResponseStream("text/html");
      
      if(request->hasParam("slot")){
        String slotParam = request->getParam("slot")->value();
        int slotInt = slotParam.toInt();
        sendDeviceFormPage(response, slotInt);
       
       }
      request->send(response);
      //request->send_P(200, "text/html", homePage);
    });


    //server.on("/deviceForm", HTTP_GET, onDevicePost);
    server->on("/deviceForm", HTTP_POST, onDevicePost);
 


  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", homePage);
    });

  server->begin();
}


WebServerClass WebServer;
