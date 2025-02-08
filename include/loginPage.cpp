class loginPage
{
public:
const static String page;
};
const String loginPage::page = R"rawliteral(





<!DOCTYPE html>
<html>

<head>
	<style>
		* {
			font-family: 'Open Sans', 'sans-serif', 'FontAwesome';
		}

		body {
			background: rgb(52, 56, 61);
		}

		#wrapper {
			position: absolute;
			width: 320px;
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
			<input type="text" name="pass" placeholder="Pass">
			<input type="text" name="ip" class="input-box" placeholder="ip xxx.xxx.xxx.xxx" autocomplete="off" value="192.168.0.123" />
			<input type="text" name="gateway" class="input-box" placeholder="gateway xxx.xxx.xxx.xxx" autocomplete="on" value="192.168.0.1" />
			<input type="text" name="subnet" class="input-box" placeholder="subnet xxx.xxx.xxx.xxx" autocomplete="on" value="255.255.255.0" />
			<input type="submit" value="Submit">
		</form>
	</div>
</body>

</html>






)rawliteral";