<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
   String eq_id = request.getParameter("ID");
   String eq_name = request.getParameter("NAME");
   String eq_type = request.getParameter("TYPE");
   Object eq_spec = request.getParameter("SPEC");
   String eq_price = request.getParameter("PRICE");
   String eq_year = request.getParameter("YEAR");
   Object eq_fund = request.getParameter("FUND");
   String eq_person = request.getParameter("PERSON");
   String eq_date = request.getParameter("DATE");
 %>
<html>
<body>
<h3>設備管理員_設備修改</h3>
<form name="REQ" action="eq_INSERT.jsp">
	*設備產編：<input type="text" name="ID" value="" size="5"><br />
	*設備名稱：<input type="text" name="NAME" value="" size="15"><br />
	*設備類型：<input type="text" name="TYPE" value="" size="10"><br />
	*規範：<input type="text" name="SPEC" value="" size="10"><br />
	*價格：<input type="text" name="PRICE" value="" size="5"><br />
	<label for="quantity">*使用年限：</label>
    <input type="number" id="quantity" name="YEAR" min="1" max="10"><br />
	*金費來源<input type="text" name="FUND" value="" size="15"><br />
	*保管人：<input type="text" name="PERSON" value="" size="10"><br />
	*購買日期：<input type="date" name="DATE" value=""><br />
	<input type="submit" value="新增"><input type="reset" value="Reset"><br />
	<input type="button" value="返回" onclick="javascript:location.href='Login_02.jsp'">
</form>
<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/equipment?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 新增
    if (eq_id!=null) {
    String sql01 = "INSERT INTO equipment_all(eq_id,eq_name,eq_type,eq_specification,eq_price,eq_year,eq_funding,eq_person,eq_buydate) values('"+eq_id+"','"+eq_name+"','"+eq_type+"','"+eq_spec+"','"+eq_price+"','"+eq_year+"','"+eq_fund+"','"+eq_person+"','"+eq_date+"')";
    conn.execsql(sql01);
   }
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "SELECT * FROM equipment_all";
    rs1.Open(conn,sql);
    out.print("<table border='1' align='center'>");
    out.print("<tr><td>設備產編</td><td>設備名稱</td><td>設備類型</td><td>設備規範</td><td>價格</td><td>使用年限</td><td>金費來源</td><td>保管人</td><td>購買日期</td></tr>");
    while(!rs1.EOF){
       String str1 = "<tr><td>"+rs1.get("eq_id")+"</td><td>"+rs1.get("eq_name")+"</td><td>"+rs1.get("eq_type")+"</td><td>"+rs1.get("eq_specification")+"</td><td>"+rs1.get("eq_price")+"</td><td>"+rs1.get("eq_year")+"</td><td>"+rs1.get("eq_funding")+"</td><td>"+rs1.get("eq_person")+"</td><td>"+rs1.get("eq_buydate")+"</td></tr>";
       out.print(str1);
       rs1.next();
    }
   out.print("</table>"); 
   conn.close();
%>
</body>
</html>