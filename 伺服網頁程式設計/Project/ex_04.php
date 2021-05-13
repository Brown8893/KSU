<!DOCTYPE html>
<html>
    <body>
        
        <?php
        $x = 5;
        
        function myTest() {
            $x = 6;
            echo "<p>Variable x inside funtion is: $x</p>";
        }
        myTest();
        
        echo "<p>Variable x outside funtion IS: $x</p>";
        ?>
    </body>
</html>



