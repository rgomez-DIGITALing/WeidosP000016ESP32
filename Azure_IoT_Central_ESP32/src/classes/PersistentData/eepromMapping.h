#pragma once
#include "PersistentDataClass.h"


// #define FIRST_INDEX     1
// #define FLAG_SIZE       1

// //Flags
// #define WIFI_SSID_SET_FLAG_INDEX                    FIRST_INDEX
// #define WIFI_PASS_SET_FLAG_INDEX                    (WIFI_SSID_SET_FLAG_INDEX + FLAG_SIZE)
// #define GATEWAY_DEVICE_ID_SET_FLAG_INDEX            (WIFI_PASS_SET_FLAG_INDEX + FLAG_SIZE)
// #define SCOPE_ID_SET_FLAG_INDEX                     (GATEWAY_DEVICE_ID_SET_FLAG_INDEX + FLAG_SIZE)
// #define GROUP_PRIMARY_KEY_SET_FLAG_INDEX            (SCOPE_ID_SET_FLAG_INDEX + FLAG_SIZE)
// #define WEIDOS_MODEL_ID_SET_FLAG_INDEX              (GROUP_PRIMARY_KEY_SET_FLAG_INDEX + FLAG_SIZE)
// #define EM_3PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX   (WEIDOS_MODEL_ID_SET_FLAG_INDEX + FLAG_SIZE)
// #define EM_1PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX   (EM_3PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX + FLAG_SIZE)
// #define AZURE_DEVICE_ID_SET_FLAGS_INDEX             (EM_1PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX + FLAG_SIZE)
// #define AZURE_DEVICE_ID_SET_FLAGS_SIZE              (MAX_NUM_AZURE_DEVICES*FLAG_SIZE)
// #define AZURE_SAS_KEY_SET_FLAGS_INDEX               (AZURE_DEVICE_ID_SET_FLAGS_INDEX + AZURE_DEVICE_ID_SET_FLAGS_SIZE)
// #define AZURE_SAS_KEY_SET_FLAGS_SIZE                (MAX_NUM_AZURE_DEVICES*FLAG_SIZE)
// #define AZURE_SCOPE_ID_SET_FLAG_INDEX               (AZURE_SAS_KEY_SET_FLAGS_INDEX + AZURE_SAS_KEY_SET_FLAGS_SIZE)
// #define AZURE_SCOPE_ID_SET_FLAG_SIZE                (FLAG_SIZE)


// #define LAST_FLAG_INDEX     AZURE_SCOPE_ID_SET_FLAG_INDEX
// #define LAST_FLAG_SIZE      AZURE_SCOPE_ID_SET_FLAG_SIZE


// //Data
// #define WIFI_SSID_INDEX             (LAST_FLAG_INDEX + LAST_FLAG_SIZE)
// #define WIFI_SSID_SIZE              32

// #define WIFI_PASS_INDEX             (WIFI_SSID_INDEX + WIFI_SSID_SIZE)
// #define WIFI_PASS_SIZE              63

// #define GATEWAY_DEVICE_ID_INDEX     (WIFI_PASS_INDEX + WIFI_PASS_SIZE)
// #define GATEWAY_DEVICE_ID_SIZE      20

// #define SCOPE_ID_INDEX              (GATEWAY_DEVICE_ID_INDEX + GATEWAY_DEVICE_ID_SIZE)
// #define SCOPE_ID_SIZE               20

// #define GROUP_PRIMARY_KEY_INDEX     (SCOPE_ID_INDEX + SCOPE_ID_SIZE)
// #define GROUP_PRIMARY_KEY_SIZE      20

// #define WEIDOS_MODEL_ID_INDEX       (GROUP_PRIMARY_KEY_INDEX + GROUP_PRIMARY_KEY_SIZE)
// #define WEIDOS_MODEL_ID_SIZE        20

