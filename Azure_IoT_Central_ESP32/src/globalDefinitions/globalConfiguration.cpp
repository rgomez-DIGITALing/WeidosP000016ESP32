#include "globalConfiguration.h"



//Clients to be used for all Modbus TCP
EthernetClient ethernetClientModbus(7);
ModbusTCPClient modbusTCPClient(ethernetClientModbus);

