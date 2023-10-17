#include "energyMeters.h"
#include "generalProperties.h"
#include "../classes/DeviceCollections/DeviceCollection.h"
#include "../iot_configs.h"
#include <Ethernet.h>


#define MODBUS_NUMBER_TRIES 5



#if defined BATCH_GENERAL_ROBOT || defined BATCH_TEST
static EthernetClient ethernetClientModbus(7);
static ModbusTCPClient modbusTCPClient(ethernetClientModbus);

IPAddress ipGeneral(10, 88, 47, 202);        //General
IPAddress ipTranselevador1(10, 88, 47, 242);        //Transelevador 1
IPAddress ipTranselevador2(10, 88, 47, 243);        //Transelevador 2
IPAddress ipTranselevador3(10, 88, 47, 244);        //Transelevador 3
IPAddress ipRobot(10, 88, 47, 220);        //Robot

EA750 generalEA(modbusTCPClient, ipGeneral);
EM750 transelevador1EM(modbusTCPClient, ipTranselevador1);
EM750 transelevador2EM(modbusTCPClient, ipTranselevador2);
EM750 transelevador3EM(modbusTCPClient, ipTranselevador3);
EM750 robotEM(modbusTCPClient, ipRobot);

EA750Manager general(generalEA, 1, MODBUS_NUMBER_TRIES);
EM750Manager transelevador1(transelevador1EM, 2, MODBUS_NUMBER_TRIES);
EM750Manager transelevador2(transelevador2EM, 3, MODBUS_NUMBER_TRIES);
EM750Manager transelevador3(transelevador3EM, 4, MODBUS_NUMBER_TRIES);
EM750Manager robot(robotEM, 5, MODBUS_NUMBER_TRIES);
#endif


#ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
static EthernetClient ethernetClientModbus(7);
static ModbusTCPClient modbusTCPClient(ethernetClientModbus);

IPAddress ipLineaEmpaquetado(10, 88, 47, 221);          //Linea Empaquetado
IPAddress ipModula4(10, 88, 47, 222);        //Modula 4
IPAddress ipModula11(10, 88, 47, 223);        //Modula 11
IPAddress ipCompresorAireComprimido(10, 88, 47, 203);        //Compresor aire comprimido
IPAddress ipAcOficinas(10, 88, 47, 241);        //Compresor aire comprimido

EM750 lineaEmpaquetadoEM(modbusTCPClient, ipLineaEmpaquetado);
EM750 modula4EM(modbusTCPClient, ipModula4);
EM750 modula11EM(modbusTCPClient, ipModula11);
EM750 compresorAireComprimidoEM(modbusTCPClient, ipCompresorAireComprimido);
EM750 acOficinasEM(modbusTCPClient, ipAcOficinas);

EM750Manager lineaEmpaquetado(lineaEmpaquetadoEM, 1, MODBUS_NUMBER_TRIES);
EM750Manager modula4(modula4EM, 2, MODBUS_NUMBER_TRIES);
EM750Manager modula11(modula11EM, 3, MODBUS_NUMBER_TRIES);
EM750Manager compresorAireComprimido(compresorAireComprimidoEM, 4, MODBUS_NUMBER_TRIES);
EM750Manager acOficinas(acOficinasEM, 5, MODBUS_NUMBER_TRIES);
#endif


#ifdef BATCH_IT_SOPORTE
EM111Manager compresorIT1(1);
EM111Manager compresorIT2(2);
EM111Manager compresorSoporte(3);
#endif

#ifdef BATCH_LETS_CONNECT
EM111Manager compresorLetsConnect(1);
EM122Manager compresorMontaje(2);
EM111Manager compresorCalidad(3);
#endif





