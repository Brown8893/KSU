<!DOCTYPE html>
<html>
<head>
<style>
table {
  width: 100%;
  border-collapse: collapse;
}

table, td, th {
  font-size: 20px;
  border: 1px solid black;
  padding: 5px;
}

th {
	background: lightyellow;
	text-align: left;
}
</style>
</head>
<body>

<?php
 echo "學號： " . $_GET['std_id'];
 echo "<br>";
 $std_id = $_GET['std_id'];
 $db_host = "localhost";
 $db_name = "ksu_database";
 $db_table = "ksu_std_table";

 $db_user = "root";
 $db_password = "";
 $conn = mysqli_connect($db_host, $db_user, $db_password);
 
 if(empty($conn)){
	print  mysqli_error ($conn);
    die ("無法對資料庫連線！" );
	exit;
 }  
 if(!mysqli_select_db( $conn, $db_name)){
	die("資料庫不存在!");
	exit;
 }  mysqli_set_charset($conn,'utf8');

  echo "AJAX 應用.結合JavaScript, php, and MySQL" . "<br><br>";
  $result = mysqli_query($conn,"SELECT * FROM ksu_std_table WHERE ksu_std_id = '$std_id'");

echo "<table>
	<tr>
	<th>學號</th>
	<th>姓名</th>
	<th>年齡</th>
	<th>入學日期</th>
	<th>分數</th>
	</tr>";
while($row = mysqli_fetch_array($result)) {
  echo "<tr>";
  echo "<td>" . $row['ksu_std_id'] . "</td>";
  echo "<td>" . $row['ksu_std_name'] . "</td>";
  echo "<td>" . $row['ksu_std_age'] . "</td>";
  echo "<td>" . $row['ksu_std_signin'] . "</td>";
  echo "<td>" . $row['ksu_std_grade'] . "</td>";
  echo "</tr>";
}
echo "</table>";
mysqli_close($conn);
?>
</body>
</html>