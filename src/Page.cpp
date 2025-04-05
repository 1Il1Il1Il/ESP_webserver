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
    .box h2, .box h3 {
        margin-top: 0;
        color: #333;
    }
    input[type="text"], input[type="number"], input[type="color"], input[type="range"] {
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
    th, td {
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
    .color-cell input[type="checkbox"] {
        margin-bottom: 5px;
    }
    .color-cell button {
        padding: 5px 10px;
        background-color: #4CAF50;
        color: white;
        border: none;
        cursor: pointer;
        border-radius: 4px;
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
        setTimeout(sendNext, 1000); // Задержка 1 секунда
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
    function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("logContent").innerHTML = this.responseText;
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
    function sendButton(buttonId) {
        send("|button|" + buttonId);
    }
    function sendInput(inputId, inputType) {
        var input = document.getElementById(inputId);
        var value = input.value;
        if (inputType === 'color') {
            value = value.replace('#', ''); // Удаляем # из значения цвета
        }
        send("|input-" + inputType + "|" + inputId + "|" + value);
    }
</script>
</head>
<body>
    <div class="container">
        <div class="box">
            <h3>CURRENT IP ADDRESS : <div class="obj2">192.168.10.10</div></h3>
        </div>
        <div class="box">
            <h2>Real time :</h2>
            <h3>Change NTP: <input type="text" id="ntpServer"> <button onclick="sendInput('ntpServer', 'text')">Send</button></h3>
            <div class="button-row">
                <button onclick="sendButton('checkNTP')">Check NTP</button>
                <button onclick="sendButton('Settime')">Set time</button>
            </div>
            <h3>Period Check Time (seconds): <input type="number" id="periodTime" value="60" onchange="sendInput('periodTime', 'number')"></h3>
        </div>
        <div class="box">
            <h2>Sensors</h2>
            <div class="button-row">
                <button onclick="sendButton('checkSensors')">Check Sensors</button>
            </div>
        </div>
        <div class="box">
            <h2>Color</h2>
            <h3>BRIGHTNASS <input class="obj2" type="range" min="0" max="100" step="1" value="100" id="brightnessRange" onchange="sendInput('brightnessRange', 'range')"></h3>
            <table>
                <tbody>
                    <tr>
                        <td><b>Static</b></td>
                        <td><input type="checkbox" id="staticCheckbox" onchange="sendCheckbox('staticCheckbox', 1)"></td>
                        <td></td>
                        <td></td>
                        <td><input type="color" id="staticColor" onchange="sendInput('staticColor', 'color')"></td>
                    </tr>
                    <tr>
                        <td><b>Spectrum</b></td>
                        <td><input type="checkbox" id="spectrumCheckbox" onchange="sendCheckbox('spectrumCheckbox', 1)"></td>
                        <td></td>
                        <td><b>speed</b> <input type="number" id="spectrumSpeed" onchange="sendInput('spectrumSpeed', 'number')"></td>
                        <td></td>
                    </tr>
                    <tr>
                        <td><b>Gradient</b></td>
                        <td><input type="checkbox" id="gradientCheckbox" onchange="sendCheckbox('gradientCheckbox', 1)"></td>
                        <td><b>shift</b> <input type="number" id="gradientShift" onchange="sendInput('gradientShift', 'number')"></td>
                        <td><b>size</b> <input type="number" id="gradientSize" onchange="sendInput('gradientSize', 'number')"></td>
                        <td></td>
                    </tr>
                    <tr>
                        <td><b>Period</b></td>
                        <td><input type="checkbox" id="periodCheckbox" onchange="sendCheckbox('periodCheckbox', 1)"></td>
                        <td></td>
                        <td><b>period, hour</b> <input type="number" id="periodHour" onchange="sendInput('periodHour', 'number')"></td>
                        <td></td>
                    </tr>
                </tbody>
            </table>
            <table>
                <tbody>
                    <tr>
                        <td class="color-cell" style="background-color: #FF0000;"><input type="checkbox" id="colorCell1" onchange="sendCheckbox('colorCell1', 1)"><br><button onclick="sendButton('showColorCell1')">Show</button></td>
                        <td class="color-cell" style="background-color: #00FF00;"><input type="checkbox" id="colorCell2" onchange="sendCheckbox('colorCell2', 1)"><br><button onclick="sendButton('showColorCell2')">Show</button></td>
                        <td class="color-cell" style="background-color: #0000FF;"><input type="checkbox" id="colorCell3" onchange="sendCheckbox('colorCell3', 1)"><br><button onclick="sendButton('showColorCell3')">Show</button></td>
                        <td class="color-cell" style="background-color: #FFFF00;"><input type="checkbox" id="colorCell4" onchange="sendCheckbox('colorCell4', 1)"><br><button onclick="sendButton('showColorCell4')">Show</button></td>
                        <td class="color-cell" style="background-color: #00FFFF;"><input type="checkbox" id="colorCell5" onchange="sendCheckbox('colorCell5', 1)"><br><button onclick="sendButton('showColorCell5')">Show</button></td>
                        <td class="color-cell" style="background-color: #FF00FF;"><input type="checkbox" id="colorCell6" onchange="sendCheckbox('colorCell6', 1)"><br><button onclick="sendButton('showColorCell6')">Show</button></td>
                    </tr>
                    <tr>
                        <td class="color-cell" style="background-color: #800000;"><input type="checkbox" id="colorCell7" onchange="sendCheckbox('colorCell7', 1)"><br><button onclick="sendButton('showColorCell7')">Show</button></td>
                        <td class="color-cell" style="background-color: #008000;"><input type="checkbox" id="colorCell8" onchange="sendCheckbox('colorCell8', 1)"><br><button onclick="sendButton('showColorCell8')">Show</button></td>
                        <td class="color-cell" style="background-color: #000080;"><input type="checkbox" id="colorCell9" onchange="sendCheckbox('colorCell9', 1)"><br><button onclick="sendButton('showColorCell9')">Show</button></td>
                        <td class="color-cell" style="background-color: #808000;"><input type="checkbox" id="colorCell10" onchange="sendCheckbox('colorCell10', 1)"><br><button onclick="sendButton('showColorCell10')">Show</button></td>
                        <td class="color-cell" style="background-color: #008080;"><input type="checkbox" id="colorCell11" onchange="sendCheckbox('colorCell11', 1)"><br><button onclick="sendButton('showColorCell11')">Show</button></td>
                        <td class="color-cell" style="background-color: #800080;"><input type="checkbox" id="colorCell12" onchange="sendCheckbox('colorCell12', 1)"><br><button onclick="sendButton('showColorCell12')">Show</button></td>
                    </tr>
                </tbody>
            </table>
            <h3>Lava Mode: <input type="checkbox" id="lavaMode" onchange="sendCheckbox('lavaMode', 1)"> Intensity: <input type="number" id="lavaIntensity" onchange="sendInput('lavaIntensity', 'number')" value="50"></h3>
            <h3>C° Separate Color: <input type="checkbox" id="celsiusColorCheckbox" onchange="sendCheckbox('celsiusColorCheckbox', 1)"> <input type="color" id="celsiusColor" onchange="sendInput('celsiusColor', 'color')"></h3>
            <h3>% Separate Color: <input type="checkbox" id="percentageColorCheckbox" onchange="sendCheckbox('percentageColorCheckbox', 1)"> <input type="color" id="percentageColor" onchange="sendInput('percentageColor', 'color')"></h3>
            <button class="reset" onclick="sendButton('reset')"><h4>RESET</h4></button>
        </div>
    </div>
</body>
</html>
)rawliteral";