void configureDeviceCollection(){
  #if defined BATCH_GENERAL_ROBOT || defined BATCH_TEST
  DeviceCollection.setEnergyMeter(general);
  DeviceCollection.setEnergyMeter(transelevador1);
  DeviceCollection.setEnergyMeter(transelevador2);
  DeviceCollection.setEnergyMeter(transelevador3);
  DeviceCollection.setEnergyMeter(robot);
  #endif


  #ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
  DeviceCollection.setEnergyMeter(lineaEmpaquetado);
  DeviceCollection.setEnergyMeter(modula4);
  DeviceCollection.setEnergyMeter(modula11);
  DeviceCollection.setEnergyMeter(compresorAireComprimido);
  DeviceCollection.setEnergyMeter(acOficinas);
  #endif


  #ifdef BATCH_LETS_CONNECT
  DeviceCollection.setEnergyMeter(compresorLetsConnect);
  DeviceCollection.setEnergyMeter(compresorMontaje);
  DeviceCollection.setEnergyMeter(compresorCalidad);
  #endif


  #ifdef BATCH_IT_SOPORTE
  DeviceCollection.setEnergyMeter(compresorIT1);
  DeviceCollection.setEnergyMeter(compresorIT2);
  DeviceCollection.setEnergyMeter(compresorSoporte);
  #endif

}




void setEnergyMeterProperties(){
  #if defined BATCH_GENERAL_ROBOT || defined BATCH_TEST
  EA750* ea750 = nullptr;
  ea750 = general.getEnergyMeter();
  ea750->setAsEA750();
  ea750->setAsset(ASSET_GENERAL);
  ea750->setIdentifier(IDENTIFIER_GENERAL);
  ea750->setLocation1(LOCATION_NAVE_400);
  ea750->setLocation2(LOCATION_CUADRO_ENTRADA);

  EM750* em750 = nullptr;
  em750 = transelevador1.getEnergyMeter();
  em750->setAsset(ASSET_TRANSELEVADOR_1);
  em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_1);
  em750->setLocation1(LOCATION_NAVE_400);
  em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  em750 = transelevador2.getEnergyMeter();
  em750->setAsset(ASSET_TRANSELEVADOR_2);
  em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_2);
  em750->setLocation1(LOCATION_NAVE_400);
  em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  em750 = transelevador3.getEnergyMeter();
  em750->setAsset(ASSET_TRANSELEVADOR_3);
  em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_3);
  em750->setLocation1(LOCATION_NAVE_400);
  em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  em750 = robot.getEnergyMeter();
  em750->setAsset(ASSET_ROBOT);
  em750->setIdentifier(IDENTIFIER_ROBOT);
  em750->setLocation1(LOCATION_NAVE_400);
  em750->setLocation2(LOCATION_CUADRO_ALMACEN);
  #endif



  #ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
  EM750* energyMeter = nullptr;
  energyMeter = lineaEmpaquetado.getEnergyMeter();
  energyMeter->setAsset(ASSET_LINEA_EMPAQUETADO);
  energyMeter->setIdentifier(IDENTIFIER_LINEA_EMPAQUETADO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

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

  energyMeter = compresorAireComprimido.getEnergyMeter();
  energyMeter->setAsset(ASSET_AIRE_COMPRIMIDO);
  energyMeter->setIdentifier(IDENTIFIER_AIRE_COMPRIMIDO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_LETS_CONNECT);

  energyMeter = acOficinas.getEnergyMeter();
  energyMeter->setAsset(ASSET_AIRE_ACONDICIONADO);
  energyMeter->setIdentifier(IDENTIFIER_AIRE_ACONDICIONADO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ENTRADA);
  #endif


  #ifdef BATCH_LETS_CONNECT
  EM111* em111 = nullptr;
  em111 = compresorLetsConnect.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_LETS_CONNECT);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_LETS_CONNECT);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);

  EM122* em122 = nullptr;
  em122 = compresorMontaje.getEnergyMeter();
  em122->setAsset(ASSET_COMPRESOR_MONTAJE);
  em122->setIdentifier(IDENTIFIER_COMPRESOR_MONTAJE);
  em122->setLocation1(LOCATION_NAVE_400);
  em122->setLocation2(LOCATION_DIRECTO_COMPRESOR);

  em111 = compresorCalidad.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_CALIDAD);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_CALIDAD);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);
  #endif
  

  #ifdef BATCH_IT_SOPORTE
  EM111* em111 = nullptr;
  em111 = compresorIT1.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_LETS_CONNECT);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_LETS_CONNECT);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  em111 = compresorIT2.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_MONTAJE);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_MONTAJE);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  em111 = compresorSoporte.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_CALIDAD);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_CALIDAD);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);
  #endif
}




