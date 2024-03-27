#pragma once
#include <ArduinoModbus.h>
#include "../../EM3PH_BaseClass/EM3PH_BaseClass.h"

// #include "../../EMDataDefinitions.h"
// #include "../../em_telemetryDefinition.h"


class EM3PH_TCP_BasicLine : public EM3PH_BaseClass{
  public:
    EM3PH_TCP_BasicLine(ModbusTCPClient& client, IPAddress ipAddress);
    EM3PH_TCP_BasicLine(uint8_t modbusId, ModbusTCPClient& client, IPAddress ipAddress);
    
    /**
     * Begin Modbus RTU Client with default Configuration (Baudrate = 9600 and config = SERIAL_8N1).
     *
     *
     * @return 0 on failure, number of values read on success
    */
    int begin();

    void stop();

    /**
     * Update attributes by requesting all registers. 
     *
     *
     * @return 0 on failure, 1 on success
     */
    int update();
    

    void updatePreviousValues() override;

    void setSkipVariables() override;
  

  private:
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the batch.
     */
    void assignData();
    void assignData2();
    void assignData3();
    void computeValues();
    /**
     * Read two bytes from the Modbus Client and join them to cast it into a float variable.
     *  
     * @return Register's data.
     */
    float getNextData();

    ModbusTCPClient& _client;
};
