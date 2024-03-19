#include "energyMeters.h"
#include <Ethernet.h>
#include "generalProperties.h"
#include "../collections/DeviceCollections/DeviceCollection.h"
#include "../collections/TriggerCollection/TriggerCollection.h"
#include "azure_parameters.h"



void setTriggers(){
  #if defined BATCH_TEST && defined FLOW_METER_TEST
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* pulseMeterTrigger = new TriggerClass(1);
  TriggerClass* pulseMeter2Trigger = new TriggerClass(2);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(pulseMeterTrigger);
  TriggerCollection.setTrigger(pulseMeter2Trigger);
  #endif


  #if defined BATCH_TEST && defined EM750_TEST
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* generalTrigger = new TriggerClass(1);
  TriggerClass* modula4Trigger = new TriggerClass(2);
  TriggerClass* modula11Trigger = new TriggerClass(3);
  TriggerClass* compresorAireComprimidoTrigger = new TriggerClass(4);
  TriggerClass* acOficinasTrigger = new TriggerClass(5);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(generalTrigger);
  TriggerCollection.setTrigger(modula4Trigger);
  TriggerCollection.setTrigger(modula11Trigger);
  TriggerCollection.setTrigger(compresorAireComprimidoTrigger);
  TriggerCollection.setTrigger(acOficinasTrigger);
  #endif


  #if defined BATCH_TEST && defined  RTU_TEST
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* barcelonaTrigger = new TriggerClass(1);
  TriggerClass* automationTrigger = new TriggerClass(2);
  TriggerClass* parisMilanTrigger = new TriggerClass(3);
  TriggerClass* rackTrigger = new TriggerClass(4);
  TriggerClass* saiTrigger = new TriggerClass(5);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(barcelonaTrigger);
  TriggerCollection.setTrigger(automationTrigger);
  TriggerCollection.setTrigger(parisMilanTrigger);
  TriggerCollection.setTrigger(rackTrigger);
  TriggerCollection.setTrigger(saiTrigger);
  #endif


  #if defined BATCH_GENERAL_ROBOT
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* generalTrigger = new TriggerClass(1);
  TriggerClass* transelevador1Trigger = new TriggerClass(2);
  TriggerClass* transelevador2Trigger = new TriggerClass(3);
  TriggerClass* transelevador3Trigger = new TriggerClass(4);
  TriggerClass* robotTrigger = new TriggerClass(5);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(generalTrigger);
  TriggerCollection.setTrigger(transelevador1Trigger);
  TriggerCollection.setTrigger(transelevador2Trigger);
  TriggerCollection.setTrigger(transelevador3Trigger);
  TriggerCollection.setTrigger(robotTrigger);
  #endif


  #if defined BATCH_TRANSELEVADORES_FAST
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* transelevador1Trigger = new TriggerClass(1);
  TriggerClass* transelevador2Trigger = new TriggerClass(2);
  TriggerClass* transelevador3Trigger = new TriggerClass(3);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(transelevador1Trigger);
  TriggerCollection.setTrigger(transelevador2Trigger);
  TriggerCollection.setTrigger(transelevador3Trigger);
  #endif


  #ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* lineaEmpaquetadoTrigger = new TriggerClass(1);
  TriggerClass* modula4Trigger = new TriggerClass(2);
  TriggerClass* modula11Trigger = new TriggerClass(3);
  TriggerClass* compresorAireComprimidoTrigger = new TriggerClass(4);
  TriggerClass* acOficinasTrigger = new TriggerClass(5);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(lineaEmpaquetadoTrigger);
  TriggerCollection.setTrigger(modula4Trigger);
  TriggerCollection.setTrigger(modula11Trigger);
  TriggerCollection.setTrigger(compresorAireComprimidoTrigger);
  TriggerCollection.setTrigger(acOficinasTrigger);
  #endif


  #ifdef BATCH_LETS_CONNECT
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* compresorLetsConnect = new TriggerClass(1);
  TriggerClass* compresorMontaje = new TriggerClass(2);
  TriggerClass* compresorCalidad = new TriggerClass(3);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(compresorLetsConnect);
  TriggerCollection.setTrigger(compresorMontaje);
  TriggerCollection.setTrigger(compresorCalidad);
  #endif


  #ifdef BATCH_IT_SOPORTE
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* compresorSoporte = new TriggerClass(1);
  TriggerClass* compresorIT1 = new TriggerClass(2);
  TriggerClass* compresorIT2 = new TriggerClass(3);
  TriggerClass* ascensor = new TriggerClass(4);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(compresorSoporte);
  TriggerCollection.setTrigger(compresorIT1);
  TriggerCollection.setTrigger(compresorIT2);
  TriggerCollection.setTrigger(ascensor);
  #endif


  #ifdef BATCH_BARCELONA_SAI
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* barcelonaTrigger = new TriggerClass(1);
  TriggerClass* automationTrigger = new TriggerClass(2);
  TriggerClass* parisMilanTrigger = new TriggerClass(3);
  TriggerClass* rackTrigger = new TriggerClass(4);
  TriggerClass* saiTrigger = new TriggerClass(5);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(barcelonaTrigger);
  TriggerCollection.setTrigger(automationTrigger);
  TriggerCollection.setTrigger(parisMilanTrigger);
  TriggerCollection.setTrigger(rackTrigger);
  TriggerCollection.setTrigger(saiTrigger);
  #endif


  #ifdef BATCH_GAC_LETS_CONNECT
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* compresorGAC4 = new TriggerClass(1);
  TriggerClass* compresorGAC5 = new TriggerClass(2);
  TriggerClass* compresorLetsConnect = new TriggerClass(3);

  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(compresorGAC4);
  TriggerCollection.setTrigger(compresorGAC5);
  TriggerCollection.setTrigger(compresorLetsConnect);
  #endif


  #ifdef BATCH_MONTACARGAS
  TriggerClass* weidosESP32Trigger = new TriggerClass(0);
  TriggerClass* montacargas = new TriggerClass(1);
  TriggerCollection.setTrigger(weidosESP32Trigger);
  TriggerCollection.setTrigger(montacargas);
  #endif
}



