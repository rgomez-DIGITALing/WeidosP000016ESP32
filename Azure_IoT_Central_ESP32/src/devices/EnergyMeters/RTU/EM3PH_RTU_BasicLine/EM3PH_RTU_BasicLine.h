#pragma once
#include "../../EM3PH_BaseClass/EM3PH_BaseClass.h"

#include "../../EMDataDefinitions.h"
#include "../../em_telemetryDefinition.h"


class EM3PH_RTU_BasicLine : public EM3PH_BaseClass{
  public:
    EM3PH_RTU_BasicLine(uint8_t modbusId);
    
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

    void updatePreviousValues() override;

  

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
     * registers corresponding to the second batch.
     */
    void computeValues();
    /**
     * Read two bytes from the Modbus Client and join them to cast it into a float variable.
     *  
     * @return Register's data.
     */
    float getNextData();

};
