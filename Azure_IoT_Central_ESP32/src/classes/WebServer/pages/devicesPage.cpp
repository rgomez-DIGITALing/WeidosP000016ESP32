#include "devicesPage.h"
#include "../../../collections/DeviceCollections/DeviceCollection.h"
#include "../../../collections/AzureIoTCollection/AzureIoTCollection.h"
#include "../../../classes/PersistentData/PersistentDataClass.h"



char* documentBegin = R"rawliteral(
        <!DOCTYPE html>
        <html lang="en">
        <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">)rawliteral";

char* documentEnd = "</html>";



char* nav = R"rawliteral(
        <nav class="box">
          <a href="/Home">Home</a>
          <a href="/devices">Devices</a>
          <a href="/ipConfig">IP Configuration</a>
          <a href="/Contact">Contact</a>
        </nav>)rawliteral";


void writeTitle(AsyncResponseStream *response, char* title){
  response->print("<title>");
  response->print(title);
  response->print("</title>");
}



void sendDevicesPage(AsyncResponseStream *response){


    response->print(R"rawliteral(
        <!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Devices</title>
  <style>
    .box{
      border: 1px solid #000;
    }
    .slot{
      width: 240px;
      /* border: 1px solid #000; */
      position: relative;
      align-items: center;
      justify-content: center;
      text-align: center;
    }
    .slotsContainer{
      display: flex;
      flex-direction: row;
      flex-wrap: wrap;
      justify-content: center;
      width: 100%;
    }
    .deviceButton{
      align-items: center;
      justify-content: center;
      text-decoration: none;
      display: inline-flex;
      height:150px;
      width:150px;
      margin: 25px;
      font-size: 25px;
      background-color: #eb8c00;
      color: #fff;
      border: none;
      border-radius: 5px;
      cursor: pointer;
      transition: transform 0.3s ease;
    }

    .deviceButton:hover {
      transform: scale(1.1);
    }
    .topleft {
      position: relative;
      top: 0px;
      left: 0px;
      margin:0px;
      font-size: 18px;
    }
  </style>
</head>
<body>
    <div style="display:flex; flex-direction: column;">
        <nav class="box">
          <a href="#">Home</a>
          <a href="#">Devices</a>
          <a href="#">IP Configuration</a>
          <a href="#">Contact</a>
        </nav>
        <main class="box">
          <div class="slotsContainer">
        )rawliteral");

        // char* namesTest[] = {"EM111", "EM220", "+", "EM750", "Pulse Meter"};
        for(int i=0; i<6; i++){
            response->print(R"rawliteral(<div class="slot"><h3 class="topleft" >Slot )rawliteral");
            response->print(i);
            response->print(R"rawliteral(:</h3><a class="deviceButton" href="/deviceForm?slot=)rawliteral");
            response->print(i);
            response->print("\">");
            response->print(DeviceCollection.getDeviceName(i));
            response->print(R"rawliteral(</a></div>)rawliteral");
        }
        response->print(R"rawliteral(</div></main></div>)rawliteral");
        response->print(R"rawliteral(<footer><center><p>&copy; 2023 Weidmuller S.A. All rights reserved.</p></center></footer></body></html>)rawliteral");
}


char* generalStyle = "";
char* deviceFormStyle = R"rawliteral(<style>
        .hidden{
            display: none;
        }
    </style>)rawliteral";

char* headEnd = "</head>";
char* bodyBegin = "<body>";
char* bodyEnd = "</body>";
// char* footer = R"rawliteral(<footer>
//       <p style="text-align: center;">&copy; 2023 Weidmuller S.A. All rights reserved.</p>
//       </footer>)rawliteral";

char* footer = "";

// <form action="/deviceForm?slot=23" method="post" id="deviceForm">