// #define EM_3PH_BASIC_LINE_MODEL_ID_INDEX    (WEIDOS_MODEL_ID_INDEX + WEIDOS_MODEL_ID_SIZE)
// #define EM_3PH_BASIC_LINE_MODEL_ID_SIZE     20

// #define EM_1PH_BASIC_LINE_MODEL_ID_INDEX    (EM_3PH_BASIC_LINE_MODEL_ID_INDEX + EM_3PH_BASIC_LINE_MODEL_ID_SIZE)
// #define EM_1PH_BASIC_LINE_MODEL_ID_SIZE     20

// #define DEVICE_CONFIGURATION_DATA_INDEX  (EM_1PH_BASIC_LINE_MODEL_ID_INDEX + EM_1PH_BASIC_LINE_MODEL_ID_SIZE)
// #define DEVICE_CONFIGURATION_DATA_SIZE  5

// #define EM_CONVERSION_FACTOR_INDEX (DEVICE_CONFIGURATION_DATA_INDEX + DEVICE_CONFIGURATION_DATA_SIZE)
// #define EM_CONVERSION_FACTOR_SIZE (MAX_ALLOWED_DEVICES*8)

// #define DEVICE_IDS_INDEX (EM_CONVERSION_FACTOR_INDEX + EM_CONVERSION_FACTOR_SIZE)
// #define DEVICE_IDS_SIZE (MAX_NUM_AZURE_DEVICES*AZURE_DEVICE_ID_SIZE)

// #define DEVICE_SAS_KEYS_INDEX (DEVICE_IDS_INDEX + DEVICE_IDS_SIZE)
// #define DEVICE_SAS_KEYS_SIZE (MAX_NUM_AZURE_DEVICES*AZURE_SAS_KEY_SIZE)

// #define AZURE_SCOPE_ID_INDEX (DEVICE_SAS_KEYS_INDEX + DEVICE_SAS_KEYS_SIZE)
// #define SCOPE_ID_SIZE (AZURE_SCOPE_ID_SIZE)


// #define INT_SIZE 4
// #define NUMBER_CONVERSION_FACTORS 2*MAX_ALLOWED_DEVICES
// #define EM_CONVERSION_FACTOR_SIZE (INT_SIZE*NUMBER_CONVERSION_FACTORS)




// //############ Flags ###########
// #define FLAG_SIZE 1
// #define FIRST_EEPROM_INDEX 1


// #define SCOPE_ID_SET_FLAG_INDEX                     (GATEWAY_DEVICE_ID_SET_FLAG_INDEX + FLAG_SIZE)

// #define AZURE_DEVICE_ID_SET_FLAGS_INDEX             (EM_1PH_BASIC_LINE_MODEL_ID_SET_FLAG_INDEX + FLAG_SIZE)
// #define AZURE_DEVICE_ID_SET_FLAGS_SIZE              (MAX_NUM_AZURE_DEVICES*FLAG_SIZE)
// #define AZURE_SAS_KEY_SET_FLAGS_INDEX               (AZURE_DEVICE_ID_SET_FLAGS_INDEX + AZURE_DEVICE_ID_SET_FLAGS_SIZE)
// #define AZURE_SAS_KEY_SET_FLAGS_SIZE                (MAX_NUM_AZURE_DEVICES*FLAG_SIZE)

// /*########## Azure Parameters ############
// EEPROM section to store Azure related parameters:
// - Scope ID (size: SCOPE_ID_SIZE)
// - Azure Device IDs (Array of Azure Device IDs):
//     · Number of Azure Device IDs = NUM_AZURE_DEVICES (see Note 1.)
//     · Size of each Azure Device ID = 
// - Azure SAS Keys (Array of Azure SAS Keys):
//     · Number of Azure SAS Keys = NUM_AZURE_DEVICES (see Note 1.)



