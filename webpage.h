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

            .navbar {
                width: 100%;
                height: 50px;
                margin: 0;
                padding: 10px 0px;
                background-color: #FFF;
                color: #5088DC;
                border-bottom: 5px solid #293578;
            }

            .navheading {
                position: fixed;
                left: 60%;
                height: 50px;
                font-size: 20px;
                font-weight: bold;
                line-height: 20px;
                padding-right: 20px;
            }

            .navtitle {
                float: left;
                height: 50px;
                font-size: 50px;
                font-weight: bold;
                line-height: 50px;
                padding-left: 20px;
            }

            .navdata {
                justify-content: flex-end;
                position: fixed;
                left: 70%;
                height: 50px;
                font-size: 20px;
                font-weight: bold;
                line-height: 20px;
                padding-right: 20px;
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
        <header>
            <div class="navbar fixed-top">
                <div class="container">
                    <div class="navtitle">Earthquake Monitoring Dashboard</div>
                    <div class="navdata" id="date">mm/dd/yyyy</div>
                    <div class="navheading">DATE</div><br>
                    <div class="navdata" id="time">00:00:00</div>
                    <div class="navheading">TIME</div>

                </div>
            </div>
        </header>
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
                    <td id="sensorNodeHostname"></td>
                </tr>
                <tr>
                    <td>Node Local IP</td>
                    <td id="sensorNodeLocalIP"></td>
                </tr>
                <tr>
                    <td>Node WiFi Signal Strength</td>
                    <td id="sensorNodeSignalStrength"></td>
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
                    <td id="sensorAccelX"></td>
                </tr>
                <tr>
                    <td>Y</td>
                    <td id="sensorAccelY"></td>
                </tr>
                <tr>
                    <td>Z</td>
                    <td id="sensorAccelZ"></td>
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
        <button type="button" id="btnMuteAlarm" onclick="ButtonPress0()">Mute Alarm</button>


    </body>

    <script type="text/javascript">

        // global variable visible to all java functions
        var xmlHttp = createXmlHttpObject();

        // function to create XML object
        function createXmlHttpObject() {
            if (window.XMLHttpRequest) {
                xmlHttp = new XMLHttpRequest();
            }
            else {
                xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
            }
            return xmlHttp;
        }

        function ButtonPress0() {
            var xhttp = new XMLHttpRequest();
            var value;

            xhttp.open("PUT", "BUTTON_0", false);
            xhttp.send();
        }

        // function to handle the response from the ESP
        function response() {
            var value;
            var xmlResponse;
            var xmldoc;
            var dt = new Date();

            // Set date and time
            document.getElementById("time").innerHTML = dt.toLocaleTimeString();
            document.getElementById("date").innerHTML = dt.toLocaleDateString();

            // Get xml object
            xmlResponse = xmlHttp.responseXML;

            // xmldoc = xmlResponse.getElementsByTagName("Sensor");
            xmldoc = xmlResponse.querySelector("Sensor > Wifi > Hostname");
            // value = xmldoc[0].firstChild.nodeValue;
            document.getElementById("sensorNodeHostname").innerHTML = xmldoc.textContent;
        }

        function process() {

            if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
                xmlHttp.open("PUT", "xml", true);
                xmlHttp.onreadystatechange = response;
                xmlHttp.send(null);
            }
            // you may have to play with this value, big pages need more porcessing time, and hence
            // a longer timeout
            setTimeout("process()", 100);
        }

    </script>
</html>

)=====";