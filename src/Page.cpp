#include "header.h"
const String WebPage = R"rawliteral(

<!DOCTYPE html>
<html>

<head>
    <title>config</title>
    <style>
        body {
            font-family: sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 20px;
            color: #333;
            line-height: 1.6;
        }

        .container {
            max-width: 1100px;
            margin: auto;
            overflow: hidden;
        }

        .box {
            background-color: #fff;
            padding: 20px;
            margin-bottom: 20px;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
        }

        .box h2,
        .box h3 {
            margin-top: 0;
            color: #333;
        }

        input[type="text"],
        input[type="number"],
        input[type="color"],
        input[type="range"] {
            width: 100%;
            padding: 10px;
            margin: 5px 0 15px 0;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }

        button {
            background-color: #008CBA;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }

        button:hover {
            background-color: #0077A3;
        }

        .button-row {
            margin-top: 10px;
        }

        .button-row button {
            margin-bottom: 5px;
            padding: 8px 15px;
            background-color: #008CBA;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 4px;
        }

        .button-row button:hover {
            background-color: #0077A3;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 20px;
        }

        th,
        td {
            border: 1px solid #ddd;
            padding: 10px;
            text-align: left;
        }

        th {
            background-color: #f2f2f2;
            font-weight: bold;
        }

        .color-cell {
            width: 80px;
            height: 50px;
            text-align: center;
            vertical-align: middle;
        }

        .color-cell button {
            padding: 5px 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 4px;
            margin: 2px;
        }

        .color-cell button:hover {
            background-color: #45a049;
        }

        input[type="color"] {
            padding: 0;
            border: none;
            background: none;
        }
    </style>
    <script>
        var sendQueue = [];
        var isSending = false;
        function send(str) {
            sendQueue.push(str);
            if (!isSending) {
                sendNext();
            }
        }
        function sendNext() {
            if (sendQueue.length === 0) {
                isSending = false;
                return;
            }
            isSending = true;
            var str = sendQueue.shift();
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("str").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "send?str=" + str, true);
            xhttp.send();
            setTimeout(sendNext, 1000);
        }
        setInterval(function () {
            getData();
        }, 2000);
        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("state").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "adcread", true);
            xhttp.send();
        }
        function sendCheckbox(checkboxId, flag) {
            var checkbox = document.getElementById(checkboxId);
            if (checkbox.checked) {
                send("|checkbox|" + checkboxId + "|" + flag);
            } else {
                send("|checkbox|" + checkboxId + "|0");
            }
        }
        function sendCheckbox2(checkboxId, flag) {
            send("|checkbox|" + checkboxId + "|" + flag);
        }
        function sendButton(buttonId) {
            send("|button|" + buttonId);
        }
        function sendInput(inputId, inputType) {
            var input = document.getElementById(inputId);
            var value = input.value;
            if (inputType === 'color') {
                value = value.replace('#', '');
            }
            send("|input-" + inputType + "|" + inputId + "|" + value);
        }
        function toggleMode(checkboxId) {
            var checkboxes = ['staticCheckbox', 'spectrumCheckbox', 'gradientCheckbox', 'periodCheckbox'];
            checkboxes.forEach(function (id) {
                if (id !== checkboxId) {
                    document.getElementById(id).checked = false;
                    sendCheckbox(id, 0);
                }
            });
            sendCheckbox(checkboxId, 1);
        }
        function uncheckOthers(checkedId) {
            var checkboxes = document.querySelectorAll('input[class="modes"]');
            checkboxes.forEach(function (checkbox) {
                if (checkbox.id !== checkedId && checkbox.checked) {
                    checkbox.checked = false;
                }
            });
        }

        // Функции для работы с IP-адресом и ссылками
        function getHost() {
            return window.location.host;
        }
        function updateHost() {
            var host = getHost(); // Предполагается, что getHost() возвращает IP-адрес, например, "192.168.1.100"
            document.getElementById("resetLink").href = "http://" + host + "/send?str=|button|reset";
            document.getElementById("resetLink").innerText = "http://" + host + "/send?str=|button|reset";
            document.getElementById("resetWifiLink").href = "http://" + host + "/send?str=|button|resetwifi";
            document.getElementById("resetWifiLink").innerText = "http://" + host + "/send?str=|button|resetwifi";
            document.getElementById("resetMemoryLink").href = "http://" + host + "/send?str=|button|resetmemory";
            document.getElementById("resetMemoryLink").innerText = "http://" + host + "/send?str=|button|resetmemory";
        }
        window.onload = updateHost;
    </script>
</head>

