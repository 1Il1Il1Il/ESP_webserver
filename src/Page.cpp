#include "header.h"
const String WebPage = R"rawliteral(









<!DOCTYPE html>

<html>

<head>
    <title>config</title>

    <script>
        function send(str) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("str").innerHTML = this.responseText;

                }
            };
            xhttp.open("GET", "send?str=" + str, true);
            xhttp.send();
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
                    document.getElementById("logContent").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "adcread", true);
            xhttp.send();
        }
    </script>

    <style>
        body {
            max-width: 1170px;
            margin-left: auto;
            margin-right: auto;

            padding-left: 15%;
            padding-right: 15%;
            padding-top: 8%;
            padding-bottom: 8%;


            background-color: rgba(194, 182, 182, 0.26);
        }

        .log-window {
            width: 500px;
            height: 300px;
            border: 1px solid #ccc;
            font-family: monospace;
            bottom: 20px;
            right: 20px;
            background-color: #f9f9f9;
        }

        .log-content {
            padding: 10px;
            height: 255px;
            overflow-y: auto;
        }
    </style>

    <script type="text/javascript">

    </script>
</head>

<body>
    <div class="box">
        <h3>
            CURRENT IP ADDRESS :
            <div class="obj2">192.168.10.10</div>
        </h3>
    </div>

    <div class="box">
        <h3>
            COLOR :
            <input type="number" class="obj2" onchange="send(this.value)">
        </h3>
    </div>

    <div class="box">
        <h3>
            BRIGHTNASS
            <input class="obj2" type="range" min="0" max="100" step="1" value="100">
        </h3>
    </div>

    <div class="box" style="border-bottom-right-radius: 0; border-bottom-left-radius: 0; ">
        <h3>
            PLAN OF ON/OFF
            <div class="obj2">
                <label class="checkbox-ios">
                    <input type="checkbox" id='pooo' name="pooo">
                    <span class="checkbox-ios-switch"></span>
                </label>
            </div>
        </h3>
    </div>

    <div class="box2">

        <div>
            <p></p>
            <h4>TIME ON : <input type="time" class="obj2"></input></h4>
            <p></p>
            <h4>TIME OFF : <input type="time" class="obj2"></input></h4>
            <p></p>

        </div>

    </div>

    </div>

    </div>

    <button class="reset">
        <h4>RESET</h4>
    </button>

    <div class="log-window">
        <div class="log-content" id="logContent">

        </div>
    </div>
</body>

</html>











)rawliteral";