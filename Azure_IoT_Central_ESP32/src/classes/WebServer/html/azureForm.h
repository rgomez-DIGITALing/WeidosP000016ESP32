#pragma once

const char* azureForm PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>WeidOS EM Gateway</title>
    <style>
        input {
            width:150px;
        }
    </style>
</head>
<body>
    <font face = "helvetica">
    <center>
        <div style = "background-color:#eb8c00; color:white; padding:20px">
            
            <h1 style="color:white; padding:0; margin:0;">WeidOS EM Gateway</h1>
            <form method="post" action="/azure">
                <label for="gwDeviceId">Gateway ID:</label>
                <input type="text" id="gwDeviceId" name="gwDeviceId" value="%gwDeviceId%" maxlength="100" required><br><br>
                <label for="gwkEY">Gateway SAS Key:</label>
                <input type="text" id="gwkEY" name="gwkEY" value="%gwKey%" maxlength="100" required><br><br>


                <label for="deviceId1">Device ID 1:</label>
                <input type="text" id="deviceId1" name="deviceId1" value="%deviceId1%" maxlength="100" required><br><br>
                <label for="deviceKey1">Device 1 SAS Key:</label>
                <input type="text" id="deviceKey1" name="deviceKey1" value="%deviceKey1%" maxlength="100" required><br><br>

                <label for="deviceId2">Device ID 2:</label>
                <input type="text" id="deviceId2" name="deviceId2" value="%deviceId2%" maxlength="100" required><br><br>
                <label for="deviceKey2">Device 2 SAS Key:</label>
                <input type="text" id="deviceKey2" name="deviceKey2" value="%deviceKey2%" maxlength="100" required><br><br>
                

                <label for="deviceId3">Device ID 3:</label>
                <input type="text" id="deviceId3" name="deviceId3" value="%deviceId3%" maxlength="100" required><br><br>
                <label for="deviceKey3">Device 3 SAS Key:</label>
                <input type="text" id="deviceKey3" name="deviceKey3" value="%deviceKey3%" maxlength="100" required><br><br>

                <label for="deviceId4">Device ID 4:</label>
                <input type="text" id="deviceId4" name="deviceId4" value="%deviceId4%" maxlength="100" required><br><br>
                <label for="deviceKey4">Device 4 SAS Key:</label>
                <input type="text" id="deviceKey4" name="deviceKey4" value="%deviceKey4%" maxlength="100" required><br><br>

                <label for="deviceId5">Device ID 5:</label>
                <input type="text" id="deviceId5" name="deviceId5" value="%deviceId5%" maxlength="100" required><br><br>
                <label for="deviceKey5">Device 5 SAS Key:</label>
                <input type="text" id="deviceKey5" name="deviceKey5" value="%deviceKey5%" maxlength="100" required><br><br>


                <label for="deviceName">Device Name:</label>
                <input type="text" id="deviceName" name="deviceName" value="%deviceName%" maxlength="20" required><br><br>

                <label for="scopeId">Scope ID:</label>
                <input type="text" id="scopeId" name="scopeId" value="%scopeId%" maxlength="20" required><br><br>

                <label for="primaryKey">Primary Key:</label>
                <input type="text" id="primaryKey" name="primaryKey" value="%primaryKey%" style="width:400px;" maxlength="64" required><br><br>

                <label for="weidosModelId">WeidOS-ESP32-Wifi Model ID:</label>
                <input type="text" id="weidosModelId" name="weidosModelId" value="%weidosModelId%" maxlength="100" required><br><br>

                <label for="em3BasicLineId">EM3Ph Basic Line Serial Model ID:</label>
                <input type="text" id="em3BasicLineId" name="em3BasicLineId" value="%em3BasicLineId%" maxlength="100" required><br><br>

                <label for="em1BasicLineId">EM1Ph Basic Line Serial Model ID:</label>
                <input type="text" id="em1BasicLineId" name="em1BasicLineId" value="%em1BasicLineId%" maxlength="100" required><br><br>

                <input type="submit" value="Submit" style = "width: auto;">
            </form>
        </div>
    </center>

    <footer>
        <center><p>&copy; 2023 Weidmuller S.A. All rights reserved.</p></center>
    </footer>
    </font>
</body>
</html>
)rawliteral";