<body>
    <div class="container">
        <div class="box">
            <h3>CURRENT IP ADDRESS: <span id="currentIp"></span></h3>
        </div>
        <div class="box">
            <h2>Real time:</h2>
            <h3>Change NTP: (for example "pool.ntp.org") <input type="text" id="ntpServer"> <button
                    onclick="sendInput('ntpServer', 'text')">Send</button></h3>
        </div>
        <div class="box">
            <h2>Color</h2>
            <h3>BRIGHTNESS <input class="obj2" type="range" min="0" max="100" step="1" value="100" id="brightnessRange"
                    onchange="sendInput('brightnessRange', 'range')"></h3>
            <table>
                <tbody>
                    <tr>
                        <td><b>Static</b></td>
                        <td><input type="checkbox" class="modes" id="staticCheckbox"
                                onclick="uncheckOthers('staticCheckbox')" onchange="toggleMode('staticCheckbox')"></td>
                        <td></td>
                        <td><b>Color</b><input type="color" id="staticColor"
                                onchange="sendInput('staticColor', 'color')"></td>
                        <td></td>
                    </tr>
                    <tr>
                        <td><b>Spectrum</b></td>
                        <td><input type="checkbox" class="modes" id="spectrumCheckbox"
                                onclick="uncheckOthers('spectrumCheckbox')" onchange="toggleMode('spectrumCheckbox')">
                        </td>
                        <td></td>
                        <td><b>speed, %</b> <input type="number" id="spectrumSpeed"
                                onchange="sendInput('spectrumSpeed', 'number')"></td>
                        <td></td>
                    </tr>
                    <tr>
                        <td><b>Gradient</b></td>
                        <td><input type="checkbox" class="modes" id="gradientCheckbox"
                                onclick="uncheckOthers('gradientCheckbox')" onchange="toggleMode('gradientCheckbox')">
                        </td>
                        <td><b>x, %</b> <input type="range" id="gradientShift"
                                onchange="sendInput('gradientShift', 'range')"></td>
                        <td><b>y, %</b> <input type="range" id="gradientSize"
                                onchange="sendInput('gradientSize', 'range')"></td>
                        <td></td>
                    </tr>
                    <tr>
                        <td><b>Period</b></td>
                        <td><input type="checkbox" class="modes" id="periodCheckbox"
                                onclick="uncheckOthers('periodCheckbox')" onchange="toggleMode('periodCheckbox')"></td>
                        <td></td>
                        <td><b>period, hour</b> <input type="number" id="periodHour"
                                onchange="sendInput('periodHour', 'number')"></td>
                        <td></td>
                    </tr>
                </tbody>
            </table>
            <table>
                <tbody>
                    <tr>
                        <td class="color-cell" style="background-color: rgb(255, 0, 0);">
                            <button onclick="sendCheckbox2('colorCell1', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell1', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(255, 0, 125);">
                            <button onclick="sendCheckbox2('colorCell2', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell2', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(255, 0, 255);">
                            <button onclick="sendCheckbox2('colorCell3', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell3', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(75, 20, 255);">
                            <button onclick="sendCheckbox2('colorCell4', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell4', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(30, 99, 255);">
                            <button onclick="sendCheckbox2('colorCell5', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell5', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(0, 255, 255);">
                            <button onclick="sendCheckbox2('colorCell6', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell6', 0)">dis</button><br>
                        </td>
                    </tr>
                    <tr>
                        <td class="color-cell" style="background-color: rgb(0, 255, 125);">
                            <button onclick="sendCheckbox2('colorCell7', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell7', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(0, 255, 0);">
                            <button onclick="sendCheckbox2('colorCell8', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell8', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(125, 255, 0);">
                            <button onclick="sendCheckbox2('colorCell9', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell9', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(255, 255, 0);">
                            <button onclick="sendCheckbox2('colorCell10', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell10', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(255, 125, 0);">
                            <button onclick="sendCheckbox2('colorCell11', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell11', 0)">dis</button><br>
                        </td>
                        <td class="color-cell" style="background-color: rgb(255, 75, 0);">
                            <button onclick="sendCheckbox2('colorCell12', 1)">en</button>
                            <button onclick="sendCheckbox2('colorCell12', 0)">dis</button><br>
                        </td>
                    </tr>
                </tbody>
            </table>
            <h3>C° Separate Color:
                <button onclick="sendCheckbox2('celsiusColorCheckbox', 1)">en</button>
                <button onclick="sendCheckbox2('celsiusColorCheckbox', 0)">dis</button><br>
                <input type="color" id="celsiusColor" onchange="sendInput('celsiusColor', 'color')">
            </h3>
            <h3>% Separate Color:
                <button onclick="sendCheckbox2('percentageColorCheckbox', 1)">en</button>
                <button onclick="sendCheckbox2('percentageColorCheckbox', 0)">dis</button><br>
                <input type="color" id="percentageColor" onchange="sendInput('percentageColor', 'color')">
            </h3>
            <h3>Blink Points:
                <button onclick="sendCheckbox2('blinkPointCheckbox', 1)">en</button>
                <button onclick="sendCheckbox2('blinkPointCheckbox', 0)">dis</button>
            </h3>
            
            <h4>Reset Board: <a id="resetLink" href="#"></a></h4>
            <h4>Clear WiFi Data: <a id="resetWifiLink" href="#"></a></h4>
            <h4>Reset All Memory: <a id="resetMemoryLink" href="#"></a></h4>
        </div>
    </div>
</body>

</html>

)rawliteral";