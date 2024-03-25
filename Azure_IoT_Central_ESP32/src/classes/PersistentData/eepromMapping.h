#pragma once
#include "PersistentDataClass.h"



static const int FIRST_DEVICE_CONFIG_DATA_INDEX = 1;
static const int FIRST_AZURE_DATA_INDEX = 1000;
static const int FIRST_ENERGY_METER_DATA_INDEX = 5000;
static const int FIRST_PULSE_ANALOG_DATA_INDEX = 7000;

static const int FLAG_SIZE = 1;
static const int UINT8_T_SIZE = 1;
static const int FLOAT_SIZE = 4;
static const int INT_SIZE = 4;
// static const int IP_SIZE = 4;
static const int PIN_SIZE = 4;
// static const int IP_ADDRESS_SIZE = 4;
static const int IP_ADDRESS_SIZE = sizeof(IPAddress);

static const int NUM_MAX_DEVICES_EEPROM = 20;



/*####### Device Configuration Data ###########
Array with the type of divice in each slot.
*/
static const int DEVICE_TYPE_SET_FLAGS_INDEX = FIRST_DEVICE_CONFIG_DATA_INDEX;
static const int DEVICE_TYPE_SET_FLAG_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int DEVICE_CONFIGURATION_DATA_INDEX = DEVICE_TYPE_SET_FLAGS_INDEX + DEVICE_TYPE_SET_FLAG_SIZE;
static const int DEVICE_CONFIGURATION_DATA_SIZE = UINT8_T_SIZE*NUM_MAX_DEVICES_EEPROM;


/*########## Azure Parameters ############
EEPROM section to store Azure related parameters:
- Scope ID (size: SCOPE_ID_SIZE)
- Azure Device IDs (Array of Azure Device IDs):
    · Number of Azure Device IDs = NUM_AZURE_DEVICES (see Note 1.)
    · Size of each Azure Device ID = 
- Azure SAS Keys (Array of Azure SAS Keys):
    · Number of Azure SAS Keys = NUM_AZURE_DEVICES (see Note 1.)



Note 1: NUM_EEPROM_AZURE_DEVICES is greater than MAX_NUM_AZURE_DEVICES defined in "AzureIoTCollection.h".
MAX_NUM_AZURE_DEVICES is currently limited to the number of Ethernet sockets available. If in the future this limitation
is overpassed and MAX_NUM_AZURE_DEVICES is increased, it will already have room in the EEPROM for the new devices without 
having to change EEPROM indixes (EEPROM mapping). Changing EEPROM map would imply that an updated Weidos would have to be
reconfigured via Web Server.
*/

static const int SCOPE_ID_SET_FLAG_INDEX = FIRST_AZURE_DATA_INDEX;
static const int SCOPE_ID_SET_FLAG_SIZE = FLAG_SIZE;

static const int SCOPE_ID_INDEX = SCOPE_ID_SET_FLAG_INDEX + SCOPE_ID_SET_FLAG_SIZE;
static const int SCOPE_ID_SIZE = AZURE_SCOPE_ID_SIZE;



static const int AZURE_DEVICE_ID_SET_FLAGS_INDEX = SCOPE_ID_INDEX + SCOPE_ID_SIZE;
static const int AZURE_DEVICES_ID_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int AZURE_DEVICE_IDS_INDEX = AZURE_DEVICE_ID_SET_FLAGS_INDEX + AZURE_DEVICES_ID_SET_FLAGS_SIZE;
static const int AZURE_DEVICES_IDS_SIZE = AZURE_ID_SIZE*NUM_MAX_DEVICES_EEPROM;



static const int AZURE_SAS_KEY_SET_FLAGS_INDEX = AZURE_DEVICE_IDS_INDEX + AZURE_DEVICES_IDS_SIZE;
static const int AZURE_SAS_KEY_SET_FLAGS_SIZE = AZURE_SAS_KEY_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int AZURE_SAS_KEYS_INDEX = AZURE_SAS_KEY_SET_FLAGS_INDEX + AZURE_SAS_KEY_SET_FLAGS_SIZE;
static const int AZURE_SAS_KEYS_SIZE = AZURE_SAS_KEY_SIZE*NUM_MAX_DEVICES_EEPROM;







/* ######### Energy Meter Data ##########


*/
//Modbus Addresses (IDs)
static const int MODBUS_ID_SET_FLAGS_INDEX = FIRST_ENERGY_METER_DATA_INDEX;
static const int MODBUS_ID_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int MODBUS_IDS_INDEX = MODBUS_ID_SET_FLAGS_INDEX + MODBUS_ID_SET_FLAGS_SIZE;
static const int MODBUS_IDS_SIZE = UINT8_T_SIZE*NUM_MAX_DEVICES_EEPROM;


//Modbus IP (for Modbus TCP/IP devices)
static const int MODBUS_TCP_IP_FLAGS_INDEX = MODBUS_IDS_INDEX + MODBUS_IDS_SIZE;
static const int MODBUS_TCP_IP_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int MODBUS_TCP_IPS_INDEX = MODBUS_TCP_IP_FLAGS_INDEX + MODBUS_TCP_IP_SET_FLAGS_SIZE;
static const int MODBUS_TCP_IPS_SIZE = IP_ADDRESS_SIZE*NUM_MAX_DEVICES_EEPROM;


//CT primary
static const int CT_PRIMARY_SET_FLAGS_INDEX = MODBUS_TCP_IPS_INDEX + MODBUS_TCP_IPS_SIZE;
static const int CT_PRIMARY_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int CT_PRIMARY_INDEX = CT_PRIMARY_SET_FLAGS_INDEX + CT_PRIMARY_SET_FLAGS_SIZE;
static const int CT_PRIMARY_SIZE = INT_SIZE*NUM_MAX_DEVICES_EEPROM;


//CT secondary
static const int CT_SECONDARY_SET_FLAGS_INDEX = CT_PRIMARY_INDEX + CT_PRIMARY_SIZE;
static const int CT_SECONDARY_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int CT_SECONDARY_INDEX = CT_SECONDARY_SET_FLAGS_INDEX + CT_SECONDARY_SET_FLAGS_SIZE;
static const int CT_SECONDARY_SIZE = INT_SIZE*NUM_MAX_DEVICES_EEPROM;


//Harmonics activated flag
static const int HARMONIC_ACTIVATED_FLAGS_INDEX = CT_SECONDARY_INDEX + CT_SECONDARY_SIZE;
static const int HARMONIC_ACTIVATED_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;



/* ######### Pulse/Analog Meter Data ##########


*/
static const int PULSE_ANALOG_PIN_SET_FLAGS_INDEX = FIRST_PULSE_ANALOG_DATA_INDEX;
static const int PULSE_ANALOG_PIN_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int PULSE_ANALOG_PIN_INDEX = PULSE_ANALOG_PIN_SET_FLAGS_INDEX + PULSE_ANALOG_PIN_SET_FLAGS_SIZE;
static const int PULSE_ANALOG_PIN_SIZE = PIN_SIZE*NUM_MAX_DEVICES_EEPROM;



static const int CONVERSION_FACTOR_SET_FLAGS_INDEX = PULSE_ANALOG_PIN_INDEX + PULSE_ANALOG_PIN_SIZE;
static const int CONVERSION_FACTOR_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int CONVERSION_FACTOR_INDEX = CONVERSION_FACTOR_SET_FLAGS_INDEX + CONVERSION_FACTOR_SET_FLAGS_SIZE;
static const int CONVERSION_FACTOR_SIZE = FLOAT_SIZE*NUM_MAX_DEVICES_EEPROM;
