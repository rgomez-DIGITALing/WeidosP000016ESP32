//#include "tasks.h"
#include "energyMeterManager.h"
#include <Ethernet.h>
#include <LogModule.h>
#include <clockModule.h>

#include "../DataHub/DataHub.h"
#include "../../AzureDevices.h"

static EthernetClient ethernetClientModbus(7);
static ModbusTCPClient modbusTCPClient(ethernetClientModbus);


//Weidos 1
#ifdef USING_MODULAS_TRANSELEVADORES
IPAddress ipModula4(10, 88, 47, 222);        //Modula 4
IPAddress ipModula11(10, 88, 47, 223);        //Modula 11
IPAddress ipTranselevador1(10, 88, 47, 242);        //Transelevador 1
IPAddress ipTranselevador2(10, 88, 47, 243);        //Transelevador 2
IPAddress ipTranselevador3(10, 88, 47, 244);        //Transelevador 3

EM750 modula4EM(modbusTCPClient, ipModula4);
EM750 modula11EM(modbusTCPClient, ipModula11);
EM750 transelevador1EM(modbusTCPClient, ipTranselevador1);
EM750 transelevador2EM(modbusTCPClient, ipTranselevador2);
EM750 transelevador3EM(modbusTCPClient, ipTranselevador3);

EnergyMeterManager modula4(modula4EM, 1, 5);
EnergyMeterManager modula11(modula11EM, 2, 5);
EnergyMeterManager transelevador1(transelevador1EM, 3, 5);
EnergyMeterManager transelevador2(transelevador2EM, 4, 5);
EnergyMeterManager transelevador3(transelevador3EM, 5, 5);
#endif

//Weidos 2
#ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
IPAddress ipGeneral(10, 88, 47, 202);                   //General
IPAddress ipRobot(10, 88, 47, 220);                     //Robot
IPAddress ipLineaEmpaquetado(10, 88, 47, 221);          //Linea Empaquetado
IPAddress ipAireCondicionado(10, 88, 47, 241);          //Aire Acondicionado
IPAddress ipAireComprimido(10, 88, 47, 203);            //Aire Comprimido

EM750 generalEM(modbusTCPClient, ipGeneral);
EM750 robotEM(modbusTCPClient, ipRobot);
EM750 lineaEmpaquetadoEM(modbusTCPClient, ipLineaEmpaquetado);
EM750 aireCondicionadoEM(modbusTCPClient, ipAireCondicionado);
EM750 aireComprimidoEM(modbusTCPClient, ipAireComprimido);

EnergyMeterManager general(generalEM, 1, 5);
EnergyMeterManager robot(robotEM, 2, 5);
EnergyMeterManager lineaEmpaquetado(lineaEmpaquetadoEM, 3, 5);
EnergyMeterManager aireCondicionado(aireCondicionadoEM, 4, 5);
EnergyMeterManager aireComprimido(aireComprimidoEM, 5, 5);
#endif



EnergyMeterUpdateState EnergyMeterManager::loop(){
    switch(state){
      case ENERGY_METER_IDLE:
        break;
      case UPDATE_ENERGY_METER:
        //state = ENERGY_METER_UPDATED;
        if(!em750.begin()){
          state = ENERGY_METER_UPDATE_FAILED;
          em750.stop();
          LogError("Modbus Client for device ID %i could not begin.", deviceId);  
          break;
        }

        if(em750.update()) state = ENERGY_METER_UPDATED;
        else state = ENERGY_METER_UPDATE_FAILED;
        
        em750.stop();
        break;
      
      case ENERGY_METER_UPDATE_FAILED:
        numTries++;
        if(numTries>maxTries){
          numTries = 0;
          state = END_TASK;
          LogError("Energy meter update failed.");
        }else{
          state = UPDATE_ENERGY_METER;
          LogError("Retrying (%i/%i)", numTries, maxTries);
        }
        break;
      case ENERGY_METER_UPDATED:
        
        //em750.printData();
        //Serial.println();
        LogInfo("Energy Meter updated: %i", deviceId);
        state = PASS_MESSAGE;
        break;
      case PASS_MESSAGE:
        energyMeterManagerData_t payload;
        payload.deviceId = deviceId;
        payload.timestamp = systemClock.getEpochTime();
        em750.getData(payload.data);
        LogInfo("Pushing data for device ID: %i", deviceId);
        emDataHub.push(payload);
        state = END_TASK;
        break;
      case END_TASK:
        state = ENERGY_METER_IDLE;
        //em750.stop();
        break;
    }

    return state;
}

bool EnergyMeterManager::sendProperties(){
  AzureIoTDevice* azureDevice = azureDevices[deviceId];

  if(propertiesSent) return propertiesSent;
  if(azureDevice->getStatus() == azure_iot_connected){
    size_t payload_buffer_length = 0;
    uint8_t* payload_buffer = azureDevice->getDataBuffer2();
    azure_iot_t* azureIoT = azureDevice->getAzureIoT();
    az_iot_hub_client const* iotHubClient = &azureIoT->iot_hub_client;
    em750_generete_properties(iotHubClient, payload_buffer, AZ_IOT_DATA_BUFFER_SIZE, &payload_buffer_length, &em750);
    int error = azureDevice->sendProperties(az_span_create(payload_buffer, payload_buffer_length));
    if(!error) propertiesSent = true;
  }
  return propertiesSent;
}
