#include "globalConfiguration.h"


// uint8_t MAX_DEVICE_TYPE = PULSE_METER_DEVICE_TYPE;

EthernetClient ethernetClientModbus(7);
ModbusTCPClient modbusTCPClient(ethernetClientModbus);

