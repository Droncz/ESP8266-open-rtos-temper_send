<html lang='fr'><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>
<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>
<title>ESP8266</title></head><body>
<div class='container-fluid'>
  <div class='row'>
    <div class='col-md-12'>
      <h1>ESP8266 Webserver + Bootstrap</h1>
      <h3>Mini meteo station</h3>
      <ul class='nav nav-pills'>
        <li class='active'>
          <a href='#'> <span class='badge pull-right'>
          %temp%
          </span> Teplota</a>
        </li><li>
          <a href='#'> <span class='badge pull-right'>
          %humi%
          </span> Atmosférická vlhkost</a>
        </li><li>
          <a href='#'> <span class='badge pull-right'>
          %pres%
          </span> Atmosférický tlak</a></li>
      </ul>
      <table class='table'>
        <thead><tr><th>Senzor</th><th>Typ</th><th>Hodnota</th><th>Předchozí hodnota</th></tr></thead>
        <tbody>
          <tr><td>DHT12</td><td>Teplota</td><td>%temp% &deg;C</td><td>-</td></tr>
          <tr class='active'><td>DHT12</td><td>Atmosférická vlhkost</td><td>%humi% %</td><td>-</td></tr>
          <tr><td>BMP180</td><td>Atmosférický tlak</td><td> %pres% kPa</td><td>-</td></tr>
      </tbody></table>
      <h3>GPIO</h3>
      <div class='row'>
        <div class='col-md-4'>
			<h4 class ='text-left'>GPIO #: %gpio_led1%<span class='badge'>%gpio_led1_state%</span></h4>
		</div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='%gpio_led1%' value='1' class='btn btn-success btn-lg'>ON</button></form></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='%gpio_led1%' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>
        <div class='col-md-4'>
			<h4 class ='text-left'>GPIO #: %gpio_led2%<span class='badge'>%gpio_led2_state%</span></h4>
		</div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='%gpio_led2%' value='1' class='btn btn-success btn-lg'>ON</button></form></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='%gpio_led2%' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>
      </div>
    <br><p><a href='http://www.projetsdiy.fr'>www.projetsdiy.fr</p>
</div></div></div>
</body></html>