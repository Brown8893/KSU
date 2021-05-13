<?php
echo "請使用loop <br><br>";
echo "從5開始，每次減1 <br><br>";

	$result = 5;
	
	for($i=1; $i<=5; $i++){
		$j = $result - $i;
		echo "第 $i 次，則 $j " . "<br>";
	}
?>