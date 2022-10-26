<?php
require "midsem.php";


    if (!isset($_GET['owner_id'])) 
        die(" Owner ID not specified");
    if ($_GET['owner_id']=='')
        die(" Owner ID is blank");
    if (!is_numeric($_GET['owner_id'] ) )
        die(" Owner ID is not numeric");
    
    $data=array();        

    $q=mysqli_query($con,"select owner_id, place, level from water_level where owner_id={$_GET['owner_id']} order by owner_id desc");    
    
    $row=mysqli_fetch_object($q);
    while ($row)
    {         
        
        echo " <br>{$row->owner_id} {$row->place} {$row->level}<br>";
        $row=mysqli_fetch_object($q);
    }       
    


?>

