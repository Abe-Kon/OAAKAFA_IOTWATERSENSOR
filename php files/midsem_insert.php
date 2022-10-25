<?php
 	$servername= "localhost";
    $username="root";
    $password="";
    $dbname="waterworks";


$con = mysqli_connect($servername,$username,$password,$dbname);

$place= $_GET['place'];
$distance_cm=$_GET['level'];


$sql = "INSERT INTO water_level (owner_id, place, level) VALUES ('{$place}', '{$distance_cm}')";

if (mysqli_query($con, $sql))
	echo "New record created successfully";
else
	echo "Failed";

?>