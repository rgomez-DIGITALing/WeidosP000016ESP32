#include "energyMeters.h"
#include "generalProperties.h"
#include "../classes/DeviceCollections/DeviceCollection.h"

#include <Ethernet.h>


#define MODBUS_NUMBER_TRIES 5



// static EthernetClient ethernetClientModbus(7);
// static ModbusTCPClient modbusTCPClient(ethernetClientModbus);

// IPAddress ipModula4(10, 88, 47, 222);        //Modula 4
// IPAddress ipModula11(10, 88, 47, 223);        //Modula 11
// IPAddress ipTranselevador1(10, 88, 47, 242);        //Transelevador 1
// IPAddress ipTranselevador2(10, 88, 47, 243);        //Transelevador 2
// IPAddress ipTranselevador3(10, 88, 47, 244);        //Transelevador 3

// EM750 modula4EM(modbusTCPClient, ipModula4);
// EM750 modula11EM(modbusTCPClient, ipModula11);
// EM750 transelevador1EM(modbusTCPClient, ipTranselevador1);
// EM750 transelevador2EM(modbusTCPClient, ipTranselevador2);
// EM750 transelevador3EM(modbusTCPClient, ipTranselevador3);

// EM750Manager modula4(modula4EM, 0, MODBUS_NUMBER_TRIES);
// EM750Manager modula11(modula11EM, 1, MODBUS_NUMBER_TRIES);
// EM750Manager transelevador1(transelevador1EM, 2, MODBUS_NUMBER_TRIES);
// EM750Manager transelevador2(transelevador2EM, 3, MODBUS_NUMBER_TRIES);
// EM750Manager transelevador3(transelevador3EM, 4, MODBUS_NUMBER_TRIES);

EM111Manager em111Taula(1);
EM111Manager em111Taula(1);
EM111Manager em111Taula(1);

void configureDeviceCollection(){
    DeviceCollection.setEnergyMeter(em111Taula);
    // DeviceCollection.setEnergyMeter(modula4);
    // DeviceCollection.setEnergyMeter(modula11);
    // DeviceCollection.setEnergyMeter(transelevador1);
    // DeviceCollection.setEnergyMeter(transelevador2);
    // DeviceCollection.setEnergyMeter(transelevador3);
}




void setEnergyMeterProperties(){
  EM111* energyMeter = nullptr;
  energyMeter = em111Taula.getEnergyMeter();
  energyMeter->setAsset(ASSET_AIRE_ACONDICIONADO);
  energyMeter->setIdentifier(IDENTIFIER_AIRE_ACONDICIONADO);
  energyMeter->setLocation1(LOCATION_NAVE_400);
  energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

  //#ifdef USING_MODULAS_TRANSELEVADORES
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

  // energyMeter = transelevador1.getEnergyMeter();
  // energyMeter->setAsset(ASSET_TRANSELEVADOR_1);
  // energyMeter->setIdentifier(IDENTIFIER_TRANSELEVADOR_1);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


  // energyMeter = transelevador2.getEnergyMeter();
  // energyMeter->setAsset(ASSET_TRANSELEVADOR_2);
  // energyMeter->setIdentifier(IDENTIFIER_TRANSELEVADOR_2);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


  // energyMeter = transelevador3.getEnergyMeter();
  // energyMeter->setAsset(ASSET_TRANSELEVADOR_3);
  // energyMeter->setIdentifier(IDENTIFIER_TRANSELEVADOR_3);
  // energyMeter->setLocation1(LOCATION_NAVE_400);
  // energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);
  //#endif

//   #ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
//   energyMeter = general.getEnergyMeter();
//   energyMeter->setAsEA750();
//   energyMeter->setAsset(ASSET_GENERAL);
//   energyMeter->setIdentifier(IDENTIFIER_GENERAL);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

//   energyMeter = robot.getEnergyMeter();
//   energyMeter->setAsset(ASSET_ROBOT);
//   energyMeter->setIdentifier(IDENTIFIER_ROBOT);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);

//   energyMeter = aireCondicionado.getEnergyMeter();
//   energyMeter->setAsset(ASSET_AIRE_ACONDICIONADO);
//   energyMeter->setIdentifier(IDENTIFIER_AIRE_ACONDICIONADO);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


//   energyMeter = aireComprimido.getEnergyMeter();
//   energyMeter->setAsset(ASSET_AIRE_COMPRIMIDO);
//   energyMeter->setIdentifier(IDENTIFIER_AIRE_COMPRIMIDO);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);


//   energyMeter = lineaEmpaquetado.getEnergyMeter();
//   energyMeter->setAsset(ASSET_LINEA_EMPAQUETADO);
//   energyMeter->setIdentifier(IDENTIFIER_LINEA_EMPAQUETADO);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_CUADRO_ALMACEN);
//   #endif

//   #ifdef BATCH_IT
//   energyMeter = compresorIT1.getEnergyMeter();
//   energyMeter->setAsset(ASSET_COMPRESOR_IT_1);
//   energyMeter->setIdentifier(IDENTIFIER_COMPRESOR_IT_1);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_SALA_IT);

//   energyMeter = compresorIT2.getEnergyMeter();
//   energyMeter->setAsset(ASSET_COMPRESOR_IT_2);
//   energyMeter->setIdentifier(IDENTIFIER_COMPRESOR_IT_2);
//   energyMeter->setLocation1(LOCATION_NAVE_400);
//   energyMeter->setLocation2(LOCATION_SALA_IT);
//   #endif
}




