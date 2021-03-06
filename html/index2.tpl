<html lang='fr'><head><meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>
<title>ESP8266 Demo - www.projetsdiy.fr</title></head><body>
<div class='container-fluid'>
  <div class='row'>
    <div class='col-md-12'>
      <h1>Demo Webserver ESP8266 + Bootstrap</h1>
      <h3>Mini station m&eacute;t&eacute;o</h3>
      <ul class='nav nav-pills'>
        <li class='active'>
          <a href='#'> <span class='badge pull-right'>
          t;
          </span> Temp&eacute;rature</a>
        </li><li>
          <a href='#'> <span class='badge pull-right'>
          h;
          </span> Humidit&eacute;</a>
        </li><li>
          <a href='#'> <span class='badge pull-right'>
          p;
          </span> Pression atmosph&eacute;rique</a></li>
      </ul>
      <table class='table'>  // Tableau des relevés
        <thead><tr><th>Capteur</th><th>Mesure</th><th>Valeur</th><th>Valeur pr&eacute;c&eacute;dente</th></tr></thead> //Entête
        <tbody>  // Contenu du tableau
          <tr><td>DHT22</td><td>Temp&eacute;rature</td><td> // Première ligne : température
            t;
            &deg;C</td><td>
            -</td></tr>
          <tr class='active'><td>DHT22</td><td>Humidit&eacute;</td><td> // 2nd ligne : Humidité
            h;
            %</td><td>
            -</td></tr>
          <tr><td>BMP180</td><td>Pression atmosph&eacute;rique</td><td> // 3ème ligne : PA (BMP180)
            p;
            mbar</td><td>
            -</td></tr>
      </tbody></table>
      <h3>GPIO</h3>
      <div class='row'>
        <div class='col-md-4'><h4 class ='text-left'>D5 
          <span class='badge'>
          etatGpio[0];
        </span></h4></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D5' value='1' class='btn btn-success btn-lg'>ON</button></form></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D5' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>
        <div class='col-md-4'><h4 class ='text-left'>D6 
          <span class='badge'>
          etatGpio[1];
        </span></h4></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D6' value='1' class='btn btn-success btn-lg'>ON</button></form></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D6' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>
        <div class='col-md-4'><h4 class ='text-left'>D7 
          <span class='badge'>
          etatGpio[2];
        </span></h4></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D7' value='1' class='btn btn-success btn-lg'>ON</button></form></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D7' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>
        <div class='col-md-4'><h4 class ='text-left'>D8 
          <span class='badge'>
          etatGpio[3];
        </span></h4></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D8' value='1' class='btn btn-success btn-lg'>ON</button></form></div>
        <div class='col-md-4'><form action='/' method='POST'><button type='button submit' name='D8' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>
      </div>
    <br><p><a href='http://www.projetsdiy.fr'>www.projetsdiy.fr</p>
</div></div></div>
</body></html>