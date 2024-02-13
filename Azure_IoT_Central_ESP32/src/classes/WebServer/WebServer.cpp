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


AsyncWebServer server(80);
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



//Simulated values for the current values of Azure configuration.
//In the final application, those will be variables that are linked to the actual state.
//  String gatewayDeviceId = "sd8qf79asd";
//  String scopeId = "qw9742asd";
//  String groupPrimaryKey = "QW=as7891gasd41312qasG";
//  String weidosModelId = "fs874sdasd";
//  String em3BasicLineId = "4k71561bnm";
//  String em1BasicLineId = "cl471asd3";


// String azureProcessor(const String& var){
//   Serial.println(var);
//   int length = var.length();
//   String tempString = var.substring(0, length-1);
//   //Serial.print("tempString: ");
//   //Serial.println(tempString);
//   if(tempString == "deviceId"){
//     int slot = String(var.charAt(length-1)).toInt();

//     //Serial.print("Slotus: ");
//     //Serial.println(slot);
//     //Serial.print("Getting device ID by calling DeviceCollection.getDeviceId(slot): ");
//     //Serial.println(AzureDeviceCollection.getDeviceId(slot));
//     return String(AzureDeviceCollection.getDeviceId(slot));
//     //return gatewayDeviceId;
//   }
//   if(tempString == "deviceKey"){
//     int slot = String(var.charAt(length-1)).toInt();
//     return String(AzureDeviceCollection.getDeviceSasKey(slot));
//     //return gatewayDeviceId;
//   }

//   if(var == "gwDeviceId") return String(AzureDeviceCollection.getDeviceId(0));
//   if(var == "gwKey"){
//     String gwKeyStrin = String(AzureDeviceCollection.getDeviceSasKey(0));
//     Serial.println("Received gateway sasky: ");
//     Serial.println(gwKeyStrin);
//     return gwKeyStrin;
//   } 
//   if(var == "scopeId") return String(AzureDeviceCollection.getScopeId());
//   if(var == "groupPrimaryKey") return groupPrimaryKey;
//   if(var == "weidosModelId") return weidosModelId;
//   if(var == "em3BasicLineId") return em3BasicLineId;
//   if(var == "em1BasicLineId") return em1BasicLineId;
//   return String();
// }



// String peripheralsProcessor(const String& var){
//   if(var == "EM1") return DeviceCollection.getEnergyMeterName(0);
//   if(var == "EM2") return DeviceCollection.getEnergyMeterName(1);
//   if(var == "EM3") return DeviceCollection.getEnergyMeterName(2);
//   if(var == "EM4") return DeviceCollection.getEnergyMeterName(3);
//   if(var == "EM5") return DeviceCollection.getEnergyMeterName(4);

//   int CF;
//   if(var == "CT1Primary"){
//     PersistentDataModule.getConversionFactor(CF, 0, true);
//     Serial.print("Preprocessor ct1: ");
//     Serial.println(String(CF));
//     return String(CF);
//   }
//   if(var == "CT1Secondary"){
//     PersistentDataModule.getConversionFactor(CF, 0, false);
//     return String(CF);
//   }

//   if(var == "CT2Primary"){
//     PersistentDataModule.getConversionFactor(CF, 1, true);
//     return String(CF);
//   }
//   if(var == "CT2Secondary"){
//     PersistentDataModule.getConversionFactor(CF, 1, false);
//     return String(CF);
//   } 

//   if(var == "CT3Primary"){
//     PersistentDataModule.getConversionFactor(CF, 2, true);
//     return String(CF);
//   }
//   if(var == "CT3Secondary"){
//     PersistentDataModule.getConversionFactor(CF, 2, false);
//     return String(CF);
//   } 

//   if(var == "CT4Primary"){
//     PersistentDataModule.getConversionFactor(CF, 3, true);
//     return String(CF);
//   }
//   if(var == "CT4Secondary"){
//     PersistentDataModule.getConversionFactor(CF, 3, false);
//     return String(CF);
//   } 

//   if(var == "CT5Primary"){
//     PersistentDataModule.getConversionFactor(CF, 4, true);
//     return String(CF);
//   }
//   if(var == "CT5Secondary"){
//     PersistentDataModule.getConversionFactor(CF, 4, false);
//     return String(CF);
//   } 

//   return String();
// }



bool isValid = true;