#if defined BATCH_GENERAL_ROBOT || defined BATCH_TRANSELEVADORES_FAST || defined BATCH_LINEA_EMPAQUETADO_AC_OFICINAS || defined BATCH_MONTACARGAS || defined EM750_TEST
static EthernetClient ethernetClientModbus(7);
static ModbusTCPClient modbusTCPClient(ethernetClientModbus);
#endif



void configureDeviceCollection(){
  DeviceCollection.setDevice(weidosESP32Manager);
  #if defined BATCH_GENERAL_ROBOT
  IPAddress ipGeneral(10, 88, 47, 202);        //General
  IPAddress ipTranselevador1(10, 88, 47, 242);        //Transelevador 1
  IPAddress ipTranselevador2(10, 88, 47, 243);        //Transelevador 2
  IPAddress ipTranselevador3(10, 88, 47, 244);        //Transelevador 3
  IPAddress ipRobot(10, 88, 47, 220);        //Robot

  EA750Manager* general = new EA750Manager(modbusTCPClient, ipGeneral, 1);
  EM750Manager* transelevador1 = new EM750Manager(modbusTCPClient, ipTranselevador1, 2);
  EM750Manager* transelevador2 = new EM750Manager(modbusTCPClient, ipTranselevador2, 3);
  EM750Manager* transelevador3 = new EM750Manager(modbusTCPClient, ipTranselevador3, 4);
  EM750Manager* robot = new EM750Manager(modbusTCPClient, ipRobot, 5);

  DeviceCollection.setDevice(general);
  DeviceCollection.setDevice(transelevador1);
  DeviceCollection.setDevice(transelevador2);
  DeviceCollection.setDevice(transelevador3);
  DeviceCollection.setDevice(robot);
  #endif


  #if defined BATCH_TRANSELEVADORES_FAST
  IPAddress ipTranselevador1(10, 88, 47, 242);        //Transelevador 1
  IPAddress ipTranselevador2(10, 88, 47, 243);        //Transelevador 2
  IPAddress ipTranselevador3(10, 88, 47, 244);        //Transelevador 3

  EM750Manager* transelevador1 = new EM750Manager(modbusTCPClient, ipTranselevador1, 1);
  EM750Manager* transelevador2 = new EM750Manager(modbusTCPClient, ipTranselevador2, 2);
  EM750Manager* transelevador3 = new EM750Manager(modbusTCPClient, ipTranselevador3, 3);

  DeviceCollection.setDevice(transelevador1);
  DeviceCollection.setDevice(transelevador2);
  DeviceCollection.setDevice(transelevador3);
  #endif


  #ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
  IPAddress ipLineaEmpaquetado(10, 88, 47, 221);          //Linea Empaquetado
  IPAddress ipModula4(10, 88, 47, 222);        //Modula 4
  IPAddress ipModula11(10, 88, 47, 223);        //Modula 11
  IPAddress ipCompresorAireComprimido(10, 88, 47, 203);        //Compresor aire comprimido
  IPAddress ipAcOficinas(10, 88, 47, 241);        //Compresor aire comprimido

  EM750Manager* lineaEmpaquetado = new EM750Manager(modbusTCPClient, ipLineaEmpaquetado, 1);
  EM750Manager* modula4 = new EM750Manager(modbusTCPClient, ipModula4, 2);
  EM750Manager* modula11 = new EM750Manager(modbusTCPClient, ipModula11, 3);
  EM750Manager* compresorAireComprimido = new EM750Manager(modbusTCPClient, ipCompresorAireComprimido, 4);
  EM750Manager* acOficinas = new EM750Manager(modbusTCPClient, ipAcOficinas, 5);

  DeviceCollection.setDevice(lineaEmpaquetado);
  DeviceCollection.setDevice(modula4);
  DeviceCollection.setDevice(modula11);
  DeviceCollection.setDevice(compresorAireComprimido);
  DeviceCollection.setDevice(acOficinas);
  #endif


  #ifdef BATCH_IT_SOPORTE
  EM111Manager* compresorSoporte = new EM111Manager(1);
  EM110Manager* compresorIT1 = new EM110Manager(2, 50, 1);
  EM110Manager* compresorIT2 = new EM110Manager(3, 50, 1);
  EM120Manager* ascensor = new EM120Manager(4, 50, 1);
  DeviceCollection.setDevice(compresorSoporte);
  DeviceCollection.setDevice(compresorIT1);
  DeviceCollection.setDevice(compresorIT2);
  DeviceCollection.setDevice(ascensor);
  #endif


  #ifdef BATCH_LETS_CONNECT
  EM111Manager* compresorLetsConnect = new EM111Manager(1);
  EM122Manager* compresorMontaje = new EM122Manager(2);
  EM111Manager* compresorCalidad = new EM111Manager(3);
  DeviceCollection.setDevice(compresorLetsConnect);
  DeviceCollection.setDevice(compresorMontaje);
  DeviceCollection.setDevice(compresorCalidad);
  #endif


  #ifdef BATCH_BARCELONA_SAI
  EM111Manager* barcelona = new EM111Manager(1);
  EM111Manager* automation = new EM111Manager(2);
  EM111Manager* parisMilan = new EM111Manager(3);
  EM111Manager* rack = new EM111Manager(4);
  EM120Manager* sai = new EM120Manager(5, 50, 1);
  DeviceCollection.setDevice(barcelona);
  DeviceCollection.setDevice(automation);
  DeviceCollection.setDevice(parisMilan);
  DeviceCollection.setDevice(rack);
  DeviceCollection.setDevice(sai);
  #endif


  #ifdef BATCH_GAC_LETS_CONNECT
  EM111Manager* compresorGAC4 = new EM111Manager(1);
  EM111Manager* compresorGAC5 = new EM111Manager(2);
  EM122Manager* compresorLetsConnect = new EM122Manager(3);
  DeviceCollection.setDevice(compresorGAC4);
  DeviceCollection.setDevice(compresorGAC5);
  DeviceCollection.setDevice(compresorLetsConnect);
  #endif


  #if defined BATCH_MONTACARGAS
  IPAddress ipElevador(10, 88, 47, 225);        //General
  EM750Manager* montacargas = new EM750Manager(modbusTCPClient, ipElevador, 1);
  DeviceCollection.setDevice(montacargas);
  #endif


  #if defined BATCH_TEST && defined FLOW_METER_TEST
  DeviceCollection.setDevice(pulseMeterManager);
  DeviceCollection.setDevice(pulseMeterManager2);
  //DeviceCollection.setDevice(analogMeterManager);
  #endif


  #if defined BATCH_TEST && defined EM750_TEST
  IPAddress ipGeneral(10, 88, 47, 202);        //General
  IPAddress ipModula4(10, 88, 47, 222);        //Modula 4
  IPAddress ipModula11(10, 88, 47, 223);        //Modula 11
  IPAddress ipCompresorAireComprimido(10, 88, 47, 203);        //Compresor aire comprimido
  IPAddress ipAcOficinas(10, 88, 47, 241);        //Compresor aire comprimido

  EA750Manager* general = new EA750Manager(modbusTCPClient, ipGeneral, 1);
  EM750Manager* modula4 = new EM750Manager(modbusTCPClient, ipModula4, 2);
  EM750Manager* modula11 = new EM750Manager(modbusTCPClient, ipModula11, 3);
  EM750Manager* compresorAireComprimido = new EM750Manager(modbusTCPClient, ipCompresorAireComprimido, 4);
  EM750Manager* acOficinas = new EM750Manager(modbusTCPClient, ipAcOficinas, 5);

  DeviceCollection.setDevice(general);
  DeviceCollection.setDevice(modula4);
  DeviceCollection.setDevice(modula11);
  DeviceCollection.setDevice(compresorAireComprimido);
  DeviceCollection.setDevice(acOficinas);
  #endif


  #if defined BATCH_TEST && defined RTU_TEST
  EM111Manager* barcelona = new EM111Manager(1);
  EM111Manager* automation = new EM111Manager(2);
  EM111Manager* parisMilan = new EM111Manager(3);
  EM111Manager* rack = new EM111Manager(4);
  EM120Manager* sai = new EM120Manager(5, 50, 1);

  
  // DeviceCollection.setDevice(barcelona);
  // DeviceCollection.setDevice(automation);
  // DeviceCollection.setDevice(parisMilan);
  // DeviceCollection.setDevice(rack);
  DeviceCollection.setDevice(sai);
  #endif
}




