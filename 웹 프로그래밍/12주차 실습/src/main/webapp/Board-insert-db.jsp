<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
<%@ page import="java.text.*" %>
<% request.setCharacterEncoding("utf-8"); %>
<html>
<body>
<%
int temp = 0, cnt = 0;
int new_id = 0, ref = 0;
String name, e_mail, title, content, passwd, reply;
Connection conn = null;
Statement stmt = null;
ResultSet rs = null;
String sql_update;

try {
	Class.forName("com.mysql.jdbc.Driver");
	String url = "jdbc:mysql://localhost:3306/wptest?serverTimezone=UTC";
	conn = DriverManager.getConnection(url,"root","0000");
	stmt = conn.createStatement();
	String sql = "select max(id) as max_id, count(*) as cnt from board_tbl";
	rs = stmt.executeQuery(sql);
} catch(Exception e) {
    out.println("DB 연동 오류입니다. : " + e.getMessage());
}

while(rs.next()) {
    cnt = Integer.parseInt(rs.getString("cnt"));
    if(cnt != 0)
        new_id = Integer.parseInt(rs.getString("max_id"));
}

new_id++;
name = request.getParameter("name");
e_mail = request.getParameter("e_mail");
title = request.getParameter("title");
content = request.getParameter("content");
passwd = request.getParameter("passwd");
reply = request.getParameter("reply");

if("y".equals(reply)) {
    ref = Integer.parseInt(request.getParameter("ref"));
} else {
    ref = new_id;
}

sql_update = "INSERT INTO board_tbl (id, name, e_mail, title, content, passwd, ref) VALUES (" 
        + new_id + ", '" + name + "', '" + e_mail + "', '" + title + "', '" + content + "', '" 
        + passwd + "', " + ref + ")";

try {
    stmt.executeUpdate(sql_update);
} catch(Exception e) {
    out.println("DB 연동 오류입니다. : " + e.getMessage());
}
%>
<center>
<h2>작성한 글이 등록되었습니다.</h2>
<img src="image/green_tree.gif">
<a href="Board-list.jsp"> 게시글 목록 보기 </a>
</center>
</body>
</html>
