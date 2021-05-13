<%@page contentType="text/html; charset=utf-8" %>
<%
   request.setCharacterEncoding("UTF-8");
   String user = request.getParameter("user");
   String pass = request.getParameter("pass");
%>
	
<!DOCTYPE html>
<html>
<head>  
    <title>Equipment login system</title>  
    <link rel = "stylesheet" type = "text/css">
	<style>
		body{   
    		background: lightblue;  
		}  
		#frm{  
    		border: solid gray 1px;  
    		width:25%;  
    		border-radius: 2px;  
    		margin: 120px auto;  
    		background: white;  
    		padding: 50px;  
		}  
		#btn1{  
    		color: #fff;  
    		background: #337ab7;
			padding: 5px;
		}
		#btn2{  
    		color: #fff;  
    		background: #E69933;
			padding: 5px;
		}
		#btn3{  
    		color: #fff;  
    		background: #769833;
			padding: 5px;
		}
	</style>
</head>  
<body>  
    <div id="frm">  
        <h1>Equipment Login</h1>  
        <form name="f1"  onsubmit="return validation()" method="POST">  
                <label> Account: </label><br>
                <input type="text" name="user"/><br>    
                <label> Password: </label><br>
                <input type="password" name="pass" /><br>
   <!--時間：2017-01-11 描述：輸入框ct100_textcode -->
    <label>驗證:</label><br>
      <input type="text" id="ctl00_txtcode"/>
	<input type="button" id="code" onclick="createCode()" /><br>
      <!--時間：2017-01-11 描述：把驗證碼定義為按鈕，點選重新整理-->
      
                <input type="button" id="btn1" value="Login" onClick="c01()"/>
    <input type="reset" id="btn2" value="Reset" />
    <input type="submit" id="btn3" value="Back" onclick="javascript:location.href='Login.jsp'"/>
    <!--時間：2017-01-11 描述：輸入框ct100_textcode -->
    
      <!--時間：2017-01-11 描述：把驗證碼定義為按鈕，點選重新整理-->
       
        </form>
<%
   request.setCharacterEncoding("UTF-8");
	
   String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/equipment?user=root&password=passwd1234";
   util.DBConnection conn = new util.DBConnection(adostr);
   
   util.RecordSet rs1 = new util.RecordSet();
   String sql = "SELECT * FROM login WHERE username = '"+user+"' AND password = '"+pass+"'";
   rs1.Open(conn,sql);
%>
    </div>     
    <script>  
            function c01() {
        		var a1=document.f1.user.value;  
                var a2=document.f1.pass.value;
    
    
        if(a1!="123" && a1!="456" && a1!="789") {
         alert("帳密錯誤!");
        
         return false;
       } 
     else if(a2!="123" && a2!="123" && a2!="123") {
          alert("帳密錯誤!");
        
         return false;
       }
      var inputCode = document.getElementById("ctl00_txtcode").value.toUpperCase(); 
   //獲取輸入框內驗證碼並轉化為大寫 
    if(inputCode.length <= 0) { //若輸入的驗證碼長度為0
      alert("請輸入驗證碼！"); //則彈出請輸入驗證碼
    }
    else if(inputCode != code) { //若輸入的驗證碼與產生的驗證碼不一致時
      alert("驗證碼輸入錯誤!"); //則彈出驗證碼輸入錯誤
      createCode(); //重新整理驗證碼
      document.getElementById("ctl00_txtcode").value = "";//清空文字框
    } else { //輸入正確時
      alert("登入成功"); //彈出
    location.href='http://localhost:8080/Login_02.jsp';
     }
  }
   //產生驗證碼
   window.onload = function() {
     createCode()
   }
   var code; //在全域性定義驗證碼
   function createCode() {
     code = "";
     var codeLength = 4; //驗證碼的長度
     var checkCode = document.getElementById("code");
     var random = new Array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'); //隨機數
     for(var i = 0; i < codeLength; i++) { //迴圈操作
      var index = Math.floor(Math.random() * 36); //取得隨機數的索引（0~35）
       code += random[index]; //根據索引取得隨機數加到code上
     }
     checkCode.value = code; //把code值賦給驗證碼
   }
   //校驗驗證碼
   function validate() {
   var inputCode = document.getElementById("ctl00_txtcode").value.toUpperCase(); //獲取輸入框內驗證碼並轉化為大寫 
   if(inputCode.length <= 0) { //若輸入的驗證碼長度為0
     alert("請輸入驗證碼！"); //則彈出請輸入驗證碼
   }
   else if(inputCode != code) { //若輸入的驗證碼與產生的驗證碼不一致時
     alert("驗證碼輸入錯誤!"); //則彈出驗證碼輸入錯誤
     createCode(); //重新整理驗證碼
     document.getElementById("ctl00_txtcode").value = "";//清空文字框
   } else { //輸入正確時
     alert("登入成功"); //彈出
 location.href='http://localhost:8080/Login_02.jsp';
    }
  }
        </script>  
</body>     
</html> 