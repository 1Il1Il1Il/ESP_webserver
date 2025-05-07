#include "header.h" // Assuming this contains necessary includes like <Arduino.h> or <WString.h>

String WebPage = R"rawliteral(
    
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
                        // Optionally update an element to show the server response or status
                        // document.getElementById("status").innerHTML = "Last command sent: " + str;
                        console.log("Server response:", this.responseText);
                    } else if (this.readyState == 4) {
                        console.error("Error sending command:", this.status, this.statusText);
                         // Optionally update status on error
                        // document.getElementById("status").innerHTML = "Error sending command: " + str;
                    }
                };
                xhttp.open("GET", "send?str=" + encodeURIComponent(str), true); // Encode the string for URL safety
                xhttp.send();
                // Consider adjusting the delay or making it adaptive based on response
                setTimeout(sendNext, 500); // Reduced delay slightly, adjust as needed
            }
            setInterval(function () {
                getData();
            }, 2000);
            function getData() {
                var xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function () {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("state").innerHTML = this.responseText; // Make sure you have an element with id="state" in your HTML if you use this
                    }
                };
                xhttp.open("GET", "adcread", true); // Assuming "adcread" is the correct endpoint
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
    
            // *** NEW FUNCTION TO SEND CURRENT TIME ***
            function sendCurrentTime() {
              var now = new Date();
              // Format as YYYY-MM-DDTHH:MM:SS (local time)
              var year = now.getFullYear();
              var month = ('0' + (now.getMonth() + 1)).slice(-2); // Add leading zero if needed
              var day = ('0' + now.getDate()).slice(-2);
              var hours = ('0' + now.getHours()).slice(-2);
              var minutes = ('0' + now.getMinutes()).slice(-2);
              var seconds = ('0' + now.getSeconds()).slice(-2);
              var timestamp = year + '-' + month + '-' + day + 'T' + hours + ':' + minutes + ':' + seconds;
    
              // Construct the message string for the server
              var message = '|settime| |' + timestamp;
              send(message); // Use the existing send function
              console.log("Sent time sync request: " + message);
              // Optional: Provide user feedback (e.g., change button text temporarily)
              // alert("Time sync request sent!");
            }
    
            function toggleMode(checkboxId) {
                var checkboxes = ['staticCheckbox', 'spectrumCheckbox', 'gradientCheckbox', 'periodCheckbox'];
                checkboxes.forEach(function (id) {
                    if (id !== checkboxId) {
                        document.getElementById(id).checked = false;
                        // Send the 'off' state for other checkboxes if needed by your logic
                        // sendCheckbox2(id, 0); // Uncomment if disabling others should send a command
                    }
                });
                // Send the 'on' state for the clicked checkbox
                sendCheckbox(checkboxId, 1); // Assuming sendCheckbox handles the checked state correctly
            }
    
            function uncheckOthers(checkedId) {
                 var checkboxes = document.querySelectorAll('input[class="modes"]');
                 checkboxes.forEach(function (checkbox) {
                     if (checkbox.id !== checkedId && checkbox.checked) {
                         checkbox.checked = false;
                         // No need to send command here, toggleMode handles sending
                     }
                 });
                 // The checkbox state change will trigger toggleMode via the onchange event
             }
    
            // Функции для работы с IP-адресом и ссылками
            function getHost() {
                return window.location.host;
            }
            function updateHost() {
                var host = getHost(); // Предполагается, что getHost() возвращает IP-адрес, например, "192.168.1.100"
                document.getElementById("resetLink").href = "http://" + host + "/send?str=|button|reset";
                document.getElementById("resetLink").innerText = "http://" + host + "/send?str=|button|reset";
                document.getElementById("resetMemoryLink").href = "http://" + host + "/send?str=|button|resetmemory";
                document.getElementById("resetMemoryLink").innerText = "http://" + host + "/send?str=|button|resetmemory";
            }
            window.onload = updateHost; // Keep this to update reset links
        </script>
    </head>
    
    <body>
        <div class="container">
            <div class="box">
                <h2>Real time:</h2>
                <h3>Set Real Time: <button onclick="sendCurrentTime()">Sync Time</button></h3>
                </div>
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
                 <h3>First Zero:
                    <button onclick="sendCheckbox2('firstzero', 1)">en</button>
                    <button onclick="sendCheckbox2('firstzero', 0)">dis</button>
                 </h3>
    
                <h4>Reset Board: <a id="resetLink" href="#"></a></h4>
                <h4>Reset All Memory: <a id="resetMemoryLink" href="#"></a></h4>
            </div>
        </div>
    </body>
    
    </html>
    
    )rawliteral";
    