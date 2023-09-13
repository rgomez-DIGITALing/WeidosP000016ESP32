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

/* --- Dependencies --- */
// C99 libraries
#include <cstdarg>
#include <cstdlib>
#include <string.h>
#include <time.h>

// For hmac SHA256 encryption
#include <mbedtls/base64.h>
#include <mbedtls/md.h>
#include <mbedtls/sha256.h>

#define ARDUINO
// Libraries for MQTT client and WiFi connection
//#include <WiFi.h>
#include <ArduinoBearSSL.h>
//#include <ArduinoMqttClient.h>
#include <MQTTClient.h>


// For hmac SHA256 encryption
#include <ECCX08.h>


#include <Ethernet.h>

// Azure IoT SDK for C includes
#include <az_core.h>
#include <az_iot.h>
#include <azure_ca.h>

// Additional sample headers
#include <clockModule.h>
#include <LogModule.h>
#include <EthernetModule.h>
#include <SDLogger.h>
#include "src/classes/AzureIoTClass/AzureIoTClass.h"
//#include "./tasks/energyMeterTask.h"
#include "src/AzureDevices.h"

#include "src/classes/EnergyMeterManager/energyMeterManager.h"

#include "src/classes/WeidosManager/WeidosManager.h"
#include "src/classes/DataHub/DataHub.h"
#include "src/classes/PersistentData/PersistentDataClass.h"
#include "src/classes/WebServer/WebServer.h"
#include "src/classes/WeidosESP32Class/WeidosESP32Class.h"

//#include "Azure_IoT_PnP_Template.h"

#include "src/iot_configs.h"

#include "src/classes/DataHub/DataHub.h"

#include <ArduinoBearSSL.h>
#include "src/classes/PersistentData/PersistentDataClass.h"
#include "src/payloadGenerators.h"

SDLoggerClass mainSDLogger("sysLog/main", "main.txt");

void loopEnergyMeters();
void setEnergyMeterProperties();
void triggerEnergyMeters();
void sendEnergyMeterProperties();


/*
 * See the documentation of `get_time_t` in AzureIoT.h for details.
 */
static unsigned long get_time()
{
    return systemClock.getEpochTime();
}


WeidosESP32Class WeidosESP32;


/* --- Arduino setup and loop Functions --- */
void setup()
{
  Serial.begin(SERIAL_LOGGER_BAUD_RATE);
  set_logging_function(logging_function);
  Serial.println("Welcome!");
  mainSDLogger.logInfo("Welcome!");
  
  EthernetModule.init();
  //connect_to_wifi();
  systemClock.begin();
  ArduinoBearSSL.onGetTime(get_time); // Required for server trusted root validation.

  //azure_pnp_init();
  Serial.println("Let's persist: ");
  mainSDLogger.logInfo("Let's persist:");
  PersistentDataModule.begin();
  Serial.println("Persisten Module has begun!");
  mainSDLogger.logInfo("Persisten Module has begun!");
  Serial.println(PersistentDataModule.getWiFiSSID());
  Serial.println(PersistentDataModule.getScopeId());

  //WebServer.setAP();
  //WebServer.setServer();
  //while(1){}
  
  //char* scopeId = PersistentDataModule.getScopeId();
  
  createObjects();
  fillArray();
  configureAzureDevices();
  setEnergyMeterProperties();


  weidosMetadata_t metadata = WeidosESP32.getMetadata();
  metadata.printMetadata();
  emDataHub.setPayloadGenerator(em750_generete_payload);
  weidosDataHub.setPayloadGenerator(weidosESP32_generete_payload);
  LogInfo("Let's go to the looP function");
  mainSDLogger.logInfo("Let's go to the looP function");
}

unsigned long prevTime = 0;
static const unsigned long DELTA_TIME = 60*1000;

unsigned long prevTime2 = 0;
static const unsigned long DELTA_TIME2 = 2*60*1000;

unsigned long prevTime3 = 0;
static const unsigned long DELTA_TIME3 = 10*1000;


bool  networkUp = false;
bool  clockRunning = false;
int prevLinkStatus = LinkON;

void loop()
{
  EthernetModule.loop();
  networkUp = EthernetModule.isNetworkUp();
  systemClock.loop(networkUp);
  clockRunning = systemClock.clockRunning();
  
  if(!networkUp){
    Azure0->stop();
    Azure1->stop();
    Azure2->stop();
    Azure3->stop();
    Azure4->stop();
    Azure5->stop();
  }





  if(networkUp && clockRunning){
    if(millis()-prevTime>DELTA_TIME){
      triggerEnergyMeters();
      weidosESP32Manager.triggerUpdate();
      prevTime = millis();
    }
  }



  if(networkUp){
    weidosESP32Manager.loop();
    loopEnergyMeters();
  }


  if(networkUp){
    emDataHub.loop();
    weidosDataHub.loop();
  }

  if(networkUp){
    sendEnergyMeterProperties();
  }


  if(networkUp){
    Azure0->loop();
    Azure1->loop();
    Azure2->loop();
    Azure3->loop();
    Azure4->loop();
    Azure5->loop();
  }

  Azure0->statusChange();
  Azure1->statusChange();
  Azure2->statusChange();
  Azure3->statusChange();
  Azure4->statusChange();
  Azure5->statusChange();

  if(millis()-prevTime3>DELTA_TIME3){
    prevTime3 = millis();
    // LogInfo("Azure0 state: %i", Azure0->getStatus());
    // LogInfo("Azure1 state: %i", Azure1->getStatus());
    // LogInfo("Azure2 state: %i", Azure2->getStatus());
    // LogInfo("Azure3 state: %i", Azure3->getStatus());
    // LogInfo("Azure4 state: %i", Azure4->getStatus());
    // LogInfo("Azure5 state: %i", Azure5->getStatus());
    mainSDLogger.logInfo("Azure0 state: %i", Azure0->getStatus());
    mainSDLogger.logInfo("Azure1 state: %i", Azure1->getStatus());
    mainSDLogger.logInfo("Azure2 state: %i", Azure2->getStatus());
    mainSDLogger.logInfo("Azure3 state: %i", Azure3->getStatus());
    mainSDLogger.logInfo("Azure4 state: %i", Azure4->getStatus());
    mainSDLogger.logInfo("Azure5 state: %i", Azure5->getStatus());
  }

  if(millis()-prevTime2>DELTA_TIME2){
    prevTime2 = millis();
    LogInfo("Link status: %i", Ethernet.linkStatus());
    mainSDLogger.logInfo("Link status: %i", Ethernet.linkStatus());
  }
}


