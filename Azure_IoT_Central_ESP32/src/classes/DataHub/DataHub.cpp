#include "DataHub.h"
//#include "globals.h"

#include <LogModule.h>



DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub1;
DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub2;
DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub3;
DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub4;
DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE> emDataHub5;
DataHub<WeidosManagerData_t, WEIDOS_METADATA_RING_BUFFER_SIZE> weidosDataHub;

DataHub<energyMeterManagerData_t, ENERGY_METER_RING_BUFFER_SIZE>* energyMeterDataHubs[5];

void fillDataHubsArray(){
    energyMeterDataHubs[0] = &emDataHub1;
    energyMeterDataHubs[1] = &emDataHub2;
    energyMeterDataHubs[2] = &emDataHub3;
    energyMeterDataHubs[3] = &emDataHub4;
    energyMeterDataHubs[4] = &emDataHub5;
    return;
}


