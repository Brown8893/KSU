<%@page contentType="text/html; charset=utf-8" %>
<%@ page import="java.io.*,java.util.*" %>
    
<%
   request.setCharacterEncoding("UTF-8");
   String user = request.getParameter("user");
   String pass = request.getParameter("pass");
%>
    
 <%
   
   Date createTime = new Date(session.getCreationTime());
   
   Date lastAccessTime = new Date(session.getLastAccessedTime());
   
%>  

     
<!doctype html>
<html>
  
<head>
<meta charset="utf-8">
<title>棕熊集團</title>
    
<style>    
h1
{
    background-color:orange;
    text-align:center;
}  
   
h2{
 color:red;
      
}    
</style>    
    
</head>
<body>  
     <table border="1" align="center"> 
   
<tr>
   <td>現在時間</td>
   <td><% out.print(lastAccessTime); %></td>
</tr>          
 </table>                             

      <form name="f1" method="POST" class="mb">  
      		<div class="brown">
				<h1 color:pink>棕熊公司設備管理系統</h1>
			</div>
			<div class="member">
				<h2>請勿洩漏公司機密，違者送辦!!!</h2>
			</div>

			<div>
				<input type="button" id="use" value="員工基本資料管理系統"  onclick="location.href='t1230.jsp'"> 
                
				<input type="button" id="buy" value="設備管理系統" " onclick="location.href='equ.jsp'"><br> 
			</div>
     </form>
       

                                                                                                                                      
</body>
</html>
