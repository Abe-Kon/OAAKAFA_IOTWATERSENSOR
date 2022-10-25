<?php
require "midsem.php";

$con = mysqli_connect($servername,$username,$password,$dbname);

$distance_cm=$_GET['level'];


$sql = "INSERT INTO water (level) VALUES ('{$distance_cm}')";

if (mysqli_query($con, $sql))
	echo "New record created successfully";
else
	echo "Failed";

?>