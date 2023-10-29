const char main_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

    <head>
        <title>Sensor Node Dashboard</title>
        <style>
            body {
                background-color: #daf8e3;
                font-family: sans-serif;
                color: #0086ad;
                text-align: center;
                margin: 0 auto;
            }

            table {
                width: 800px;
                border-collapse: collapse;
                border-radius: 25px;
                box-shadow: 2px 2px 10px 0 rgba(0, 0, 0, 0.25);
                margin: 0 auto;

            }

            th,
            td {
                border-width: 1px;
                border-style: solid;
                padding: 10px;
                text-align: center;
            }

            .header_bottom {
                border-bottom-width: 2px;
            }

            .top {
                border-top: none;
            }

            .left {
                border-left: none;
            }

            .right {
                border-right: none;
            }

            .bottom {
                border-bottom: none;
            }

            .ml1 {
                margin-left: 10px;
            }

            .ml2 {
                margin-left: 20px;
            }

            .ml3 {
                margin-left: 30px;
            }

            .ml4 {
                margin-left: 40px;
            }

            .ml5 {
                margin-left: 50px;
            }

            .connection-table {
                color: #0086ad;
                background-color: none;
            }

            .sensor-table {
                margin-top: 20px;
                color: #0086ad;
                background-color: none;
            }

            .earthquake-table {
                margin-top: 20px;
                color: #fff;
                background-color: #FFAF42;
            }

            button {
                color: #ffffff;
                background-color: #FFAF42;
                border-radius: 20px;
                border: none;
                box-shadow: 0 5px 5px 0 rgba(0, 0, 0, 0.2);
                margin-top: 40px;
                font-size: 20px;
                font-weight: bolder;
                padding: 20px 40px;

            }

        </style>
    </head>

    <body onload="getConnectionData()">
        <h1>Earthquake Monitoring Dashboard</h1>
        <h2>Connection:<span class="ml3" id="date">mm/dd/yyyy</span><span class="ml3" id="time">00:00:00</span></h2>

        <table class="connection-table">
            <thead>
                <tr>
                    <th class="top left header_bottom">WIFI</th>
                    <th class="header_bottom top">Sensor Node</th>
                    <th class="header_bottom top right">Alarm Node</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td class="left">Node Hostname</td>
                    <td id="sensorNodeHostname"></td>
                    <td class="right" id="alarmNodeHostname"></td>
                </tr>
                <tr>
                    <td class="left">Node Local IP</td>
                    <td id="sensorNodeLocalIP"></td>
                    <td class="right" id="alarmNodeLocalIP"></td>

                </tr>
                <tr>
                    <td class="left bottom">Node WiFi Signal Strength</td>
                    <td class="bottom" id="sensorNodeSignalStrength"></td>
                    <td class="right bottom" id="alarmNodeWiFiSignalStrength"></td>
                </tr>
            </tbody>
        </table>

        <table class="sensor-table">
            <thead>
                <tr>
                    <th class="header_bottom left top">Sensor</th>
                    <th class="header_bottom top">Accelerometer</th>
                    <th class="header_bottom top">Gyroscope</th>
                    <th class="header_bottom top">Magnetometer</th>
                    <th class="header_bottom top right">Temperature</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td class="left">X</td>
                    <td id="sensorAccelX"></td>
                    <td id="sensorGyroX"></td>
                    <td id="sensorMagX"></td>
                    <td class="right bottom" id="sensorTemp" rowspan="3"></td>
                </tr>
                <tr>
                    <td class="left">Y</td>
                    <td id="sensorAccelY"></td>
                    <td id="sensorGyroY"></td>
                    <td id="sensorMagY"></td>
                </tr>
                <tr>
                    <td class="left bottom">Z</td>
                    <td class="bottom" id="sensorAccelZ"></td>
                    <td class="bottom" id="sensorGyroZ"></td>
                    <td class="bottom" id="sensorMagZ"></td>
                </tr>
            </tbody>
        </table>

        <table class="earthquake-table">
            <thead>
                <tr>
                    <th class="header_bottom top left">Earthquake</th>
                    <th class="header_bottom top right">Value</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td class="left">Magnitude</td>
                    <td class="right" id="earthquakeMagnitude"></td>
                </tr>
                <tr>
                    <td class="left bottom">Level</td>
                    <td class="right bottom" id="earthquakeLevel"></td>
                </tr>
            </tbody>
        </table>
        <button type="button" id="btnMuteAlarm" onclick="btnMute()">Mute Alarm</button>
    </body>

    <script type="text/javascript">
        setInterval(function () {
            updateData();
            var dateTime = getCurrentDateTime();
            document.getElementById("time").innerHTML = dateTime.time;
            document.getElementById("date").innerHTML = dateTime.date;
        }, 500);

        function getCurrentDateTime() {
            var date = new Date();
            var time = date.toLocaleTimeString();
            var dateString = date.toLocaleDateString();
            return {
                time: time,
                date: dateString
            };
        }

        function btnMute() {
            var xhttp = new XMLHttpRequest();
            xhttp.open("PUT", "btnMute", false);
            xhttp.send();
        }

        function getConnectionData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var xmlDoc = xhttp.responseXML;
                    var sensorNode = xmlDoc.querySelector("Sensor");
                    var alarmNode = xmlDoc.querySelector("Alarm");
                    // --------------------------------------------------- WIFI
                    var wifiNode = sensorNode.querySelector("Wifi");
                    var hostname = wifiNode.querySelector("Hostname").textContent;
                    var localIP = wifiNode.querySelector("Local_IP").textContent;
                    var signalStrength = wifiNode.querySelector("Signal_Strength").textContent;
                    document.getElementById('sensorNodeHostname').innerHTML = hostname;
                    document.getElementById('sensorNodeLocalIP').innerHTML = localIP;
                    document.getElementById('sensorNodeSignalStrength').innerHTML = signalStrength;

                    wifiNode = alarmNode.querySelector("Wifi");
                    hostname = wifiNode.querySelector("Hostname").textContent;
                    localIP = wifiNode.querySelector("Local_IP").textContent;
                    signalStrength = wifiNode.querySelector("Signal_Strength").textContent;
                    document.getElementById('alarmNodeHostname').innerHTML = hostname;
                    document.getElementById('alarmNodeLocalIP').innerHTML = localIP;
                    document.getElementById('alarmNodeWiFiSignalStrength').innerHTML = signalStrength;
                }
            };
            xhttp.open("GET", "connectionXML", true);
            xhttp.send();
        }

        function updateData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var xmlDoc = xhttp.responseXML;
                    var sensorNode = xmlDoc.querySelector("Sensor");
                    var alarmNode = xmlDoc.querySelector("Alarm");
                    var earthquakeNode = xmlDoc.querySelector("Earthquake");

                    // --------------------------------------------------- Earthquake
                    var earthquakeMagnitude = earthquakeNode.querySelector("Magnitude").textContent;
                    var earthquakeLevel = earthquakeNode.querySelector("Level").textContent;
                    document.getElementById('earthquakeMagnitude').innerHTML = earthquakeMagnitude;
                    document.getElementById('earthquakeLevel').innerHTML = earthquakeLevel;

                    // --------------------------------------------------- Accelerometer
                    var accelNode = sensorNode.querySelector("Accelerator");
                    var x = accelNode.querySelector("X").textContent;
                    var y = accelNode.querySelector("Y").textContent;
                    var z = accelNode.querySelector("Z").textContent;
                    document.getElementById('sensorAccelX').innerHTML = x;
                    document.getElementById('sensorAccelY').innerHTML = y;
                    document.getElementById('sensorAccelZ').innerHTML = z;
                    // --------------------------------------------------- Gyroscope
                    var gyroNode = sensorNode.querySelector("Gyroscope");
                    x = gyroNode.querySelector("X").textContent;
                    y = gyroNode.querySelector("Y").textContent;
                    z = gyroNode.querySelector("Z").textContent;
                    document.getElementById('sensorGyroX').innerHTML = x;
                    document.getElementById('sensorGyroY').innerHTML = y;
                    document.getElementById('sensorGyroZ').innerHTML = z;
                    // --------------------------------------------------- Magnetometer
                    var magNode = sensorNode.querySelector("Magnetometer");
                    x = magNode.querySelector("X").textContent;
                    y = magNode.querySelector("Y").textContent;
                    z = magNode.querySelector("Z").textContent;
                    document.getElementById('sensorMagX').innerHTML = x;
                    document.getElementById('sensorMagY').innerHTML = y;
                    document.getElementById('sensorMagZ').innerHTML = z;
                    // --------------------------------------------------- Temperature
                    var tempNode = sensorNode.querySelector("Temperature");
                    x = tempNode.querySelector("Celsius").textContent;
                    document.getElementById('sensorTemp').innerHTML = x;
                }
            };
            xhttp.open("GET", "sensorXML", true);
            xhttp.send();
        }
    </script>

</html>

)=====";