  <?php


    $servername= "localhost";
    $username="root";
    $password="";
    $dbname="waterworks";
    $con = mysqli_connect($servername,$username,$password,$dbname);


    if (!isset($_GET['owner_id'])) 
        die(" Owner ID not specified");
    if ($_GET['owner_id']=='')
        die(" Owner ID is blank");
    if (!is_numeric($_GET['owner_id'] ) )
        die(" Owner ID is not numeric");
    if ($_GET['owner_id']>'3'||$_GET['owner_id']<'1')
        die(" Owner ID does not exist");
    
    $data=array();        

    $q=mysqli_query($con,"select owner_id, place, level from water_level where owner_id={$_GET['owner_id']} order by level DESC LIMIT 5");    
    
    $row=mysqli_fetch_object($q);
    
    echo "
      <table align='center' width='70%'>;
            <tr bgcolor='#C27BA0'>
                <th><font color='#FFFFFF'>Owner ID</th>
                <th><font color='#FFFFFF'>Location</th>
                <th><font color='#FFFFFF'>Water Level</th>
            </tr>
    ";
    while ($row)
    {         
        echo "
        <tr bgcolor='#C27BA0'><font color='#FFFFFF'>
                    <td><font color='#FFFFFF'>{$row->owner_id}</td>
                    <td><font color='#FFFFFF'>{$row->place} </td>
                    <td><font color='#FFFFFF'>{$row->level}</td>
        </tr>

        ";
        //echo " <br/>{$row->owner_id} {$row->place} {$row->level}<br/>";
        $row=mysqli_fetch_object($q);
    } 
    echo "</table>";     
    


?>

