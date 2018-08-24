<html>
<head>
<meta charset="utf-8">
<meta http-equiv="refresh" content="60">
<meta name="viewport" content="width=device-width; initial-scale=1; shrink-to-fit=no; maximum-scale=2.0;">
<link rel="stylesheet" type="text/css" href="style.css">

<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
<script type="text/javascript">
    google.charts.load('current', {'packages':['gauge']});
    google.charts.setOnLoadCallback(drawChart);
	function drawChart() {
		var data = google.visualization.arrayToDataTable([ 
			['Label', 'Value'], 
			['Moisture',  %chartValue%]
		]); 

		var options = {
			width: 400, height: 120,
			redFrom: 0, redTo: 25,
			yellowFrom: 25, yellowTo: 75,
			greenFrom: 75, greenTo: 100,
			minorTicks: 5
		};

		var chart = new google.visualization.Gauge(document.getElementById('chart_div'));

		chart.draw(data, options);

		setInterval(function() {
			data.setValue(0, 1, %chartValue%);
		chart.draw(data, options);
		}, 13000);
	}
</script>
<title>Řízení GPIO</title>
</head>

<body>
<div id="main">
<h1 style="size:12px;">Vlhkost půdy</h1>
<table>
	<tr><td>Změřená hodnota</td><td>%analogValue%</td><td><div id="chart_div" style="width: 300px; height: 120px;"></div></td>
	<tr><td><button type="submit" onClick="window.location.reload()">Obnovit</button></a></td></tr>
</table>
</div>
</body>
</html>