<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
   String sno = util.paostring.toString(request.getParameter("SNO"));
   String sname = util.paostring.toString(request.getParameter("SNAME"));
   String R1 = util.paostring.toString(request.getParameter("R1"));
   String ACT = util.paostring.toString(request.getParameter("ACT"));
   String sage = util.paostring.toString(request.getParameter("SAGE"));
   String sdate = util.paostring.toString(request.getParameter("SDATE")); 
   String sphone = util.paostring.toString(request.getParameter("SPHONE"));
   String saddress = util.paostring.toString(request.getParameter("SADDRESS"));

   System.out.println(sno+","+sname+","+sage+","+sdate+","+sphone+","+saddress+","+R1+","+ACT);
 %>
<html>

<body>
    <h1>員工基本資料管理系統</h1>
<form name="REQ" action="t1230.jsp">
    <input type="hidden" name="ACT" value="" />

	員工姓名<input type="text" name="SNAME" value="" size="5">
    員工編號<input type="text" name="SNO" value="" size="5"><br />
    
    <label for="quantity">年齡</label>
    <input type="number" id="quantity" name="SAGE" min="1" max="100"><br />
    生日<input type="date" name="SDATE" value="" size="5"><br />
    電話<input type="text" name="SPHONE" value="" size="10">
    住址<input type="text" name="SADDRESS" value="" size="15"><br /><br />
	<input type="button" value="新增" onClick="REQ.ACT.value='ADD';REQ.submit()">
	<input type="button" value="編輯" onClick="REQ.action='t1230-edit.jsp';REQ.submit()">
	<input type="button" value="刪除" onClick="REQ.ACT.value='DEL';REQ.submit()"><br /><br />
    <input type="button" value="返回主畫面" onClick="REQ.action='Login_02.jsp';REQ.submit()">
    
    
<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/db1216?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
   
   
    // ----- 新增
    if (!sno.equals("")&& ACT.equals("ADD")) {
    String sql01 = "INSERT INTO staff(sno,sname,sage,sdate,phone,address) values('"+sno+"','"+sname+"','"+sage+"','"+sdate+"','"+sphone+"','"+saddress+"')";
    conn.execsql(sql01);
   }
   
    // ----- 刪除
    if (!R1.equals("")&& ACT.equals("DEL")) {
    String sql01 = "delete from staff where sno='"+R1+"'";
    conn.execsql(sql01);
   }
   
   
   
    if (!R1.equals("") && ACT.equals("DEL")) {
    String sql01 = "DELETE FROM staff WHERE sno='"+R1+"'";
    conn.execsql(sql01);
   }
   
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "select * from staff";
    rs1.Open(conn,sql);
    out.print("<table border='1' cellspacing='0'>");
    out.print("<tr><td>選取</td><td>員工編號</td><td>員工姓名</td><td>年齡</td><td>生日</td><td>電話</td><td>住址</td></tr>");
    while(!rs1.EOF){
       String str1 = "<tr>";
   	   str1 += "<td><input type='radio' name='R1' id='R1' value='"+rs1.get("sno")+"' /></td>";
   	   str1 += "<td>"+rs1.get("sno")+"</td><td>"+rs1.get("sname")+"</td><td>"+rs1.get("sage")+"</td><td>"+rs1.get("sdate")+"</td>"; 
       str1 += "<td>"+rs1.get("phone")+"<td>"+rs1.get("address")+"</td>";
       str1 += "</tr>";
       out.print(str1);
       rs1.next();
    }
   out.print("</table>"); 
   conn.close();
%>
</form>
</body>
</html>
