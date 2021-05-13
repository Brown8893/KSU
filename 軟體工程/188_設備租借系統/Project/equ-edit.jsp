<%@page contentType="text/html; charset=utf-8" %>
<!-- charset=big5 -->
<%
   request.setCharacterEncoding("UTF-8");
String eno = util.paostring.toString(request.getParameter("ENO"));
   String ename = util.paostring.toString(request.getParameter("ENAME"));
   String R1 = util.paostring.toString(request.getParameter("R1"));
   String ACT = util.paostring.toString(request.getParameter("ACT"));
   String eclass = util.paostring.toString(request.getParameter("ECLASS"));
   String snid = util.paostring.toString(request.getParameter("SNID")); 
   String date = util.paostring.toString(request.getParameter("DATE"));
   String detail = util.paostring.toString(request.getParameter("DETAIL"));
   
   
   
  System.out.println(eno+","+ename+","+eclass+","+snid+","+date+","+detail+","+R1+","+ACT);
   
   String adostr = "mysql,org.gjt.mm.mysql.Driver,jdbc:mysql://localhost/db1216?user=root&password=passwd1234";
   util.DBConnection conn = new util.DBConnection(adostr);
    
    // ----- 儲存
    if (!eno.equals("SAVE")) {
    String sql01 = "UPDATE equ SET ename = '"+ename+"', eclass = '"+eclass+"', snid = '"+snid+"', date = '"+date+"', detail = '"+detail+"' WHERE eno = '"+eno+"'";
     conn.execsql(sql01);
   }
   
   
   
   
   request.setCharacterEncoding("UTF-8");
   
    util.RecordSet rs1 = new util.RecordSet();
        
    String sql = "select * from equ WHERE eno='"+R1+"'";
    rs1.Open(conn,sql);
    if(!rs1.EOF){
   	   eno = rs1.get("eno");
   	   ename = rs1.get("ename");
       eclass = rs1.get("eclass");
       snid = rs1.get("snid");
       date = rs1.get("date");
       detail = rs1.get("detail");
    }
    out.print("</table>"); 
    conn.close();
 %>
<html>
<body>
<h1>設備管理系統編輯</h1>
<form name="REQ" action="equ-edit.jsp">
    <input type="hidden" name="ACT" value=""/>
	設備編號<input type="text" name="ENO" value="<%=eno%>" size="15" onFocus="this.blur()"><br />
	設備名稱<input type="text" name="ENAME" value="<%=ename%>" size="15"><br />
    分類類別<input type="text" name="ECLASS" value="<%=eclass%>" size="15"><br />
	產品型號<input type="text" name="SNID" value="<%=snid%>" size="15"><br />
	登入日期<input type="text" name="DATE" value="<%=date%>" size="15"><br />
	備註<input type="text" name="DETAIL" value="<%=detail%>" size="15"><br />

	<input type="button" value="儲存" onClick="REQ.ACT.value='SAVE';REQ.submit()">
	<input type="button" value="返回" onClick="REQ.action='equ.jsp';REQ.submit()"><br /><br />
</form>
</body>
</html>
