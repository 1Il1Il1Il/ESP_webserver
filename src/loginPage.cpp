#include "header.h"
const String loginWebPage = R"rawliteral(





<!DOCTYPE html>
<html>

<head>
	<style>
		

		body {
			background: rgb(52, 56, 61);
		}

		#wrapper {
			position: absolute;
			width: 100%;
			height: 50%;
			left: 50%;
			margin-left: -160px;
			top: 50%;
			margin-top: -75px;
		}

		/* === Sign in Form === */
		#signin {
			height: 90px;
			width: 300px;
			border-radius: 8px;
			position: relative;
		}
		input {
			width: 50%;
			margin: 4px;
			height: 25px;
		}

	</style>
	<meta charset="UTF-8">
	<title>Wifi config</title>
	<link rel="stylesheet" href="css/style.css">
</head>

<body>
	<div id="wrapper">
		<form action="/connect" method="POST">
			<input type="text" name="ssid" placeholder="SSID">
			<input type="password" name="pass" placeholder="Pass">

			<p>static ip :</p>
			<input
			oninput="document.getElementById('text').innerHTML = 'clock settings site :	http://' + this.value;"
			type="text"
			name="ip"
			class="input-box"
			placeholder="ip xxx.xxx.xxx.xxx"
			autocomplete="off"
			value="192.168.0.123"
			/>
			<p><b id="text">clock settings site :	http://192.168.0.123</b></p>
			
			<p>gateWay :</p>
			<p><input type="text" name="gateway" class="input-box" placeholder="gateway xxx.xxx.xxx.xxx" autocomplete="on" value="192.168.0.1"></p>
			<p>subnet :</p>
			<input type="text" name="subnet" class="input-box" placeholder="subnet xxx.xxx.xxx.xxx" autocomplete="on" value="255.255.255.0" />

			<p>dns :</p>
			<p><input type="text" name="dns" class="input-box" placeholder="dns xxx.xxx.xxx.xxx" autocomplete="on" value="8.8.8.8"></p>
			<p>dns2 :</p>
			<p><input type="text" name="dns2" class="input-box" placeholder="dns2 xxx.xxx.xxx.xxx" autocomplete="on" value="8.8.8.8"></p>

			<p></p>
			<input type="submit" value="Submit">
		</form>
	</div>
</body>

</html>






)rawliteral";