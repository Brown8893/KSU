<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
   String bno = util.paostring.toString(request.getParameter("SNO"));
   String bname = util.paostring.toString(request.getParameter("SNAME"));
   String R1 = util.paostring.toString(request.getParameter("R1"));
   String ACT = util.paostring.toString(request.getParameter("ACT"));
   
   
 %>
	<style>
		      .box{
  width: 1500px;
  height: 500px;
  margin: auto;
  position: relative;
}
.box6 .content{
  width: 400px;
  position: absolute;
  top:50%;
  left: 50%;
  transform: translate(-50%, -50%);
}
		.button1 {
  background-color: white; 
  color: black; 
  border: 3px solid #4CAF50;
			left: 50%;
}

		</style>
<html>
	
<body>
	<div class="box box6">
<div class="content">
	<div class="button1">
<strong><font size="6">設備租借</font></strong><br><br>
<form name="REQ" action="t1230.jsp">
	<input type="hidden" name="ACT" value="">
	<strong><font size="5">設備ID:</font></strong><input type="text" name="SNO" value="" size="5" style="width:180;height:25  "><br />
	<strong><font size="5">員工工號:</font></strong><input type="text" name="SNAME" value="" size="5" style="width:180;height:25  " ><br />
		<br>
	<input type="button" value="借用" onclick="REQ.ACT.value='ADD';REQ.submit()">
	<input type="button" value="返回" onClick="location.href='t0102.jsp'" >
<input type="button" value="借出單位">
<input type="button" value="設備名稱查詢" onClick="location.href='eq_SELECT.jsp'">
<div>
	</div>
	
	<br>
<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/db1229?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 新增
    if (!bno.equals("") && ACT.equals("ADD")) {
    String sql01 = "INSERT INTO equipment_rental(member_id,equipment_id) values('"+bno+"','"+bname+"')";
    conn.execsql(sql01);
   }
 
   
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "select * from equipment_rental";
    rs1.Open(conn,sql);
    out.print("<table border='1' cellspacing='0'>");
    out.print("<tr><td>選取</td><td>member_id</td><td>equipment_id</td></tr>");
    while(!rs1.EOF){
       String str1 = "<tr>";
   	   str1 += "<td><input type='radio' name='R1' id='R1' value='"+rs1.get("member_id")+"' /></td>";
   	   str1 += "<td>"+rs1.get("member_id")+"</td><td>"+rs1.get("equipment_id")+"</td>";
   	   str1 += "</tr>";
       out.print(str1);
       rs1.next();
    }
   out.print("</table>"); 
   conn.close();

    %>
	</div>
</form>
		</div>
</body>
</html>
