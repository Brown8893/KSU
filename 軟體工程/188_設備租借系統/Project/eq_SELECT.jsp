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
   String ACT = util.paostring.toString(request.getParameter("ACT"));
 %>
<html>
<body>
<h3>設備管理員_設備履歷</h3>
<form name="REQ" action="eq_SELECT.jsp">
	<input type="hidden" name="ACT" value="" />
	輸入設備編號查詢：<input type="text" name="ID" value="" size="5"><br />
	<input type="button" value="查詢" onClick="REQ.ACT.value='SEL';REQ.submit()">
	<input type="button" value="清除" onclick="javascript:location.href='eq_SELECT.jsp'">
	<input type="button" value="返回" onclick="javascript:location.href='Login_02.jsp'">
</form>
<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/equipment?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 查詢
    if (ACT.equals("SEL")) {
    String sql01 = "SELECT * FROM equipment_all WHERE eq_id LIKE '%"+eq_id+"%'";
    conn.execsql(sql01);
   }
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "SELECT * FROM equipment_all WHERE eq_id LIKE '%"+eq_id+"%'";
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