//This function is needed so there is only one energy meter looping when not in idle state.
//Since they all share the same Modbus TCP Client, they can not work at the same time.
void loopEnergyMeters(){
  #ifdef USING_MODULAS_TRANSELEVADORES
  if(transelevador1.loop() != ENERGY_METER_IDLE) return;
  if(transelevador2.loop() != ENERGY_METER_IDLE) return;
  if(transelevador3.loop() != ENERGY_METER_IDLE) return;
  if(modula4.loop() != ENERGY_METER_IDLE) return;
  if(modula11.loop() != ENERGY_METER_IDLE) return;
  #endif

  #ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
  if(general.loop() != ENERGY_METER_IDLE) return;
  if(robot.loop() != ENERGY_METER_IDLE) return;
  if(lineaEmpaquetado.loop() != ENERGY_METER_IDLE) return;
  if(aireCondicionado.loop() != ENERGY_METER_IDLE) return;
  if(aireComprimido.loop() != ENERGY_METER_IDLE) return;
  #endif

  return;
}


void setEnergyMeterProperties(){
  EM750* energyMeter = nullptr;

  #ifdef USING_MODULAS_TRANSELEVADORES
  energyMeter = modula4.getEnergyMeter();
  energyMeter->setAsset(ASSET_MODULA_4);
  energyMeter->setIdentifier(IDENTIFIER_MODULA_4);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  energyMeter = modula11.getEnergyMeter();
  energyMeter->setAsset(ASSET_MODULA_11);
  energyMeter->setIdentifier(IDENTIFIER_MODULA_11);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  energyMeter = transelevador1.getEnergyMeter();
  energyMeter->setAsset(ASSET_TRANSELEVADOR_1);
  energyMeter->setIdentifier(IDENTIFIER_TRANSELEVADOR_1);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


  energyMeter = transelevador2.getEnergyMeter();
  energyMeter->setAsset(ASSET_TRANSELEVADOR_2);
  energyMeter->setIdentifier(IDENTIFIER_TRANSELEVADOR_2);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


  energyMeter = transelevador3.getEnergyMeter();
  energyMeter->setAsset(ASSET_TRANSELEVADOR_3);
  energyMeter->setIdentifier(IDENTIFIER_TRANSELEVADOR_3);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);
  #endif

  #ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
  energyMeter = general.getEnergyMeter();
  energyMeter->setAsEA750();
  energyMeter->setAsset(ASSET_GENERAL);
  energyMeter->setIdentifier(IDENTIFIER_GENERAL);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  energyMeter = robot.getEnergyMeter();
  energyMeter->setAsset(ASSET_ROBOT);
  energyMeter->setIdentifier(IDENTIFIER_ROBOT);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  energyMeter = aireCondicionado.getEnergyMeter();
  energyMeter->setAsset(ASSET_AIRE_ACONDICIONADO);
  energyMeter->setIdentifier(IDENTIFIER_AIRE_ACONDICIONADO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


  energyMeter = aireComprimido.getEnergyMeter();
  energyMeter->setAsset(ASSET_AIRE_COMPRIMIDO);
  energyMeter->setIdentifier(IDENTIFIER_AIRE_COMPRIMIDO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


  energyMeter = lineaEmpaquetado.getEnergyMeter();
  energyMeter->setAsset(ASSET_LINEA_EMPAQUETADO);
  energyMeter->setIdentifier(IDENTIFIER_LINEA_EMPAQUETADO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);
  #endif
}


void triggerEnergyMeters(){
  #ifdef USING_MODULAS_TRANSELEVADORES
  transelevador1.triggerUpdate(); 
  transelevador2.triggerUpdate();
  transelevador3.triggerUpdate();
  modula4.triggerUpdate();
  modula11.triggerUpdate();
  #endif

  #ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
  general.triggerUpdate();
  robot.triggerUpdate();
  lineaEmpaquetado.triggerUpdate();
  aireCondicionado.triggerUpdate();
  aireComprimido.triggerUpdate();
  #endif

}


void sendEnergyMeterProperties(){
  #ifdef USING_MODULAS_TRANSELEVADORES
  transelevador1.sendProperties(); 
  transelevador2.sendProperties();
  transelevador3.sendProperties();
  modula4.sendProperties();
  modula11.sendProperties();
  #endif

  #ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
  general.sendProperties();
  robot.sendProperties();
  lineaEmpaquetado.sendProperties();
  aireCondicionado.sendProperties();
  aireComprimido.sendProperties();
  #endif
}