void WebServerClass::setServer()
{
  //* Set each endpoint and its callback function---

    server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", wifiForm, wifiProcessor);
    });



    // server.on("/wifi", HTTP_POST, [](AsyncWebServerRequest *request)
    // {
    //   int params = request->params();
    //   Serial.print("Number of parameters: ");
    //   Serial.println(params);

    //   if(params == 2){
    //     String ssid = request->getParam(0)->value();
    //     Serial.print("SSID: ");
    //     Serial.println(ssid);

    //     if(isValid){
    //       PersistentDataModule.setWiFiSSID(ssid);
    //     }

    //     String password = request->getParam(1)->value();
    //     Serial.print("Password: ");
    //     Serial.println(password);

    //     if(isValid){
    //       PersistentDataModule.setWiFiPass(password);
    //     }
    //   }

    //   request->send_P(200, "text/html", "WiFi Posted!");
    // });



    // server.on("/azure", HTTP_GET, [](AsyncWebServerRequest *request)
    // {
    //   request->send_P(200, "text/html", azureForm, azureProcessor);
    // });



    // server.on("/azure", HTTP_POST, [](AsyncWebServerRequest *request)
    // {
    //   int params = request->params();
    //   Serial.print("Number of parameters: ");
    //   Serial.println(params);

    //   int i = 0;

    //   if(params == 18){
    //     //Serial.println("18");
        
    //     String userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceId(userInput, 0);
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceSasKey(userInput, 0);

    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceId(userInput, 1);
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceSasKey(userInput, 1);

    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceId(userInput, 2);
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceSasKey(userInput, 2);

    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceId(userInput, 3);
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceSasKey(userInput, 3);
 
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceId(userInput, 4);
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceSasKey(userInput, 4);

    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceId(userInput, 5);
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setDeviceSasKey(userInput, 5);



    //     userInput = request->getParam(i++)->value();    //Device name
        
    //     userInput = request->getParam(i++)->value();
    //     AzureDeviceCollection.setScopeId(userInput);
    //   }
      

    //   request->send_P(200, "text/html", "Azure parameters Posted!");
    // });



    // server.on("/energy-meters", HTTP_GET, [](AsyncWebServerRequest *request)
    // {
    //   request->send_P(200, "text/html", energyMetersForm, peripheralsProcessor);
    // });



    // server.on("/energy-meters", HTTP_POST, [](AsyncWebServerRequest *request)
    // {
    //   int params = request->params();
    //   Serial.print("Number of parameters: ");
    //   Serial.println(params);

    //   if(params == 15){
    //     String EM0 = request->getParam(0)->value();
    //     DeviceCollection.setDevice(EM0, 0);
    //     String CT0Primary = request->getParam(1)->value();
    //     String CT0Secondary = request->getParam(2)->value();
    //     PersistentDataModule.saveConversionFactor(CT0Primary.toInt(), 0, true);
    //     PersistentDataModule.saveConversionFactor(CT0Secondary.toInt(), 0, false);

    //     String EM1 = request->getParam(3)->value();
    //     DeviceCollection.setDevice(EM1, 1);
    //     String CT1Primary = request->getParam(4)->value();
    //     String CT1Secondary = request->getParam(5)->value();
    //     PersistentDataModule.saveConversionFactor(CT1Primary.toInt(), 1, true);
    //     PersistentDataModule.saveConversionFactor(CT1Secondary.toInt(), 1, false);

    //     String EM2 = request->getParam(6)->value();
    //     DeviceCollection.setDevice(EM2, 2);
    //     String CT2Primary = request->getParam(7)->value();
    //     String CT2Secondary = request->getParam(8)->value();
    //     PersistentDataModule.saveConversionFactor(CT2Primary.toInt(), 2, true);
    //     PersistentDataModule.saveConversionFactor(CT2Secondary.toInt(), 2, false);


    //     String EM3 = request->getParam(9)->value();
    //     DeviceCollection.setDevice(EM3, 3);
    //     String CT3Primary = request->getParam(10)->value();
    //     String CT3Secondary = request->getParam(11)->value();
    //     PersistentDataModule.saveConversionFactor(CT3Primary.toInt(), 3, true);
    //     PersistentDataModule.saveConversionFactor(CT3Secondary.toInt(), 3, false);


    //     String EM4 = request->getParam(12)->value();
    //     DeviceCollection.setDevice(EM4, 4);
    //     String CT4Primary = request->getParam(13)->value();
    //     String CT4Secondary = request->getParam(14)->value();
    //     PersistentDataModule.saveConversionFactor(CT4Primary.toInt(), 4, true);
    //     PersistentDataModule.saveConversionFactor(CT4Secondary.toInt(), 4, false);
    //   }
      
    //   request->send_P(200, "text/html", "Energy Meters posted!");
    // });


    // server.on("/flow-meters", HTTP_GET, [](AsyncWebServerRequest *request)
    // {
    //   request->send_P(200, "text/html", "Flow Meters!");
    // });



    // server.on("/flow-meters", HTTP_POST, [](AsyncWebServerRequest *request)
    // {      
    //   request->send_P(200, "text/html", "Flow Meters posted!");
    // });


    // server.on("/pulse-meters", HTTP_GET, [](AsyncWebServerRequest *request)
    // {
    //   request->send_P(200, "text/html", "Pulse Meters!");
    // });



    // server.on("/pulse-meters", HTTP_POST, [](AsyncWebServerRequest *request)
    // {      
    //   request->send_P(200, "text/html", "Pulse Meters posted!");
    // });


    // server.onNotFound([](AsyncWebServerRequest *request)
    // {
    //   request->send(404, "text/html", homePage);
    // });






  server.on("/devices", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      AsyncResponseStream *response = request->beginResponseStream("text/html");
      sendDevicesPage(response);
      request->send(response);
      //request->send_P(200, "text/html", homePage);
    });

  
  server.on("/deviceForm", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      if(request->hasParam("slot")){
        Serial.println("Yes it has");
        String slot = request->getParam("slot")->value();
        int slotInt = slot.toInt();
        Serial.print("Slot is: ");
        Serial.println(slotInt);
       } else Serial.println("No, it hasn't");
      AsyncResponseStream *response = request->beginResponseStream("text/html");
      sendDeviceFormPage(response);
      request->send(response);
      //request->send_P(200, "text/html", homePage);
    });


    //server.on("/deviceForm", HTTP_GET, onDevicePost);
    server.on("/deviceForm", HTTP_POST, onDevicePost);
 


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/html", homePage);
    });

  server.begin();
}






WebServerClass WebServer;
