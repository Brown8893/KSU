<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
   String equipment_id = request.getParameter("ID");
   String quantity = request.getParameter("NAME");
   String remaining = request.getParameter("TYPE");

   String ACT = util.paostring.toString(request.getParameter("ACT"));
 %>
<html>
<body><center>
<front size="20"><h3>設備名稱查詢</h3></front>
<form name="REQ" action="t0102-3.jsp">
	<input type="hidden" name="ACT" value="" />
	<strong><front size="8">輸入設備名稱查詢：</front></strong><input type="text" name="ID" value="" size="5"><br /><br>
	<input type="button" value="查詢" onClick="REQ.ACT.value='SEL';REQ.submit()">
	<input type="button" value="清除" onclick="javascript:location.href='t0102-3.jsp'">
	<input type="button" value="返回" onclick="javascript:location.href='t0102.jsp'">
</form></center>
<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/db1229?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 查詢
    if (ACT.equals("SEL")) {
    String sql01 = "SELECT * FROM equipment name query WHERE equipment_id LIKE '%"+equipment_id+"%'";
    conn.execsql(sql01);
   }
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "SELECT * FROM equipment_name_query WHERE equipment_id LIKE '%"+equipment_id+"%'";
    rs1.Open(conn,sql);
    out.print("<table border='1' align='center'>");
    out.print("<tr><td>設備ID</td><td>設備總共數量</td><td>設備剩餘類型</td></tr>");
    while(!rs1.EOF){
       String str1 = "<tr><td>"+rs1.get("equipment_id")+"</td><td>"+rs1.get("quantity")+"</td><td>"+rs1.get("remaining")+"</td></tr>";
       out.print(str1);
       rs1.next();
    }
   out.print("</table>"); 
   conn.close();
%>
</body>
</html>