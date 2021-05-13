<?php
	
	$myfile = fopen("newfile.txt", "w")
			   or die("Unable to open file!");
	$txt = "John Sieg 3\n";
	fwrite($myfile, $txt)
		or die("Unable to write file!");
	$txt = "John Sieg 4\n";
	fwrite($myfile, $txt)
		or die("Unable to write file!");
	fclose($myfile);
	echo "The execution is done completely! <br>";
?>