#include "header.h"
const String WebPage = R"rawliteral(









<!DOCTYPE html>

<html>

<head>
    <title>config</title>

    <script>
        function send(str) 
        {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              document.getElementById("str").innerHTML = this.responseText;
              
            }
          };
          xhttp.open("GET", "send?str="+str, true);
          xhttp.send();
        }
        setInterval(function() 
        {
          getData();
        }, 2000); 
        function getData() {
          var xhttp = new XMLHttpRequest();
          xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
              document.getElementById("state").innerHTML = this.responseText;
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

        .reset {
            padding-left: 6%;
            padding-right: 6%;

            margin-left: 2%;

            background-color: rgb(219, 102, 19);
            border-radius: 15px;
        }

        .box {
            padding-top: 0.5%;
            padding-bottom: 0.5%;
            padding-left: 6%;
            padding-right: 6%;

            width: 80%;

            margin: 2%;

            background-color: rgb(232, 108, 20);
            border-radius: 15px;
        }

        .obj2 {
            float: right;
            color: black;
        }

        .box2 {

            padding-top: 0.5%;
            padding-bottom: 0.5%;
            padding-left: 6%;
            padding-right: 6%;


            width: 80%;
            top: 120%;

            margin: 2%;
            margin-top: -2%;

            background-color: rgb(255, 151, 77);
            border-bottom-left-radius: 15px;
            border-bottom-right-radius: 15px;

            /*animation: myAnimation 2s infinite;*/


            clip-path: polygon(0% 0, 100% 0%, 100% 100%, 0% 100%);
        }

        .subbox {
            clip-path: polygon(0% 0, 100% 0%, 100% 100%, 0% 100%);
            order: 2;
            padding-top: 0.5%;
            padding-bottom: 0.5%;
            padding-left: 6%;
            padding-right: 6%;

            margin-top: -0.5%;
            margin-bottom: -0.5%;
            margin-left: -7.5%;
            margin-right: -7.5%;

            background-color: rgb(232, 108, 20);
            border-radius: 15px;


        }

        input[type="color"] {
            width: 5rem;
            height: 2rem;
            background-color: rgb(255, 154, 72);
            border-color: black;
            border: 0;
            border-radius: 5px;
            position: relative;
            top: -5px;
        }

        input[type="range"] {
            color: red;

            accent-color: rgb(0, 0, 0);
            background: #ff4500;
            width: 5rem;
            height: 2rem;
            border: 0;
            border-radius: 5px;
            position: relative;
            top: -6px;
        }

        h3 {
            color: rgb(18, 18, 18);
        }

        input {
            background-color: rgb(255, 110, 6);
        }

        .button2 {
            padding-left: 6%;
            padding-right: 6%;

            width: 47%;
            margin-left: 2%;

            background-color: rgb(219, 102, 19);
            border-radius: 15px;
        }

        .checkbox-ios {
            top: -4px;
            display: inline-block;
            height: 28px;
            line-height: 28px;
            margin-right: 10px;
            position: relative;
            vertical-align: middle;
            font-size: 14px;
            user-select: none;
        }

        .checkbox-ios .checkbox-ios-switch {
            position: relative;
            display: inline-block;
            box-sizing: border-box;
            width: 56px;
            height: 28px;
            border: 1px solid rgba(0, 0, 0, .1);
            border-radius: 20%/40%;
            vertical-align: top;
            background: rgb(219, 102, 19);
            transition: .2s;
        }

        .checkbox-ios .checkbox-ios-switch:before {
            content: '';
            position: absolute;
            top: 1px;
            left: 1px;
            display: inline-block;
            width: 24px;
            height: 24px;
            border-radius: 50%;
            background: rgb(0, 0, 0);
            box-shadow: 0 3px 5px rgba(0, 0, 0, .3);
            transition: .15s;
        }

        .checkbox-ios input[type=checkbox] {
            display: block;
            width: 0;
            height: 0;
            position: absolute;
            z-index: -1;
            opacity: 0;
        }

        .checkbox-ios input[type=checkbox]:checked+.checkbox-ios-switch:before {
            transform: translateX(28px);
        }

        .checkbox-ios input[type=checkbox]:checked+.checkbox-ios-switch {
            background: rgb(255, 154, 72);
        }

        .box input[id="pooo"]:checked+label {
            animation: myAnimation 4s infinite alternate, myAnimation2 4s infinite alternate;

        }

        @keyframes myAnimation {
            0% {
                clip-path: polygon(0% 0%, 100% 0%, 100% 0%, 0% 0%);
                transform: translate(0, -100%);

            }

            100% {
                clip-path: polygon(0% 0%, 100% 0%, 100% 100%, 0% 100%);
                transform: translate(0%, 100%);
            }
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
            <input type="color" class="obj2" onchange="send('color')">
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



    <div class="box"  style="border-bottom-right-radius: 0; border-bottom-left-radius: 0; ">
        <h3>
            TIMER
        </h3>

    </div>

    <div class="box2">

        <div>
            <p>
            <h4>TIME : <input type="time" class="obj2"></input></h4>
            <p>
            <button class="button2">
                <h4>START</h4>
            </button> 
            <button class="button2" class="obj2">
                <h4>STOP</h4>
            </button> 


        </div>

    </div>

    <div class="box">
        <h3>
            COLOR CHANGE
            <div class="obj2">
                <label class="checkbox-ios">
                    <input type="checkbox">
                    <span class="checkbox-ios-switch"></span>
                </label>
            </div>
        </h3>
    </div>

    <button class="reset">
        <h4>RESET</h4>
    </button>
</body>

</html>











)rawliteral";
