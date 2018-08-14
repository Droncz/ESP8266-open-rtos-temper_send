<html>
<head><title>Esp8266 web server</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="main">
<h1>Esp8266 web server</h1>
<p>
This page has been loaded <b>%counter%</b> times.
<ul>
<li><a href="/wifi">Wi-fi</a> scan and connection.</li>
<li><a href="led.tpl">LED</a>control</li>
<li><a href="websocket/index.html">Websockets</a>.</li>
<li>Esphttpd <a href="test/">test suite</a></li>
<li>OTA <a href="flash/index.html">flashing</a></ul>
</ul>
</p>

<p>
<h2>DHT senzor</h2>
<table border="1"> <tr><th>Sensor</th><th>Value</th><th>Unit</th></tr>
	<tr><td>Teplota</td><td>%temp%</td><td>C</td></tr>
	<tr><td>Tlak</td><td>%pres%</td><td>kPa</td></tr>
	<tr><td>Vlkhost</td><td>%humi%</td><td>%%</td></tr>
</table>

</p>
</div>
</body></html>
