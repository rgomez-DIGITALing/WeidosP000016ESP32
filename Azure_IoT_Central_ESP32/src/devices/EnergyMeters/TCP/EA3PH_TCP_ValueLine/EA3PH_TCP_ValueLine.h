#pragma once
#include <ArduinoModbus.h>
#include "../../EM3PH_BaseClass/EM3PH_BaseClass.h"
// #include "../EMDataDefinitions.h"
// #include "../em_telemetryDefinition.h"



class EA3PH_TCP_ValueLine : public EM3PH_BaseClass{
  public:
    
    EA3PH_TCP_ValueLine(ModbusTCPClient& client, IPAddress ipAddress);
    EA3PH_TCP_ValueLine(uint8_t modbusId, ModbusTCPClient& client, IPAddress ipAddress);
    
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

    void validateData();

    
  
    float* getData();
    void resetPrevValues(){ prevDataAvailable = false; }
    void updatePreviousValues();



  private:

    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the first batch.
     */
    void assignData();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the second batch.
     */
    void assignData2();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the third batch.
     */
    void assignData3();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the forth batch.
     */
    void assignData4();
    /**
     * Read from the Modbus Client buffer and assign all bytes to its corresponding variable for the
     * registers corresponding to the forth batch.
     */
    void assignData5();

    void computeData();
    /**
     * Read two bytes from the Modbus Client and join them to cast it into a float variable.
     *  
     * @return Register's data.
     */
    float getNextData();

    
    ModbusTCPClient& _client;
};
