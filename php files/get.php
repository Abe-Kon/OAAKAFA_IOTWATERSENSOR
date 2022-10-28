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

    $q=mysqli_query($con,"select owner_id, place, level from water_level where owner_id={$_GET['owner_id']} order by owner_id DESC LIMIT 5");    
    
    $row=mysqli_fetch_object($q);
    
    echo "
        <table>
            <tr>
                <td>col1</td>
                <td>col1</td>
                <td>col1</td>
            </tr>
    ";
    while ($row)
    {         
        echo "
        <tr>
                    <td>{$row->owner_id}</td>
                    <td>{$row->place} </td>
                    <td>{$row->level}</td>
        </tr>

        ";
        //echo " <br/>{$row->owner_id} {$row->place} {$row->level}<br/>";
        $row=mysqli_fetch_object($q);
    } 
    echo "</table>";     
    


?>

