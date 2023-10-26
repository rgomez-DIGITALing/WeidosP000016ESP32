#include "energyMeters.h"
#include <Ethernet.h>
#include "generalProperties.h"
#include "../collections/DeviceCollections/DeviceCollection.h"
#include "azure_parameters.h"


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
EM111Manager compresorSoporte(1);
EM110Manager compresorIT1(2, 50, 1);
EM110Manager compresorIT2(3, 50, 1);
EM120Manager ascensor(4, 50, 1);
#endif

#ifdef BATCH_LETS_CONNECT
EM111Manager compresorLetsConnect(1);
EM122Manager compresorMontaje(2);
EM111Manager compresorCalidad(3);
#endif

#ifdef BATCH_BARCELONA_SAI
EM111Manager barcelona(1);
EM111Manager automation(2);
EM111Manager parisMilan(3);
EM111Manager rack(4);
EM120Manager sai(5, 50, 1);
#endif





void configureDeviceCollection(){
  #if defined BATCH_GENERAL_ROBOT || defined BATCH_TEST
  DeviceCollection.setDevice(general);
  DeviceCollection.setDevice(transelevador1);
  DeviceCollection.setDevice(transelevador2);
  DeviceCollection.setDevice(transelevador3);
  DeviceCollection.setDevice(robot);
  #endif


  #ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
  DeviceCollection.setDevice(lineaEmpaquetado);
  DeviceCollection.setDevice(modula4);
  DeviceCollection.setDevice(modula11);
  DeviceCollection.setDevice(compresorAireComprimido);
  DeviceCollection.setDevice(acOficinas);
  #endif


  #ifdef BATCH_LETS_CONNECT
  DeviceCollection.setDevice(compresorLetsConnect);
  DeviceCollection.setDevice(compresorMontaje);
  DeviceCollection.setDevice(compresorCalidad);
  #endif


  #ifdef BATCH_IT_SOPORTE
  DeviceCollection.setDevice(compresorSoporte);
  DeviceCollection.setDevice(compresorIT1);
  DeviceCollection.setDevice(compresorIT2);
  DeviceCollection.setDevice(ascensor);
  #endif


  #ifdef BATCH_BARCELONA_SAI
  DeviceCollection.setDevice(barcelona);
  DeviceCollection.setDevice(automation);
  DeviceCollection.setDevice(parisMilan);
  DeviceCollection.setDevice(rack);
  DeviceCollection.setDevice(sai);
  #endif

}




void setEnergyMeterProperties(){
  #if defined BATCH_GENERAL_ROBOT || defined BATCH_TEST
  EA750* ea750 = nullptr;
  ea750 = general.getEnergyMeter();
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
  em111 = compresorSoporte.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_CALIDAD);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_CALIDAD);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  EM110* em110 = nullptr;
  em110 = compresorIT1.getEnergyMeter();
  em110->setAsset(ASSET_COMPRESOR_LETS_CONNECT);
  em110->setIdentifier(IDENTIFIER_COMPRESOR_LETS_CONNECT);
  em110->setLocation1(LOCATION_NAVE_400);
  em110->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  em110 = compresorIT2.getEnergyMeter();
  em110->setAsset(ASSET_COMPRESOR_MONTAJE);
  em110->setIdentifier(IDENTIFIER_COMPRESOR_MONTAJE);
  em110->setLocation1(LOCATION_NAVE_400);
  em110->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  EM120* em120 = nullptr;
  em120 = ascensor.getEnergyMeter();
  em120->setAsset(ASSET_ASCENSOR);
  em120->setIdentifier(IDENTIFIER_ASCENSOR);
  em120->setLocation1(LOCATION_NAVE_400);
  em120->setLocation2(LOCATION_DIRECTO_COMPRESOR);
  #endif


  #ifdef BATCH_BARCELONA_SAI
  EM111* em111 = nullptr;
  em111 = barcelona.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_SALA_BARCELONA);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_BARCELONA);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_TERRAZA);

  em111 = automation.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_SALA_AUTOMOTION);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_AUTOMOTION);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_TERRAZA);

  em111 = parisMilan.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_SALA_PARIS_MILAN);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_PARIS_MILAN);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_TERRAZA);

  em111 = rack.getEnergyMeter();
  em111->setAsset(ASSET_COMPRESOR_SALA_RACK);
  em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_RACK);
  em111->setLocation1(LOCATION_NAVE_400);
  em111->setLocation2(LOCATION_TERRAZA);


  EM120* em120 = nullptr;
  em120 = sai.getEnergyMeter();
  em120->setAsset(ASSET_ENCHUFES_EQUIPOS_SAI);
  em120->setIdentifier(IDENTIFIER_ENCHUFES_EQUIPOS_SAI);
  em120->setLocation1(LOCATION_NAVE_400);
  em120->setLocation2(LOCATION_SALA_RACK_SAI);
  #endif
}
