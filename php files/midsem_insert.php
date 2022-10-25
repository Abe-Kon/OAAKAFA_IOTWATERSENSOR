<?php
require "midsem.php";

$owner_id= $_GET['owner_id'];
$place= $_GET['place'];
$distance_cm=$_GET['level'];


$sql = "INSERT INTO water_level (owner_id, place, level) VALUES ('{$owner_id}', '{$place}', '{$distance_cm}')";

if (mysqli_query($con, $sql))
	echo "New record created successfully";
else
	echo "Failed";

?>