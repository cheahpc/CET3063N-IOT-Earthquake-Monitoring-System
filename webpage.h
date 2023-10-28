const char main_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

    <head>
        <title>Sensor Node Dashboard</title>
        <style>
            body {
                background-color: #D5F2FE;
                font-family: sans-serif;
                color: #5088DC;
                text-align: center;
                margin: 0 auto;
            }

            table {
                width: 33%;
                border-collapse: collapse;
                border-radius: 20px;
                box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.2);
                margin: 0 auto;
            }

            th,
            td {
                color: #353535;
                border: none;
                padding: 5px;
                text-align: center;
            }

            .sensor-node {
                background-color: #a3f0ff;
            }

            .accelerometer {
                margin-top: 20px;
                background-color: #c6ffe6;
            }

            .alarm-node {
                background-color: #a3f0ff;
            }

            .earthquake {
                background-color: #ffc6c6;
            }

            button {
                background-color: #ff4400;
                color: #ffffff;
                border-radius: 20px;
                border: none;
                box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.2);
                margin-top: 40px;
                font-size: 20px;
                font-weight: bolder;
                padding: 20px;
            }

        </style>
    </head>

    <body>
        <h1>Earthquake Monitoring Dashboard</h1>
        <h2>Sensor Node</h2>
        <table class="sensor-node">
            <thead>
                <tr>
                    <th>WIFI</th>
                    <th>Value</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td>Node Hostname</td>
                    <td id="nodeHostname"></td>
                </tr>
                <tr>
                    <td>Node Local IP</td>
                    <td id="nodeLocalIP"></td>
                </tr>
                <tr>
                    <td>Node WiFi Signal Strength</td>
                    <td id="nodeWiFiSignalStrength"></td>
                </tr>
            </tbody>
        </table>

        <table class="accelerometer">
            <thead>
                <tr>
                    <th>Accelerometer</th>
                    <th>Value</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td>X</td>
                    <td id="accelerometerX"></td>
                </tr>
                <tr>
                    <td>Y</td>
                    <td id="accelerometerY"></td>
                </tr>
                <tr>
                    <td>Z</td>
                    <td id="accelerometerZ"></td>
                </tr>
            </tbody>
        </table>

        <h2>Alarm Node</h2>

        <table class="alarm-node">
            <thead>
                <tr>
                    <th>WIFI</th>
                    <th>Value</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td>Node Hostname</td>
                    <td id="alarmNodeHostname"></td>
                </tr>
                <tr>
                    <td>Node LocalIP</td>
                    <td id="alarmNodeLocalIP"></td>
                </tr>
                <tr>
                    <td>Node WiFi Signal Strength</td>
                    <td id="alarmNodeWiFiSignalStrength"></td>
                </tr>
            </tbody>
        </table>

        <h2>Earthquake</h2>

        <table class="earthquake">
            <thead>
                <tr>
                    <th>Item</th>
                    <th>Value</th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td>Magnitude</td>
                    <td id="earthquakeMagnitude"></td>
                </tr>
                <tr>
                    <td>Level</td>
                    <td id="earthquakeLevel"></td>
                </tr>
            </tbody>
        </table>

        <button id="snoozeAlarmButton">Snooze Alarm</button>

        <script>
            // Update the sensor node data every 1 second
            setInterval(updateSensorNodeData, 1000);

            // Snooze the alarm when the snooze alarm button is clicked
            document.getElementById("snoozeAlarmButton").addEventListener("click", function () {
                // TODO: Implement the snooze alarm functionality
            });

            function updateSensorNodeData() {
                // TODO: Implement the sensor node data update functionality
            }
        </script>
    </body>

</html>

)=====";