char* deviceFormContent = R"rawliteral(<h1>Device Form</h1>

    <form method="post" id="deviceForm">
        
        <div class="userInput2">
            <label for="device">Select a Device:</label>
            <select name="device" id="deviceSelect"  onchange="showDeviceFields()">
                <option value="0">Select a device...</option>
                <option value="1">EM110</option>
                <option value="2">EM111</option>
                <option value="3">EM120</option>
                <option value="4">EM122</option>
                <option value="5">EM220</option>
                <option value="6">EM750</option>
                <option value="7">EA750</option>
                <option value="8">EM120-TCP</option>
                <option value="9">EM122-TCP</option>
                <option value="10">EM220-TCP</option>
                <option value="11">Pulse Meter</option>
                <option value="12">Analog Meter</option>
                <option value="13">Weidos ESP32</option>
            </select>
        </div>

        <div class="userInput" id="scopeId">
            <label for="scopeId">Scope ID:</label>
            <input type="text" name="scopeId" id="scopeIdInput" value="%s">
        </div>

        <div class="userInput" id="azureId">
            <label for="azureId">Azure ID:</label>
            <input type="text" name="azureId" id="azureIdInput" value="%s">
        </div>

        <div class="userInput" id="azureSasKey">
            <label for="azureSasKey">Azure SAS Key:</label>
            <input type="text" name="azureSasKey" id="azureSasKeyInput" value="%s">
        </div>

        <div class="userInput" id="ipAddress">
            <label for="ipAddress">IP Address:</label>
            <input type="text" name="ipAddress" id="ipAddressInput" value="%s">
        </div>

        <div class="userInput" id="modbusAddress">
            <label for="modbusAddress">Modbus Address:</label>
            <input type="number" name="modbusAddress" id="modbusAddressInput" value="%i">
        </div>
  
        <div class="userInput" id="ctPrimary" >
            <label for="ctPrimary">CT Primary:</label>
            <input type="text" name="ctPrimary" id="ctPrimaryInput" value="%i">
        </div>

        <div class="userInput" id="ctSecondary">
            <label for="ctSecondary">CT Secondary:</label>
            <input type="text" name="ctSecondary" id="ctSecondaryInput" value="%i">
        </div>

        <div class="userInput" id="digitalPin">
            <label for="digitalPin">Digital Pin:</label>
            <select name="digitalPin" id="digitalPinInput">
                <option value="0"></option>
                <option value="1">DI_4</option>
                <option value="2">DI_5</option>
                <option value="3">DI_6</option>
                <option value="4">DI_7</option>
            </select>
        </div>

        <div class="userInput" id="analogPin">
            <label for="analogPin">Analog Pin:</label>
            <select name="analogPin" id="analogPinInput">
                <option value="0"></option>
                <option value="1">ADI_0</option>
                <option value="2">ADI_1</option>
                <option value="3">ADI_2</option>
                <option value="4">ADI_3</option>
            </select>
        </div>

        <div class="userInput" id="conversionFactor">
            <label for="conversionFactor">Conversion Factor:</label>
            <input type="number" name="conversionFactor" id="conversionFactorInput"  value="%f" required step="0.01">
        </div>

        <input type="submit" value="Submit">
        <a href="/devices"><button type="button">Cancel</button></a>

    </form>)rawliteral";





