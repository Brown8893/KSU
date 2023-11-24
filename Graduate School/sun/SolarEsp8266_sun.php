<?php 
header('Content-Type: text/html; charset=utf-8');
include "SolarDateBase.php";

date_default_timezone_set('Asia/Taipei');

$time=date("Y-m-d h:i:s");
$Voltage=$_GET["Voltage"];
$Current=$_GET["Current"];
$Power=$_GET["Power"];

// 查詢最後一條記錄的 ID
$sql = "SELECT id FROM vo_sun ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // 找到最後一條記錄的 ID
    $row = $result->fetch_assoc();
    $last_id = $row["id"];

    $sql =sprintf("INSERT INTO vo_sun (`time`,`vo`,`co`,`pow`) VALUES (now(), '%s', '%s', '%s')",
		    $_GET["Voltage"],$_GET["Current"],$_GET["Power"]);
    
    mysqli_query($conn,$sql) or die ("MYSQL error");

    // 在此基礎上進行修改操作
    $update_sql = "UPDATE vo_sun SET vo = $Voltage, co = $Current, pow = $Power WHERE id = $last_id";

    if ($conn->query($update_sql) === TRUE) {
        echo "記錄更新成功";
    } else {
        echo "Error: " . $conn->error;
    }
} else {
    echo "沒有找到記錄";
}

// 關閉連接
$conn->close();

//$sql =sprintf("INSERT INTO vo_sun (`time`,`vo`,`co`,`pow`) VALUES (now(), '%s', '%s', '%s')",
		
		//$_GET["Voltage"],$_GET["Current"],$_GET["Power"]);
		 
//mysqli_query($conn,$sql) or die ("MYSQL error");

?>