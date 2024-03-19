#include "EA3PH_TCP_ValueLine.h"



#define MODBUS_ADDRESS      1
#define MODBUS_TIMEOUT      100


#define REG_ADDRESS_BATCH_1         19000
#define NUM_REGISTERS_BATCH_1       94
#define NUM_DATA_BATCH_1            NUM_REGISTERS_BATCH_1/2

#define REG_ADDRESS_BATCH_2         3793
#define NUM_REGISTERS_BATCH_2       6
#define NUM_DATA_BATCH_2            NUM_REGISTERS_BATCH_2/2

#define REG_ADDRESS_BATCH_3         3893
#define NUM_REGISTERS_BATCH_3       6
#define NUM_DATA_BATCH_3            NUM_REGISTERS_BATCH_3/2

#define REG_ADDRESS_BATCH_4         3859
#define NUM_REGISTERS_BATCH_4       2
#define NUM_DATA_BATCH_4            NUM_REGISTERS_BATCH_4/2

#define REG_ADDRESS_BATCH_5         3929
#define NUM_REGISTERS_BATCH_5       2
#define NUM_DATA_BATCH_5            NUM_REGISTERS_BATCH_5/2

#define REG_ADDRESS_BATCH_6         3805
#define NUM_REGISTERS_BATCH_6       16
#define NUM_DATA_BATCH_6            NUM_REGISTERS_BATCH_6/2


//Batches for Harmonics
//L1L2 Voltage harmonics
#define REG_ADDRESS_BATCH_7         17
#define NUM_REGISTERS_BATCH_7       26
#define NUM_DATA_BATCH_7            NUM_REGISTERS_BATCH_7/2

//L2L3 Voltage harmonics
#define REG_ADDRESS_BATCH_8         143
#define NUM_REGISTERS_BATCH_8       26
#define NUM_DATA_BATCH_8            NUM_REGISTERS_BATCH_8/2

//L3L1 Voltage harmonics
#define REG_ADDRESS_BATCH_9         269
#define NUM_REGISTERS_BATCH_9       26
#define NUM_DATA_BATCH_9            NUM_REGISTERS_BATCH_9/2

//L1 Voltage harmonics
#define REG_ADDRESS_BATCH_10         395
#define NUM_REGISTERS_BATCH_10       26
#define NUM_DATA_BATCH_10            NUM_REGISTERS_BATCH_10/2


//L2 Voltage harmonics
#define REG_ADDRESS_BATCH_11         521
#define NUM_REGISTERS_BATCH_11       26
#define NUM_DATA_BATCH_11            NUM_REGISTERS_BATCH_11/2


//L3 Voltage harmonics
#define REG_ADDRESS_BATCH_12         647
#define NUM_REGISTERS_BATCH_12       26
#define NUM_DATA_BATCH_12            NUM_REGISTERS_BATCH_12/2

//L4 Voltage harmonics
#define REG_ADDRESS_BATCH_13         773
#define NUM_REGISTERS_BATCH_13       26
#define NUM_DATA_BATCH_13            NUM_REGISTERS_BATCH_13/2

//L1 Current harmonics
#define REG_ADDRESS_BATCH_14         899
#define NUM_REGISTERS_BATCH_14       26
#define NUM_DATA_BATCH_14            NUM_REGISTERS_BATCH_14/2

//L2 Current harmonics
#define REG_ADDRESS_BATCH_15         1025
#define NUM_REGISTERS_BATCH_15       26
#define NUM_DATA_BATCH_15            NUM_REGISTERS_BATCH_15/2

//L3 Current harmonics
#define REG_ADDRESS_BATCH_16         1151
#define NUM_REGISTERS_BATCH_16       26
#define NUM_DATA_BATCH_16            NUM_REGISTERS_BATCH_16/2

//L4 Current harmonics
#define REG_ADDRESS_BATCH_17         1277
#define NUM_REGISTERS_BATCH_17       26
#define NUM_DATA_BATCH_17            NUM_REGISTERS_BATCH_17/2










