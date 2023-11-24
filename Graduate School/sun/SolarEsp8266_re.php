<?php 
header('Content-Type: text/html; charset=utf-8');
include "SolarDateBase.php";

date_default_timezone_set('Asia/Taipei');

$time=date("Y-m-d h:i:s");
$time=date("Y-m-d h:i:s");
$Vo1=$_GET["Vo1"];
$Lux1=$_GET["Lux1"];
$Vo2=$_GET["Vo2"];
$Lux2=$_GET["Lux2"];
$Vo3=$_GET["Vo3"];
$Lux3=$_GET["Lux3"];

// 查詢最後一條記錄的 ID
$sql = "SELECT id FROM vo_sun ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // 找到最後一條記錄的 ID
    $row = $result->fetch_assoc();
    $last_id = $row["id"];

    $sql =sprintf("INSERT INTO vo_sun (`time`,`sun_v1`,`lux_1`,`sun_v2`,`lux_2`,`sun_v3`,`lux_3`) VALUES (now(),  '%s', '%s', '%s', '%s', '%s', '%s')",		
		    $_GET["Vo1"],$_GET["Lux1"],$_GET["Vo2"],$_GET["Lux2"],$_GET["Vo3"],$_GET["Lux3"]);
    
    mysqli_query($conn,$sql) or die ("MYSQL error");

    // 在此基礎上進行修改操作
    $update_sql = "UPDATE vo_sun SET sun_v1 = '$Vo1', lux_1 = '$Lux1', sun_v2 = '$Vo2', lux_2 = '$Lux2', sun_v3 = '$Vo3', lux_3 = '$Lux3' WHERE id = $last_id";

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