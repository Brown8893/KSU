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
   
   
   
  System.out.println(sno+","+sname+","+R1+","+sage+","+sdate+","+sphone+","+saddress+","+ACT);
   
   String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/db1216?user=root&password=passwd1234";
   util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 儲存
    if (!sno.equals("SAVE")) {
    String sql01 = "UPDATE staff SET sname = '"+sname+"', sage = '"+sage+"', sdate = '"+sdate+"', phone = '"+sphone+"', address = '"+saddress+"' WHERE sno = '"+sno+"'";
     conn.execsql(sql01);
   }
   
   request.setCharacterEncoding("UTF-8");
   
    util.RecordSet rs1 = new util.RecordSet();
        
    String sql = "select * from staff WHERE sno='"+R1+"'";
    rs1.Open(conn,sql);
    if(!rs1.EOF){
   	   sno = rs1.get("sno");
   	   sname = rs1.get("sname");
       sage = rs1.get("sage");
       sdate = rs1.get("sdate");
       sphone = rs1.get("phone");
       saddress = rs1.get("address");
    }
    out.print("</table>"); 
    conn.close();
 %>
<html>
<body>
<h1>員工基本資料編輯</h1>
<form name="REQ" action="t1230-edit.jsp">
    <input type="hidden" name="ACT" value=""/>
	員工編號<input type="text" name="SNO" value="<%=sno%>" size="15" onFocus="this.blur()"><br />
	員工姓名<input type="text" name="SNAME" value="<%=sname%>" size="15"><br />
    年齡<input type="text" name="SAGE" value="<%=sage%>" size="15"><br />
	生日<input type="text" name="SDATE" value="<%=sdate%>" size="15"><br />
	電話<input type="text" name="SPHONE" value="<%=sphone%>" size="15"><br />
	住址<input type="text" name="SADDRESS" value="<%=saddress%>" size="15"><br />

	<input type="button" value="儲存" onClick="REQ.ACT.value='SAVE';REQ.submit()">
	<input type="button" value="返回" onClick="REQ.action='t1230.jsp';REQ.submit()"><br /><br />
</form>
</body>
</html>
