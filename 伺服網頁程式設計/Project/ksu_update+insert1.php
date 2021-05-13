<?php
$number=str_replace("'","''",$_REQUEST['number']);
$name=str_replace("'","''",$_REQUEST['name']);
 $db_host = "localhost";
 $db_name = "ksu_database";
 $db_table = "ksu_std_table";
 $db_user = "root";
 $db_password = "";
 
 // 連結檢測
 $conn = mysqli_connect($db_host, $db_user, $db_password);
 if(empty($conn)){
	print  mysqli_error ($conn);
    die ("無法對資料庫連線！" );
	exit;
 }  
 if(!mysqli_select_db( $conn, $db_name)){
	die("資料庫不存在!");
	exit;
 }  

 //自型設定  
 mysqli_set_charset($conn,'utf8');
      

	$result = mysqli_query($conn,"UPDATE $db_table
								  SET ksu_std_name= '$name'
								  WHERE ksu_std_id = '$number'");
	
	$updated_rows = mysqli_affected_rows($conn);

	if ($updated_rows != 0){
		echo "<br> <br>";
		echo "學號	新姓名<br>";
		echo $number . "	" . $name . "<br>";
		echo "1 record updated" . "<br><br>";
	} else{	
		$insert_result = mysqli_query($conn,"INSERT INTO $db_table(ksu_std_id,ksu_std_name)
											 VALUES('$number','$name')");
		echo "於ksu_std_table中,找不到學生學號" . $number . "但已自動加入";
		echo "<br> <br>";
		echo "學號	新姓名<br>";
		echo $number . "	" . $name . "<br>";
		echo "1 record inserted" . "<br><br>";
	}
	echo "<form enctype=\"multipart/form-data\"	method=\"post\"	action=\"ksu_update+insert1.html\">";
	echo "<input type=\"submit\" name=\"sub\" value=\"返回\"/>";
	echo "</form>";
?>