EA3PH_TCP_ValueLine::EA3PH_TCP_ValueLine(ModbusTCPClient& client, IPAddress ipAddress) : _client(client), EM3PH_BaseClass(ipAddress){}
EA3PH_TCP_ValueLine::EA3PH_TCP_ValueLine(uint8_t modbusId, ModbusTCPClient& client, IPAddress ipAddress) : _client(client), EM3PH_BaseClass(modbusId, ipAddress){}



int EA3PH_TCP_ValueLine::begin(){
    _client.setTimeout(MODBUS_TIMEOUT);
    comError = COM_OK;
    if(_client.begin(ipAddress)) return 1;

    comError = COM_BEGIN_ERROR;
    return 0;
}

void EA3PH_TCP_ValueLine::stop(){
  _client.stop();
  return;
}

int EA3PH_TCP_ValueLine::update(){
    int response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_1, NUM_REGISTERS_BATCH_1);
    if(response != NUM_REGISTERS_BATCH_1)
    {   
        comError = COM_BATCH_1_ERROR;
        return 0;
    }
    assignData();


    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_2, NUM_REGISTERS_BATCH_2);
    if(response != NUM_REGISTERS_BATCH_2)
    {
        comError = COM_BATCH_2_ERROR;
        return 0;
    }
    assignData2();
    

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_3, NUM_REGISTERS_BATCH_3);  
    if(response != NUM_REGISTERS_BATCH_3)
    {
        comError = COM_BATCH_3_ERROR;
        return 0;
    }
    assignData3();


    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_4, NUM_REGISTERS_BATCH_4);  
    if(response != NUM_REGISTERS_BATCH_4)
    {
        comError = COM_BATCH_4_ERROR;
        return 0;
    }
    assignData4();


    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_5, NUM_REGISTERS_BATCH_5);  
    if(response != NUM_REGISTERS_BATCH_5)
    {
        comError = COM_BATCH_5_ERROR;
        return 0;
    }
    assignData5();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_6, NUM_REGISTERS_BATCH_6);  
    if(response != NUM_REGISTERS_BATCH_6)
    {
        comError = COM_BATCH_6_ERROR;
        return 0;
    }
    assignData6();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_7, NUM_REGISTERS_BATCH_7);  
    if(response != NUM_REGISTERS_BATCH_7)
    {
        comError = COM_BATCH_7_ERROR;
        return 0;
    }
    assignData7();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_8, NUM_REGISTERS_BATCH_8);  
    if(response != NUM_REGISTERS_BATCH_8)
    {
        comError = COM_BATCH_8_ERROR;
        return 0;
    }
    assignData8();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_9, NUM_REGISTERS_BATCH_9);  
    if(response != NUM_REGISTERS_BATCH_9)
    {
        comError = COM_BATCH_9_ERROR;
        return 0;
    }
    assignData9();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_10, NUM_REGISTERS_BATCH_10);  
    if(response != NUM_REGISTERS_BATCH_10)
    {
        comError = COM_BATCH_10_ERROR;
        return 0;
    }
    assignData10();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_11, NUM_REGISTERS_BATCH_11);  
    if(response != NUM_REGISTERS_BATCH_11)
    {
        comError = COM_BATCH_11_ERROR;
        return 0;
    }
    assignData11();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_12, NUM_REGISTERS_BATCH_12);  
    if(response != NUM_REGISTERS_BATCH_12)
    {
        comError = COM_BATCH_12_ERROR;
        return 0;
    }
    assignData12();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_13, NUM_REGISTERS_BATCH_13);  
    if(response != NUM_REGISTERS_BATCH_13)
    {
        comError = COM_BATCH_13_ERROR;
        return 0;
    }
    assignData13();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_14, NUM_REGISTERS_BATCH_14);  
    if(response != NUM_REGISTERS_BATCH_14)
    {
        comError = COM_BATCH_14_ERROR;
        return 0;
    }
    assignData14();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_15, NUM_REGISTERS_BATCH_15);  
    if(response != NUM_REGISTERS_BATCH_15)
    {
        comError = COM_BATCH_15_ERROR;
        return 0;
    }
    assignData15();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_16, NUM_REGISTERS_BATCH_16);  
    if(response != NUM_REGISTERS_BATCH_16)
    {
        comError = COM_BATCH_16_ERROR;
        return 0;
    }
    assignData16();

    response = _client.requestFrom(modbusId, INPUT_REGISTERS, REG_ADDRESS_BATCH_17, NUM_REGISTERS_BATCH_17);  
    if(response != NUM_REGISTERS_BATCH_17)
    {
        comError = COM_BATCH_17_ERROR;
        return 0;
    }
    assignData17();


    computeData();


    
    return 1;
}


