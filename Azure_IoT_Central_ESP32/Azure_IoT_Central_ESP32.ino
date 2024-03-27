// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/*
 * This is an Arduino-based Azure IoT Central sample specific for Espressif ESP32.
 * It uses our Azure Embedded SDK for C to help interact with Azure IoT.
 * For reference, please visit https://github.com/azure/azure-sdk-for-c and
 * https://azureiotcentral.com/.
 *
 * To connect and work with Azure IoT Hub you need an MQTT client, connecting, subscribing
 * and publishing to specific topics to use the messaging features of the hub.
 * Our azure-sdk-for-c is an MQTT client support library, helping composing and parsing the
 * MQTT topic names and messages exchanged with the Azure IoT Hub.
 *
 * The additional layers in this sketch provide a structured use of azure-sdk-for-c and
 * the MQTT client of your choice to perform all the steps needed to connect and interact with
 * Azure IoT Central.
 *
 * AzureIoT.cpp contains a state machine that implements those steps, plus abstractions to simplify
 * its overall use. Besides the basic configuration needed to access the Azure IoT services,
 * all that is needed is to provide the functions required by that layer to:
 * - Interact with your MQTT client,
 * - Perform data manipulations (HMAC SHA256 encryption, Base64 decoding and encoding),
 * - Receive the callbacks for Plug and Play properties and commands.
 *
 * Azure_IoT_PnP_Template.cpp contains the actual implementation of the IoT Plug and Play template
 * specific for the Espressif ESP32 board.
 *
 * To properly connect to your Azure IoT services, please fill the information in the
 * `iot_configs.h` file.
 */


#include <esp_task_wdt.h>

#define WDT_TIMEOUT 2*60 //in seconds


// For hmac SHA256 encryption
#include <ECCX08.h>

// Additional sample headers
#include <clockModule.h>
#include <LogModule.h>
#include <EthernetModule.h>

#include "src/config/AzureDevices.h"
#include "src/config/DataHubCollection.h"
#include "src/config/energyMeters.h"

#include "src/collections/DeviceCollections/DeviceCollection.h"
#include "src/collections/DataHubCollection/DataHubCollection.h"
#include "src/collections/AzureIoTCollection/AzureIoTCollection.h"
#include "src/collections/SDBackaupSenderCollection/SDBackupSenderCollection.h"
#include "src/collections/TriggerCollection/TriggerCollection.h"
#include "src/classes/SDFolderManager/SDFolderManager.h"
#include "src/classes/WebServer/WebServer.h"
#include "src/classes/PersistentData/PersistentDataClass.h"
#include "src/classes/SystemConfigurator/SystemConfigurator.h"

#include <ArduinoBearSSL.h>



/*
 * See the documentation of `get_time_t` in AzureIoT.h for details.
 */
static unsigned long get_time()
{
    return systemClock.getEpochTime();
}



/* --- Arduino setup and loop Functions --- */
void setup()
{
  Serial.begin(SERIAL_LOGGER_BAUD_RATE);
  set_logging_function(logging_function);
  set_logging_function_2(logging_function_2);
  // delay(10000);
  Serial.println("Welcome!");

  EthernetModule.init();
  systemClock.begin();
  ArduinoBearSSL.onGetTime(get_time); // Required for server trusted root validation.

  PersistentDataModule.begin();
  DataHubCollection.init();
  DeviceCollection.init();
  AzureIoTCollection.init();
  TriggerCollection.init();
  SDBackupSenderCollection.init();

  #ifdef USING_WEB_SERVER  
  DeviceCollection.createDevices(); //Web Server Only
  AzureIoTCollection.configure(); //Web Server Only
  #endif 

  #ifndef USING_WEB_SERVER
  createObjects();      //No Web Sever
  configureAzureDevices();  //No Web Sever
  setAzureIoTCollectionDevices(); //No Web Sever
  
  configureDeviceCollection(); //No Web Sever
  setTriggers();  //No Web Sever
  setDataHubCollection();   //No Web Sever
  setDataHubsPayloadGenerators();   //No Web Sever
  #endif

  #ifdef USING_WEB_SERVER
  if(digitalRead(DI_7)){
    WebServer.setAP();
    WebServer.setServer();
    while(1){}
  }

  AzureIoTCollection.createObjects(); //Web Server Only. This function must be called after WebSever objecte for memory reasons.
  SystemConfigurator.configure();     //Web Server Only
  #endif

  // SDBackupSenderCollection.begin();
  DeviceCollection.initFlowMeters();
  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch

  
  LogInfo("Let's go to the looP function");
}




// unsigned long prevTcpTime = 0;
// static const unsigned long TCP_UPDATE_FREQUENCY = 60*1000;

// unsigned long prevNoTcpTime = 0;
// static const unsigned long NO_TCP_UPDATE_FREQUENCY = 60*1000;

unsigned long prevTime = 0;
static const unsigned long DELTA_TIME = 60*1000;

bool  networkUp = false;
bool  clockRunning = false;
int prevLinkStatus = LinkON;
// unsigned long prevEthernetLoop = 0;
// static const unsigned long ETHERNET_FREQUENCY = 100;

void loop()
{
  esp_task_wdt_reset();

  EthernetModule.loop();
  networkUp = EthernetModule.isNetworkUp();
  systemClock.loop(networkUp);
  clockRunning = systemClock.clockRunning();

  if(!networkUp){
    AzureIoTCollection.stop();
  }

  if(clockRunning){
    TriggerCollection.loop(networkUp);
    DeviceCollection.loop();

  } 

  if(networkUp){
    AzureIoTCollection.loop();
    DataHubCollection.loop();
    DeviceCollection.sendDevicesProperties();
    // SDBackupSenderCollection.loop();
  }



  if(millis()-prevTime>DELTA_TIME){
    prevTime = millis();
    LogInfo("Link status: %i", Ethernet.linkStatus());
  }

}
