<?php
	require_once "OOM.php";

	$log_class = OOM::factory_f("Logs");
	$logs = $log_class->all();
?>

<!DOCTYPE html>
<html>
<head>
	<title>SCANER ARP</title>
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">

	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" crossorigin="anonymous">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
</head>
<body>
	<table class="table table-hover">
		<tr>
			<td>ID</td>
			<td>MAC</td>
			<td>IP</td>
			<td>HORA</td>
		</tr>
		<?php
		foreach ($logs as $log) {
			echo "<tr><td>".$log->attr["id"]."</td>";
			echo "<td>".$log->attr["mac"]."</td>";
			echo "<td>".$log->attr["ip"]."</td>";
			echo "<td>".$log->attr["time"]."</td></tr>";
		}

		?>
	</table>
</body>
</html>