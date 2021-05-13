<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
   String eno = util.paostring.toString(request.getParameter("ENO"));
   String ename = util.paostring.toString(request.getParameter("ENAME"));
   String R1 = util.paostring.toString(request.getParameter("R1"));
   String ACT = util.paostring.toString(request.getParameter("ACT"));
   String snid = util.paostring.toString(request.getParameter("SNID"));
   String date = util.paostring.toString(request.getParameter("DATE")); 
   String eclass = util.paostring.toString(request.getParameter("ECLASS"));
   String detail = util.paostring.toString(request.getParameter("DETAIL"));

   System.out.println(eno+","+ename+","+eclass+","+snid+","+date+","+detail+","+R1+","+ACT);
 %>
<html>

<body>
    <h1>設備管理系統</h1>
<form name="REQ" action="equ.jsp">
    <input type="hidden" name="ACT" value="" />

	
    設備編號<input type="text" name="ENO" value="" size="5"><br />
    設備名稱<input type="text" name="ENAME" value="" size="5">
    分類類別<input type="text"  name="ECLASS" value="" size="5"><br />
    登入日期<input type="date" name="DATE" value="" size="5"><br />
    產品序號<input type="text" name="SNID" value="" size="10">
    備註<input type="text" name="DETAIL" value="" size="15"><br /><br />
	<input type="button" value="新增" onClick="REQ.ACT.value='ADD';REQ.submit()">
	<input type="button" value="編輯" onClick="REQ.action='equ-edit.jsp';REQ.submit()">
	<input type="button" value="刪除" onClick="REQ.ACT.value='DEL';REQ.submit()"><br /><br />
    <input type="button" value="返回主畫面" onClick="REQ.action='Login_02.jsp';REQ.submit()">

<%
    request.setCharacterEncoding("UTF-8");
	
    String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/db1216?user=root&password=passwd1234";
    util.DBConnection conn = new util.DBConnection(adostr);
    
   
   
    // ----- 新增
    if (!eno.equals("")&& ACT.equals("ADD")) {
    String sql01 = "INSERT INTO equ(eno,ename,eclass,snid,date,detail) values('"+eno+"','"+ename+"','"+eclass+"','"+snid+"','"+date+"','"+detail+"')";
    conn.execsql(sql01);
   }
   
    // ----- 刪除
    if (!R1.equals("")&& ACT.equals("DEL")) {
    String sql01 = "delete from equ where eno='"+R1+"'";
    conn.execsql(sql01);
   }
   
   
   
    if (!R1.equals("") && ACT.equals("DEL")) {
    String sql01 = "DELETE FROM equ WHERE eno='"+R1+"'";
    conn.execsql(sql01);
   }
   
    util.RecordSet rs1 = new util.RecordSet();
    
    
    String sql = "select * from equ";
    rs1.Open(conn,sql);
    out.print("<table border='1' cellspacing='0'>");
    out.print("<tr><td>選取</td><td>設備編號</td><td>設備名稱</td><td>分類類別</td><td>登入日期</td><td>產品序號</td><td>備註</td></tr>");
    while(!rs1.EOF){
       String str1 = "<tr>";
   	   str1 += "<td><input type='radio' name='R1' id='R1' value='"+rs1.get("eno")+"' /></td>";
   	   str1 += "<td>"+rs1.get("eno")+"</td><td>"+rs1.get("ename")+"</td><td>"+rs1.get("eclass")+"</td><td>"+rs1.get("date")+"</td>"; 
       str1 += "<td>"+rs1.get("snid")+"<td>"+rs1.get("detail")+"</td>";
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
