<%@page contentType="text/html; charset=utf-8" %>
	
<!DOCTYPE html>
<html>
<head>  
    <title>棕熊集團</title>  
    <link rel = "stylesheet" type = "text/css">
	<style>
        
		.login{
			text-align: center;
		}
		.color{
			text-align: center;
			width: auto;
			height: auto;
			background-color: aqua;
		}
		.click{
			font-size: 20px;
		}
	</style>
</head>  
<body>  
        <div class="login">  
        <form name="f1" method="POST">  
        	<div class="color">
				<h1>棕熊公司管理維護系統</h1>
			</div>
    
    
        <div id="frm" name="EQ">  
        <h1>帳戶登入</h1>  
        <form name="f1" action="Login.jsp" onsubmit="return validation()" method="POST">  
                <label> 帳戶: </label>
                <input type="text" id ="user" name="user"/><br>    
                <label> 密碼: </label>
                <input type="password" id="pass" name="pass" /><br><br><br>
                <input type="submit" id="btn1" value="登入" onClick="EQ.action='Login_02.jsp';EQ.submit()"/>
				<input type="reset" id="btn2" value="重置" /><br><br><br><br><br><br><br>
    
        </form>
    

       <form>
            <marquee direction="left" height="100" scrollamount="7" style="font-size: 30px">
				棕熊公司管理維護系統，請先登入方可使用系統
			</marquee>
        </form>
    </div> 
        
        <script>  
            function validation()  
            {  
                window.onscroll = function() {scrollFunction()};
				var id=document.f1.user.value;  
                var ps=document.f1.pass.value;  
                if(id.length=="" && ps.length=="") {  
                    alert("User Name and Password fields are empty");  
                    return false;  
                }  
                else if(id.length=="" || ps.length=="") {  
                        alert("用戶帳密為空");  
                        return false;  
                } 
				else if(id!="admin" ) {
						alert("權限不足");
						return false;
				}
				else if(ps!="0000") {
						alert("權限不足");
						return false;
				}
				else{
					alert("帳號："+id+"  登入成功~");
				}
             }
		
        </script> 
        </body> 
</html> 