char* deviceFormScripts = R"rawliteral(<script>
        var selectedItemIs = 3;

        document.addEventListener("DOMContentLoaded", function() {
            // Your code to be executed when the DOM is ready
            var deviceSelect = document.getElementById("deviceSelect");
            deviceSelect.value = selectedItemIs;
            document.getElementById('deviceSelect').selectedIndex = %i;
            document.getElementById('digitalPinInput').selectedIndex = %i;
            document.getElementById('analogPinInput').selectedIndex = %i;

            var event = new Event("change");
            deviceSelect.dispatchEvent(event);
        });


    function showDeviceFields() {
        // Get the selected value
        var userInputs = document.querySelectorAll(".userInput");
        userInputs.forEach(input => {
            input.classList.add("hidden");
            var inputTag = document.getElementById(input.id+"Input");
            if(inputTag.hasAttribute('required')) inputTag.removeAttribute('required', '');
        });



        var selectedDevice = document.getElementById("deviceSelect").value;
        if(selectedDevice != "0"){
            showInput("scopeId");
            showInput("azureId");
            showInput("azureSasKey");
        }

        if(selectedDevice === "1" || selectedDevice === "2" || selectedDevice === "3" || selectedDevice === "4" || selectedDevice === "5"){
            showInput("modbusAddress");
        }

        if(selectedDevice === "6" || selectedDevice === "7" || selectedDevice === "8" || selectedDevice === "9" || selectedDevice === "10"){
            showInput("ipAddress");
            showInput("modbusAddress");
        }

        if(selectedDevice === "1" || selectedDevice === "4" || selectedDevice === "5"){
            showInput("ctPrimary");
            showInput("ctSecondary");
        }

        if(selectedDevice === "11"){
            showInput("digitalPin");
            showInput("conversionFactor");
        }

        if(selectedDevice === "12"){
            showInput("analogPin");
            showInput("conversionFactor");
        }
    }

    function showInput(id){
        var element = document.getElementById(id);
        element.classList.remove('hidden');
        element = document.getElementById(id+"Input");
        // element = document.getElementsByName(id);
        console.log(id+"input");
        element.setAttribute('required', '');
    }
</script>)rawliteral";




void sendDeviceFormPage(AsyncResponseStream *response, int slot){
    char* scopeId = "";
    char* azureId = "";
    char* azureSasKey = "";
    IPAddress ipAddress = IPAddress(255, 255, 255, 255);
    char*  ip = "255.255.255.255";
    int modbusAddress = slot;
    int ctPrimary = 0;
    int ctSecondary = 0;
    float conversionFactor = 5.0;
    uint8_t deviceType = 0;
    int digitalPin = 0;
    int analogPin = 0;


    if(PersistentDataModule.isScopeIdSet()) scopeId = AzureIoTCollection.getScopeId();
    if(PersistentDataModule.isAzureIdSet(slot)) azureId = AzureIoTCollection.getAzureId(slot);
    if(PersistentDataModule.isSasKeySet(slot)) azureSasKey = AzureIoTCollection.getSasKey(slot);
    

    String ipString = "";
    if(PersistentDataModule.isModbusAddressSet(slot)) modbusAddress = PersistentDataModule.getModbusAddress(slot);
    if(PersistentDataModule.isCTPrimarySet(slot)) ctPrimary = PersistentDataModule.getCTPrimary(slot);
    if(PersistentDataModule.isCTSecondarySet(slot)) ctSecondary = PersistentDataModule.getCTSecondary(slot);
    if(PersistentDataModule.isDigitalPinSet(slot)) digitalPin = PersistentDataModule.getDigitalPin(slot);
    if(PersistentDataModule.isAnalogPinSet(slot)) analogPin = PersistentDataModule.getAnalogPin(slot);
    if(PersistentDataModule.isConversionSet(slot)) conversionFactor = PersistentDataModule.getConversionFactor(slot);
    if(PersistentDataModule.isDeviceTypeSet(slot)) deviceType = DeviceCollection.getDeviceType(slot);
    if(PersistentDataModule.isIpAddressSet(slot)){
        Serial.println("IP Address is set!");
        ipAddress = PersistentDataModule.getIpAddress(slot);
        ipString = String(ipAddress[0]) + "." + String(ipAddress[1]) + "." + String(ipAddress[2]) + "." + String(ipAddress[3]);
    }
    Serial.print("IP String is: ");
    Serial.println(ipString);
    

    Serial.print("Device Type: ");
    Serial.println(deviceType);
    // if(DeviceCollection.isEnergyMeter(slot))


    response->print(documentBegin);
    writeTitle(response, "Device Form");
    response->print(generalStyle);
    response->print(deviceFormStyle);
    response->print(headEnd);
    response->print(bodyBegin);
    response->printf(deviceFormContent, scopeId, azureId, azureSasKey, ipString.c_str(), modbusAddress, ctPrimary, ctSecondary, conversionFactor);
    response->print(footer);
    response->print(bodyEnd);

    
    response->printf(deviceFormScripts, deviceType, digitalPin, analogPin);
    response->print(documentEnd);

    return;
}
