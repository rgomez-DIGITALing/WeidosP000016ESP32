#include "globalConfiguration.h"


#ifdef USING_WEB_SERVER
//Clients to be used for all Modbus TCP
EthernetClient ethernetClientModbus(7);
ModbusTCPClient modbusTCPClient(ethernetClientModbus);
#endif
