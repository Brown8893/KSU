<?php

 $co=str_replace("'","''",$_REQUEST['co']);

  $db_host = "localhost";
  $db_name = "aaa";
  $db_table = "vo_1004";

 $db_user = "root";
 $db_password = "g030a004";
 $conn = mysqli_connect($db_host, $db_user, $db_password);  //建立連線
 if(empty($conn)){
	print  mysqli_error ($conn);
    die ("無法對資料庫連線！" );
	exit;
 } 

 if(!mysqli_select_db( $conn, $db_name)){
	die("資料庫不存在!");
	exit;
 }
 mysqli_set_charset($conn,'utf8');
 
 
    
$result = mysqli_query($conn,"SELECT * FROM $db_table where co = '$co'");
    



echo "<table border='2'>
<tr>
<th>ID</th>
<th>電壓</th>
<th>電流</th>


</tr>";

while($row = mysqli_fetch_array($result))
  {
  
  echo "<tr>";
  
  echo "<td>" . $row['id'] . "</td>";
  echo "<td>" . $row['vo'] . "</td>";
  echo "<td>" . $row['co'] . "</td>";
	 
  
  echo "</tr>";
  }
echo "</table>";

echo "1 record find";
?>

<form enctype="multipart/form-data"  method="post" action="ksu_find.html">
<input type="submit" name="sub" value="返回"/>
</form>