// Note 1: NUM_EEPROM_AZURE_DEVICES is greater than MAX_NUM_AZURE_DEVICES defined in "AzureIoTCollection.h".
// MAX_NUM_AZURE_DEVICES is currently limited to the number of Ethernet sockets available. If in the future this limitation
// is overpassed and MAX_NUM_AZURE_DEVICES is increased, it will already have room in the EEPROM for the new devices without 
// having to change EEPROM indixes (EEPROM mapping). Changing EEPROM map would imply that an updated Weidos would have to be
// reconfigured via Web Server.
// */









static const int FIRST_AZURE_DATA_INDEX = 1;
static const int FIRST_ENERGY_METER_DATA_INDEX = 3000;
static const int FIRST_PULSE_ANALOG_DATA_INDEX = 5000;

static const int FLAG_SIZE = 1;
static const int UINT8_T_SIZE = 1;
static const int FLOAT_SIZE = 4;
static const int IP_SIZE = 4;
static const int PIN_SIZE = 4;

static const int NUM_MAX_DEVICES_EEPROM = 20;


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
static const int AZURE_DEVICES_IDS_SIZE = AZURE_DEVICE_ID_SIZE*NUM_MAX_DEVICES_EEPROM;



static const int AZURE_SAS_KEY_SET_FLAGS_INDEX = AZURE_DEVICE_IDS_INDEX + AZURE_DEVICES_IDS_SIZE;
static const int AZURE_SAS_KEY_SET_FLAGS_SIZE = AZURE_SAS_KEY_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int AZURE_SAS_KEYS_INDEX = AZURE_SAS_KEY_SET_FLAGS_INDEX + AZURE_SAS_KEY_SET_FLAGS_SIZE;
static const int AZURE_SAS_KEYS_SIZE = AZURE_SAS_KEY_SIZE*NUM_MAX_DEVICES_EEPROM;



/* ######### Energy Meter Data ##########


*/
static const int MODBUS_ID_SET_FLAGS_INDEX = FIRST_ENERGY_METER_DATA_INDEX;
static const int MODBUS_ID_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int MODBUS_IDS_INDEX = MODBUS_ID_SET_FLAGS_INDEX + MODBUS_ID_SET_FLAGS_SIZE;
static const int MODBUS_IDS_SIZE = UINT8_T_SIZE*NUM_MAX_DEVICES_EEPROM;



static const int MODBUS_TCP_IP_FLAGS_INDEX = MODBUS_IDS_INDEX + MODBUS_IDS_SIZE;
static const int MODBUS_TCP_IP_SET_FLAGS_SIZE = IP_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int MODBUS_TCP_IPS_INDEX = MODBUS_TCP_IP_FLAGS_INDEX + MODBUS_TCP_IP_SET_FLAGS_SIZE;
static const int MODBUS_TCP_IPS_SIZE = UINT8_T_SIZE*NUM_MAX_DEVICES_EEPROM;



static const int CT_PRIMARY_SET_FLAGS_INDEX = MODBUS_TCP_IPS_INDEX + MODBUS_TCP_IPS_SIZE;
static const int CT_PRIMARY_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int CT_PRIMARY_INDEX = CT_PRIMARY_SET_FLAGS_INDEX + CT_PRIMARY_SET_FLAGS_SIZE;
static const int CT_PRIMARY_SIZE = FLOAT_SIZE*NUM_MAX_DEVICES_EEPROM;



static const int CT_SECONDARY_SET_FLAGS_INDEX = CT_PRIMARY_INDEX + CT_PRIMARY_SIZE;
static const int CT_SECONDARY_SET_FLAGS_SIZE = FLAG_SIZE*NUM_MAX_DEVICES_EEPROM;

static const int CT_SECONDARY_INDEX = CT_SECONDARY_SET_FLAGS_INDEX + CT_SECONDARY_SET_FLAGS_SIZE;
static const int CT_SECONDARY_SIZE = FLOAT_SIZE*NUM_MAX_DEVICES_EEPROM;




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