void setEnergyMeterProperties(){
  #if defined BATCH_TEST && defined FLOW_METER_TEST
  #endif

  #if defined BATCH_TEST && defined EM750_TEST



  // EM750* energyMeter = nullptr;
  // energyMeter = lineaEmpaquetado.getEnergyMeter();
  // energyMeter->setAsset(ASSET_LINEA_EMPAQUETADO);
  // energyMeter->setIdentifier(IDENTIFIER_LINEA_EMPAQUETADO);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  // energyMeter = modula4.getEnergyMeter();
  // energyMeter->setAsset(ASSET_MODULA_4);
  // energyMeter->setIdentifier(IDENTIFIER_MODULA_4);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  // energyMeter = modula11.getEnergyMeter();
  // energyMeter->setAsset(ASSET_MODULA_11);
  // energyMeter->setIdentifier(IDENTIFIER_MODULA_11);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  // energyMeter = compresorAireComprimido.getEnergyMeter();
  // energyMeter->setAsset(ASSET_AIRE_COMPRIMIDO);
  // energyMeter->setIdentifier(IDENTIFIER_AIRE_COMPRIMIDO);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_LETS_CONNECT);

  // energyMeter = acOficinas.getEnergyMeter();
  // energyMeter->setAsset(ASSET_AIRE_ACONDICIONADO);
  // energyMeter->setIdentifier(IDENTIFIER_AIRE_ACONDICIONADO);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ENTRADA);
  #endif


  // #if defined BATCH_GENERAL_ROBOT
  // EA750* ea750 = nullptr;
  // ea750 = general.getEnergyMeter();
  // ea750->setAsset(ASSET_GENERAL);
  // ea750->setIdentifier(IDENTIFIER_GENERAL);
  // ea750->setLocation1(LOCATION_NAVE_400);
  // ea750->setLocation2(LOCATION_CUADRO_ENTRADA);

  // EM750* em750 = nullptr;
  // em750 = transelevador1.getEnergyMeter();
  // em750->setAsset(ASSET_TRANSELEVADOR_1);
  // em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_1);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  // em750 = transelevador2.getEnergyMeter();
  // em750->setAsset(ASSET_TRANSELEVADOR_2);
  // em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_2);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  // em750 = transelevador3.getEnergyMeter();
  // em750->setAsset(ASSET_TRANSELEVADOR_3);
  // em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_3);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  // em750 = robot.getEnergyMeter();
  // em750->setAsset(ASSET_ROBOT);
  // em750->setIdentifier(IDENTIFIER_ROBOT);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);
  // #endif


  // #if defined BATCH_TRANSELEVADORES_FAST
  // EM750* em750 = nullptr;
  // em750 = transelevador1.getEnergyMeter();
  // em750->setAsset(ASSET_TRANSELEVADOR_1);
  // em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_1);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  // em750 = transelevador2.getEnergyMeter();
  // em750->setAsset(ASSET_TRANSELEVADOR_2);
  // em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_2);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);

  // em750 = transelevador3.getEnergyMeter();
  // em750->setAsset(ASSET_TRANSELEVADOR_3);
  // em750->setIdentifier(IDENTIFIER_TRANSELEVADOR_3);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);
  // #endif



  // #ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
  // EM750* energyMeter = nullptr;
  // energyMeter = lineaEmpaquetado.getEnergyMeter();
  // energyMeter->setAsset(ASSET_LINEA_EMPAQUETADO);
  // energyMeter->setIdentifier(IDENTIFIER_LINEA_EMPAQUETADO);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  // energyMeter = modula4.getEnergyMeter();
  // energyMeter->setAsset(ASSET_MODULA_4);
  // energyMeter->setIdentifier(IDENTIFIER_MODULA_4);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  // energyMeter = modula11.getEnergyMeter();
  // energyMeter->setAsset(ASSET_MODULA_11);
  // energyMeter->setIdentifier(IDENTIFIER_MODULA_11);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  // energyMeter = compresorAireComprimido.getEnergyMeter();
  // energyMeter->setAsset(ASSET_AIRE_COMPRIMIDO);
  // energyMeter->setIdentifier(IDENTIFIER_AIRE_COMPRIMIDO);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_LETS_CONNECT);

  // energyMeter = acOficinas.getEnergyMeter();
  // energyMeter->setAsset(ASSET_AIRE_ACONDICIONADO);
  // energyMeter->setIdentifier(IDENTIFIER_AIRE_ACONDICIONADO);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ENTRADA);
  // #endif


  // #ifdef BATCH_LETS_CONNECT
  // EM111* em111 = nullptr;
  // em111 = compresorLetsConnect.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_LETS_CONNECT);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_LETS_CONNECT);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);

  // EM122* em122 = nullptr;
  // em122 = compresorMontaje.getEnergyMeter();
  // em122->setAsset(ASSET_COMPRESOR_MONTAJE);
  // em122->setIdentifier(IDENTIFIER_COMPRESOR_MONTAJE);
  // em122->setLocation1(LOCATION_NAVE_400);
  // em122->setLocation2(LOCATION_DIRECTO_COMPRESOR);

  // em111 = compresorCalidad.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_CALIDAD);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_CALIDAD);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);
  // #endif


  // #ifdef BATCH_IT_SOPORTE

  // EM111* em111 = nullptr;
  // em111 = compresorSoporte.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_CALIDAD);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_CALIDAD);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  // EM110* em110 = nullptr;
  // em110 = compresorIT1.getEnergyMeter();
  // em110->setAsset(ASSET_COMPRESOR_LETS_CONNECT);
  // em110->setIdentifier(IDENTIFIER_COMPRESOR_LETS_CONNECT);
  // em110->setLocation1(LOCATION_NAVE_400);
  // em110->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  // em110 = compresorIT2.getEnergyMeter();
  // em110->setAsset(ASSET_COMPRESOR_MONTAJE);
  // em110->setIdentifier(IDENTIFIER_COMPRESOR_MONTAJE);
  // em110->setLocation1(LOCATION_NAVE_400);
  // em110->setLocation2(LOCATION_DIRECTO_COMPRESOR);


  // EM120* em120 = nullptr;
  // em120 = ascensor.getEnergyMeter();
  // em120->setAsset(ASSET_ASCENSOR);
  // em120->setIdentifier(IDENTIFIER_ASCENSOR);
  // em120->setLocation1(LOCATION_NAVE_400);
  // em120->setLocation2(LOCATION_DIRECTO_COMPRESOR);
  // #endif


  // #ifdef BATCH_BARCELONA_SAI
  // EM111* em111 = nullptr;
  // em111 = barcelona.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_SALA_BARCELONA);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_BARCELONA);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_TERRAZA);

  // em111 = automation.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_SALA_AUTOMOTION);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_AUTOMOTION);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_TERRAZA);

  // em111 = parisMilan.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_SALA_PARIS_MILAN);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_PARIS_MILAN);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_TERRAZA);

  // em111 = rack.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_SALA_RACK);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_SALA_RACK);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_TERRAZA);


  // EM120* em120 = nullptr;
  // em120 = sai.getEnergyMeter();
  // em120->setAsset(ASSET_ENCHUFES_EQUIPOS_SAI);
  // em120->setIdentifier(IDENTIFIER_ENCHUFES_EQUIPOS_SAI);
  // em120->setLocation1(LOCATION_NAVE_400);
  // em120->setLocation2(LOCATION_SALA_RACK_SAI);
  // #endif


  // #ifdef BATCH_GAC_LETS_CONNECT
  // EM111* em111 = nullptr;
  // em111 = compresorGAC4.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_GAC4);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_GAC4);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_PLANTA_0);

  // em111 = compresorGAC5.getEnergyMeter();
  // em111->setAsset(ASSET_COMPRESOR_GAC5);
  // em111->setIdentifier(IDENTIFIER_COMPRESOR_GAC5);
  // em111->setLocation1(LOCATION_NAVE_400);
  // em111->setLocation2(LOCATION_PLANTA_0);

  // EM122* em122 = nullptr;
  // em122 = compresorLetsConnect.getEnergyMeter();
  // em122->setAsset(ASSET_COMPRESOR_SALA_LETS_CONNECT);
  // em122->setIdentifier(IDENTIFIER_COMPRESOR_SALA_LETS_CONNECT);
  // em122->setLocation1(LOCATION_NAVE_400);
  // em122->setLocation2(LOCATION_PLANTA_MINUS_1);
  // #endif


  // #ifdef BATCH_ELEVADOR
  // EM750* em750 = nullptr;
  // em750 = montacargas.getEnergyMeter();
  // em750->setAsset(ASSET_ELEVADOR);
  // em750->setIdentifier(IDENTIFIER_ELEVADOR);
  // em750->setLocation1(LOCATION_NAVE_400);
  // em750->setLocation2(LOCATION_CUADRO_ALMACEN);
  // #endif

}