// void EA3PH_TCP_ValueLine::validateData(){
//   for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++){
//     if(isnan(data[i])) data[i] = -1;
//   }
  
//   return;
// }

void EA3PH_TCP_ValueLine::setSkipVariables(){
        phaseCurrentSum = SKIP_DATA_VALUE;

        return;
}


float* EA3PH_TCP_ValueLine::getData(){
  return data;
};

void EA3PH_TCP_ValueLine::assignData(){
    voltageL1N = getNextData();
    voltageL2N = getNextData();
    voltageL3N = getNextData();
    voltageL1L2 = getNextData();
    voltageL2L3 = getNextData();
    voltageL1L3 = getNextData();
    currentL1 = getNextData();
    currentL2 = getNextData();
    currentL3 = getNextData();
    currentTotal = getNextData();
    realPowerL1N = getNextData();
    realPowerL2N = getNextData();
    realPowerL3N = getNextData();
    realPowerTotal = getNextData();
    apparentPowerL1N = getNextData();
    apparentPowerL2N = getNextData();
    apparentPowerL3N = getNextData();
    apparentPowerTotal = getNextData();
    reactivePowerL1N = getNextData();
    reactivePowerL2N = getNextData();
    reactivePowerL3N = getNextData();
    reactivePowerTotal = getNextData();
    cosPhiL1 = getNextData();
    cosPhiL2 = getNextData();
    cosPhiL3 = getNextData();
    frequency = getNextData();
    rotField = getNextData();
    realEnergyL1 = getNextData()/1000.0f;
    realEnergyL2 = getNextData()/1000.0f;
    realEnergyL3 = getNextData()/1000.0f;
    realEnergyTotal = getNextData()/1000.0f;
    realEnergyConsL1 = getNextData()/1000.0f;       //realEnergyConsL1 deleted variable
    realEnergyConsL2 = getNextData()/1000.0f;       //realEnergyConsL2 deleted variable
    realEnergyConsL3 = getNextData()/1000.0f;       //realEnergyConsL3 deleted variable
    realEnergyConsTotal = getNextData()/1000.0f;      //realEnergyConsTotal deleted variable
    realEnergyDelivL1 = getNextData()/1000.0f;      //realEnergyDelivL1 deleted variable     
    realEnergyDelivL2 = getNextData()/1000.0f;      //realEnergyDelivL2 deleted variable
    realEnergyDelivL3 = getNextData()/1000.0f;      //realEnergyDelivL3 deleted variable
    realEnergyDelivTotal = getNextData()/1000.0f;      //realEnergyDelivTotal deleted variable
    apparentEnergyL1 = getNextData()/1000.0f;
    apparentEnergyL2 = getNextData()/1000.0f;
    apparentEnergyL3 = getNextData()/1000.0f;
    apparentEnergyTotal = getNextData()/1000.0f;
    reactiveEnergyL1 = getNextData()/1000.0f;
    reactiveEnergyL2 = getNextData()/1000.0f;
    reactiveEnergyL3 = getNextData()/1000.0f;
    reactiveEnergyTotal = getNextData()/1000.0f;
    // getNextData();      //reactiveEnergyIndL1 deleted variable
    // getNextData();      //reactiveEnergyIndL2 deleted variable
    // getNextData();      //reactiveEnergyIndL3 deleted variable
    // getNextData();      //reactiveEnergyIndTotal deleted variable
    // getNextData();      //reactiveEnergyCapL1 deleted variable
    // getNextData();      //reactiveEnergyCapL2 deleted variable
    // getNextData();      //reactiveEnergyCapL3 deleted variable
    // getNextData();      //reactiveEnergyCapTotal deleted variable
    // THDVoltsL1N = getNextData();
    // THDVoltsL2N = getNextData();
    // THDVoltsL3N = getNextData();
    // THDCurrentL1 = getNextData();
    // THDCurrentL2 = getNextData();
    // THDCurrentL3 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData2(){
    THDVoltsL1L2 = getNextData();
    THDVoltsL2L3 = getNextData();
    THDVoltsL1L3 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData3(){
    powerFactorL1N = getNextData();
    powerFactorL2N = getNextData();
    powerFactorL3N = getNextData();
}

void EA3PH_TCP_ValueLine::assignData4(){
    currentNeutral = getNextData();
}

void EA3PH_TCP_ValueLine::assignData5(){
    cosPhiTotal = getNextData();
}



void EA3PH_TCP_ValueLine::assignData6(){
    THDVoltsL1N = getNextData();
    THDVoltsL2N = getNextData();
    THDVoltsL3N = getNextData();
    THDVoltsL4N = getNextData();
    THDCurrentL1 = getNextData();
    THDCurrentL2 = getNextData();
    THDCurrentL3 = getNextData();
    THDCurrentL4 = getNextData();
}


void EA3PH_TCP_ValueLine::assignData7(){
    HVolts3L1L2 = getNextData();
    HVolts5L1L2 = getNextData();
    HVolts7L1L2 = getNextData();
    HVolts9L1L2 = getNextData();
    HVolts11L1L2 = getNextData();
    HVolts13L1L2 = getNextData();
    HVolts15L1L2 = getNextData();

}

void EA3PH_TCP_ValueLine::assignData8(){
    HVolts3L2L3 = getNextData();
    HVolts5L2L3 = getNextData();
    HVolts7L2L3 = getNextData();
    HVolts9L2L3 = getNextData();
    HVolts11L2L3 = getNextData();
    HVolts13L2L3 = getNextData();
    HVolts15L2L3 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData9(){
    HVolts3L3L1 = getNextData();
    HVolts5L3L1 = getNextData();
    HVolts7L3L1 = getNextData();
    HVolts9L3L1 = getNextData();
    HVolts11L3L1 = getNextData();
    HVolts13L3L1 = getNextData();
    HVolts15L3L1 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData10(){
    HVolts3L1 = getNextData();
    HVolts5L1 = getNextData();
    HVolts7L1 = getNextData();
    HVolts9L1 = getNextData();
    HVolts11L1 = getNextData();
    HVolts13L1 = getNextData();
    HVolts15L1 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData11(){
    HVolts3L2 = getNextData();
    HVolts5L2 = getNextData();
    HVolts7L2 = getNextData();
    HVolts9L2 = getNextData();
    HVolts11L2 = getNextData();
    HVolts13L2 = getNextData();
    HVolts15L2 = getNextData(); 
}

void EA3PH_TCP_ValueLine::assignData12(){
    HVolts3L3 = getNextData();
    HVolts5L3 = getNextData();
    HVolts7L3 = getNextData();
    HVolts9L3 = getNextData();
    HVolts11L3 = getNextData();
    HVolts13L3 = getNextData();
    HVolts15L3 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData13(){
    HVolts3L4 = getNextData();
    HVolts5L4 = getNextData();
    HVolts7L4 = getNextData();
    HVolts9L4 = getNextData();
    HVolts11L4 = getNextData();
    HVolts13L4 = getNextData();
    HVolts15L4 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData14(){
    HCurrent3L1 = getNextData();
    HCurrent5L1 = getNextData();
    HCurrent7L1 = getNextData();
    HCurrent9L1 = getNextData();
    HCurrent11L1 = getNextData();
    HCurrent13L1 = getNextData();
    HCurrent15L1 = getNextData();
}

void EA3PH_TCP_ValueLine::assignData15(){
    HCurrent3L2 = getNextData();
    HCurrent5L2 = getNextData();
    HCurrent7L2 = getNextData();
    HCurrent9L2 = getNextData();
    HCurrent11L2 = getNextData();
    HCurrent13L2 = getNextData();
    HCurrent15L2 = getNextData();

}

void EA3PH_TCP_ValueLine::assignData16(){
    HCurrent3L3 = getNextData();
    HCurrent5L3 = getNextData();
    HCurrent7L3 = getNextData();
    HCurrent9L3 = getNextData();
    HCurrent11L3 = getNextData();
    HCurrent13L3 = getNextData();
    HCurrent15L3 = getNextData();

}

void EA3PH_TCP_ValueLine::assignData17(){
    HCurrent3L4 = getNextData();
    HCurrent5L4 = getNextData();
    HCurrent7L4 = getNextData();
    HCurrent9L4 = getNextData();
    HCurrent11L4 = getNextData();
    HCurrent13L4 = getNextData();
    HCurrent15L4 = getNextData();
}


void EA3PH_TCP_ValueLine::computeData(){
    powerFactorTotal = realPowerTotal/apparentPowerTotal;

    avgVoltageLN = (voltageL1N + voltageL2N + voltageL3N)/3.0f;
    avgVoltageLL = (voltageL1L2 + voltageL2L3 + voltageL1L3)/3.0f;
    avgCurrentL = (currentL1 + currentL2 + currentL3)/3.0f;

    // if(apparentPowerTotal != 0) cosPhiTotal = realPowerTotal/apparentPowerTotal;
    // else cosPhiTotal = -1;
    // if(isnan(cosPhiTotal)) cosPhiTotal = -1;  //Check if, after all, it is still NaN

    avgTHDVoltsLN = (THDVoltsL1N + THDVoltsL2N + THDVoltsL3N)/3.0f;
    avgTHDCurrentL = (THDCurrentL1 + THDCurrentL2 + THDCurrentL3)/3.0f;
    avgTHDVoltsLL = (THDVoltsL1L2 + THDVoltsL2L3 + THDVoltsL1L3)/3.0f;


    realEnergyAdjustedL1 = realEnergyConsL1 + realEnergyDelivL1;
    realEnergyAdjustedL2 = realEnergyConsL2 + realEnergyDelivL2;
    realEnergyAdjustedL3 = realEnergyConsL3 + realEnergyDelivL3;
    realEnergyAdjustedTotal = realEnergyAdjustedL1 + realEnergyAdjustedL2 + realEnergyAdjustedL3;

    realEnergyConsTotalSum = realEnergyConsL1 + realEnergyConsL2 + realEnergyConsL3;
    realEnergyDelivTotalSum = realEnergyDelivL1 + realEnergyDelivL2 + realEnergyDelivL3;
}

float EA3PH_TCP_ValueLine::getNextData(){
    long msb = _client.read();
    long lsb =  _client.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData; 
    return data;
};

void EA3PH_TCP_ValueLine::updatePreviousValues(){
  prevRealEnergyAdjustedL1 = realEnergyAdjustedL1;
  prevRealEnergyAdjustedL2 = realEnergyAdjustedL2;
  prevRealEnergyAdjustedL3 = realEnergyAdjustedL3;
  prevRealEnergyAdjustedTotal = realEnergyAdjustedTotal;
  prevApparentEnergyL1 = apparentEnergyL1;
  prevApparentEnergyL2 = apparentEnergyL2;
  prevApparentEnergyL3 = apparentEnergyL3;
  prevApparentEnergyTotal = apparentEnergyTotal;
  prevReactiveEnergyL1 = reactiveEnergyL1;
  prevReactiveEnergyL2 = reactiveEnergyL2;
  prevReactiveEnergyL3 = reactiveEnergyL3;
  prevReactiveEnergyTotal = reactiveEnergyTotal;

  prevDataAvailable = true;
}
