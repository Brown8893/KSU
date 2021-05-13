<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
   String eq_name = request.getParameter("NAME");
   String eq_type = request.getParameter("TYPE");
   String eq_price = request.getParameter("PRICE");
   String eq_quantity = request.getParameter("QUAN");
   String eq_year = request.getParameter("YEAR");
   String eq_reason = request.getParameter("REAS");
   String eq_stamp = request.getParameter("DATE");
   Object eq_specification = request.getParameter("SPEC");
   String ACT = util.paostring.toString(request.getParameter("ACT"));
 %>
<html>
<body>
<h3>設備管理員_設備添購</h3>
<form name="REQ" action="eq_BUY.jsp">
	<input type="hidden" name="ACT" value="" />
	*設備名稱：<input type="text" name="NAME" value="" size="20"><br />
	*設備類型：<input type="text" name="TYPE" value="" size="10"><br />
	*價格：<input type="text" name="PRICE" value="" size="5"><br />
	<label for="quantity">*數量：</label>
    <input type="number" id="quantity" name="QUAN" min="1" max="100"><br />
	<label for="quantity">*使用年限：</label>
    <input type="number" id="quantity" name="YEAR" min="1" max="10"><br />
	*購買原因: <input type="text" name="REAS" value="" size="25"><br />
	*購買日期戳記：<input type="datetime-local" name="DATE" value=""><br />
	*規格：<input type="text" name="SPEC" value="" size="20"><br />
	<input type="submit" value="送出" onClick="REQ.ACT.value='ADD';REQ.submit()">
	<input type="reset" value="Reset">
	<input type="button" value="返回" onclick="javascript:location.href='Login_02.jsp'">
</form>
<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/equipment?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 新增
    if (ACT.equals("ADD")) {
    String sql01 = "INSERT INTO equipment_buylist(eq_name,eq_type,eq_price,eq_quantity,eq_year,eq_reason,eq_stamp,eq_specification) values('"+eq_name+"','"+eq_type+"','"+eq_price+"','"+eq_quantity+"','"+eq_year+"','"+eq_reason+"','"+eq_stamp+"','"+eq_specification+"')";
    conn.execsql(sql01);
   }
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "SELECT * FROM equipment_buylist WHERE eq_stamp = '"+eq_stamp+"'";
    rs1.Open(conn,sql);
    out.print("<table border='1' align='center'>");
    out.print("<tr><td>設備名稱</td><td>類型</td><td>單價</td><td>數量</td><td>使用年限</td><td>購買原因</td><td>時間戳記</td><td>設備規格</td></tr>");
    while(!rs1.EOF){
       String str1 = "<tr><td>"+rs1.get("eq_name")+"</td><td>"+rs1.get("eq_type")+"</td><td>"+rs1.get("eq_price")+"</td><td>"+rs1.get("eq_quantity")+"</td><td>"+rs1.get("eq_year")+"</td><td>"+rs1.get("eq_reason")+"</td><td>"+rs1.get("eq_stamp")+"</td><td>"+rs1.get("eq_specification")+"</td></tr>";
       out.print(str1);
       rs1.next();
    }
   out.print("</table>"); 
   conn.close();
%>
</body>
</html>