#include "devicesPage.h"



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
      background-color: #3498db;
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

        char* namesTest[] = {"EM111", "EM220", "+", "EM750", "Pulse Meter"};
        for(int i=0; i<5; i++){
            response->print(R"rawliteral(<div class="slot"><h3 class="topleft" >Slot )rawliteral");
            response->print(i);
            response->print(R"rawliteral(:</h3><a class="deviceButton" href="/deviceForm?slot=)rawliteral");
            response->print(i);
            response->print("\">");
            response->print(namesTest[i]);
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
char* footer = R"rawliteral(<footer>
      <p style="text-align: center;">&copy; 2023 Weidmuller S.A. All rights reserved.</p>
      </footer>)rawliteral";

// <form action="/deviceForm?slot=23" method="post" id="deviceForm">

char* deviceFormContent = R"rawliteral(<h1>Device Form</h1>

    <form method="post" id="deviceForm">
        
        <div class="userInput2">
            <label for="device">Select a Device:</label>
            <select name="device" id="deviceSelect"  onchange="showDeviceFields()">
                <option value="0">Select a device...</option>
                <option value="1" selected>EM110</option>
                <option value="2">EM111</option>
                <option value="3">EM120</option>
                <option value="4">EM122</option>
                <option value="5">EM750</option>
                <option value="6">EA750</option>
                <option value="7">Pulse Meter</option>
                <option value="8">Analog Meter</option>
            </select>
        </div>



        <div class="userInput" id="azureId">
            <label for="azureId">Azure ID:</label>
            <input type="text" name="azureId" id="azureIdInput">
        </div>



        <div class="userInput" id="azureSasKey">
            <label for="azureSasKey">Azure SAS Key:</label>
            <input type="text" name="azureSasKey" id="azureSasKeyInput">
        </div>


        <div class="userInput" id="ipAddress">
            <label for="ipAddress">IP Address:</label>
            <input type="text" name="ipAddress" id="ipAddressInput">
        </div>



        <div class="userInput" id="modbusAddress">
            <label for="modbusAddress">Modbus Address:</label>
            <input type="number" name="modbusAddress"  id="modbusAddressInput" value="1" readonly>
        </div>
  

        <div class="userInput" id="cpPrimary" >
            <label for="cpPrimary">CP Primary:</label>
            <input type="text" name="cpPrimary" id="cpPrimaryInput">
        </div>


        <div class="userInput" id="cpSecondary">
            <label for="cpSecondary">CP Secondary:</label>
            <input type="text" name="cpSecondary" id="cpSecondaryInput">
        </div>


        <div class="userInput" id="digitalPin">    
            <label for="digitalPin">Digital Pin:</label>
            <select name="digitalPin" id="digitalPinInput">
                <option value=""></option>
                <option value="DI_4">DI_4</option>
                <option value="DI_5">DI_5</option>
                <option value="DI_6">DI_6</option>
                <option value="DI_7">DI_7</option>
            </select>
        </div>
  

        <div class="userInput" id="conversionFactor">
            <label for="conversionFactor">Conversion Factor:</label>
            <input type="number" name="conversionFactor" id="conversionFactorInput"  required step="0.01">
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
            console.log("On load Body!");
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
        if(selectedDevice != ""){
            showInput("azureId");
            showInput("azureSasKey");
        }
        if(selectedDevice === "1" || selectedDevice === "2" || selectedDevice === "3" || selectedDevice === "4"){
            showInput("modbusAddress");
        } 

        if(selectedDevice === "5" || selectedDevice === "6"){
            showInput("ipAddress");
            showInput("modbusAddress");
        }

        if(selectedDevice === "7" || selectedDevice === "8"){
            showInput("digitalPin");
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




void sendDeviceFormPage(AsyncResponseStream *response){
    response->print(documentBegin);
    writeTitle(response, "Device Form");
    response->print(generalStyle);
    response->print(deviceFormStyle);
    response->print(headEnd);
    response->print(bodyBegin);
    response->print(deviceFormContent);
    response->print(footer);
    response->print(bodyEnd);
    response->print(deviceFormScripts);
    response->print(documentEnd);
}
