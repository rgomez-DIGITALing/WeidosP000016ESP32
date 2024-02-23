#include "EM3PH_TCP_ValueLine.h"



#define MODBUS_ADDRESS      1
#define MODBUS_TIMEOUT      100


#define REG_ADDRESS_BATCH_1         19000
#define NUM_REGISTERS_BATCH_1       122
#define NUM_DATA_BATCH_1            NUM_REGISTERS_BATCH_1/2

#define REG_ADDRESS_BATCH_2         826
#define NUM_REGISTERS_BATCH_2       22
#define NUM_DATA_BATCH_2            NUM_REGISTERS_BATCH_2/2

#define REG_ADDRESS_BATCH_3         10085
#define NUM_REGISTERS_BATCH_3       2
#define NUM_DATA_BATCH_3            NUM_REGISTERS_BATCH_3/2



// EM3PH_TCP_ValueLine::EM3PH_TCP_ValueLine(ModbusTCPClient& client, IPAddress ipAddress) : _client(client), ipAddress(ipAddress), prevDataAvailable(false){}
EM3PH_TCP_ValueLine::EM3PH_TCP_ValueLine(ModbusTCPClient& client, IPAddress ipAddress) : _client(client), EM3PH_BaseClass(ipAddress){}
EM3PH_TCP_ValueLine::EM3PH_TCP_ValueLine(uint8_t modbusId, ModbusTCPClient& client, IPAddress ipAddress) : _client(client), EM3PH_BaseClass(modbusId, ipAddress){}

int EM3PH_TCP_ValueLine::begin(){
    _client.setTimeout(MODBUS_TIMEOUT);
    comError = COM_OK;
    if(_client.begin(ipAddress)) return 1;

    comError = COM_BEGIN_ERROR;
    return 0;
}

void EM3PH_TCP_ValueLine::stop(){
  _client.stop();
  return;
}

int EM3PH_TCP_ValueLine::update(){
    comError = COM_OK;
    
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

    computeData();

    return 1;
}


// void EM3PH_TCP_ValueLine::validateData(){
//   for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++){
//     if(isnan(data[i])) data[i] = -1;
//   }
  
//   return;
// }


float* EM3PH_TCP_ValueLine::getData(){
  return data;
};

void EM3PH_TCP_ValueLine::assignData(){
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
    realEnergyTotal = getNextData()/1000.0f;//31

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
    getNextData();      //reactiveEnergyIndL1 deleted variable
    getNextData();      //reactiveEnergyIndL2 deleted variable   
    getNextData();      //reactiveEnergyIndL3 deleted variable    
    getNextData();      //reactiveEnergyIndTotal deleted variable
    getNextData();      //reactiveEnergyCapL1 deleted variable
    getNextData();      //reactiveEnergyCapL2 deleted variable
    getNextData();      //reactiveEnergyCapL3 deleted variable
    getNextData();      //reactiveEnergyCapTotal deleted variable
    THDVoltsL1N = getNextData();
    THDVoltsL2N = getNextData();
    THDVoltsL3N = getNextData();
    THDCurrentL1N = getNextData();
    THDCurrentL2N = getNextData();
    THDCurrentL3N = getNextData();
}

void EM3PH_TCP_ValueLine::assignData2(){
    cosPhiTotal = getNextData();
    powerFactorL1N = getNextData();
    powerFactorL2N = getNextData();
    powerFactorL3N = getNextData();
    powerFactorTotal = getNextData();
    getNextData();
    getNextData();
    getNextData();
    THDVoltsL1L2 = getNextData();
    THDVoltsL2L3 = getNextData();
    THDVoltsL1L3 = getNextData();


    Serial.println("[assignData EM]");
    Serial.print("THDVoltsL1L2: ");
    Serial.println(THDVoltsL1L2);
    Serial.print("THDVoltsL2L3: ");
    Serial.println(THDVoltsL2L3);
    Serial.print("THDVoltsL1L3: ");
    Serial.println(THDVoltsL1L3);
}

void EM3PH_TCP_ValueLine::assignData3(){
    currentNeutral = getNextData();
}

void EM3PH_TCP_ValueLine::computeData(){
    avgVoltageLN = (voltageL1N + voltageL2N + voltageL3N)/3.0f;
    avgVoltageLL = (voltageL1L2 + voltageL2L3 + voltageL1L3)/3.0f;
    avgCurrentL = (currentL1 + currentL2 + currentL3)/3.0f;

    // if(apparentPowerTotal != 0) avgCosPhi = realPowerTotal/apparentPowerTotal;
    // else avgCosPhi = -1;
    // if(isnan(avgCosPhi)) avgCosPhi = -1;  //Check if, after all, it is still NaN

    avgTHDVoltsLN = (THDVoltsL1N + THDVoltsL2N + THDVoltsL3N)/3.0f;
    avgTHDCurrentLN = (THDCurrentL1N + THDCurrentL2N + THDCurrentL3N)/3.0f;
    avgTHDVoltsLL = (THDVoltsL1L2 + THDVoltsL2L3 + THDVoltsL1L3)/3.0f;

    
    realEnergyAdjustedL1 = realEnergyConsL1 + realEnergyDelivL1;
    realEnergyAdjustedL2 = realEnergyConsL2 + realEnergyDelivL2;
    realEnergyAdjustedL3 = realEnergyConsL3 + realEnergyDelivL3;
    realEnergyAdjustedTotal = realEnergyAdjustedL1 + realEnergyAdjustedL2 + realEnergyAdjustedL3;

    realEnergyConsTotalSum = realEnergyConsL1 + realEnergyConsL2 + realEnergyConsL3;
    realEnergyDelivTotalSum = realEnergyDelivL1 + realEnergyDelivL2 + realEnergyDelivL3;

    // Serial.println("[comptueData]");
    // Serial.print("realEnergyConsL1: ");
    // Serial.println(realEnergyConsL1);
    // Serial.print("realEnergyConsL2: ");
    // Serial.println(realEnergyConsL2);
    // Serial.print("realEnergyConsL3: ");
    // Serial.println(realEnergyConsL3);
    // Serial.print("realEnergyAdjustedL1: ");
    // Serial.println(realEnergyAdjustedL1);
    // Serial.print("realEnergyAdjustedL2: ");
    // Serial.println(realEnergyAdjustedL2);
    // Serial.print("realEnergyAdjustedL3: ");
    // Serial.println(realEnergyAdjustedL3);
}

float EM3PH_TCP_ValueLine::getNextData(){
    long msb = _client.read();
    long lsb =  _client.read();
    uint32_t rawData = (msb << 16) + lsb; // Bit Shift operation to join both registers
    float data = *(float *)&rawData; 
    return data;
};


void EM3PH_TCP_ValueLine::updatePreviousValues(){
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
