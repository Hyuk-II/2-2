<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
<%@ page import="java.text.*" %>
<% request.setCharacterEncoding("utf-8"); %>
<html>
<body>
<%
String name, e_mail, title, content;
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

int id = Integer.parseInt(request.getParameter("id"));
name = request.getParameter("name");
e_mail = request.getParameter("e_mail");
title = request.getParameter("title");
content = request.getParameter("content");


sql_update = "UPDATE board_tbl SET name = '"+name+"', e_mail = '" + e_mail
					+ "', title = '"+title+"', content = '"+content+"' WHERE id = "+id+";";

try {
    stmt.executeUpdate(sql_update);
} catch(Exception e) {
    out.println("DB 연동 오류입니다. : " + e.getMessage());
}
%>
<center>
<h2>작성한 글이 등록되었습니다.</h2>
<img src="image/red_tree.gif">
<a href="Board-read.jsp?id=<%= id %>"> 작성한 글 확인 </a>
<img src="image/green_tree.gif">
<a href="Board-list.jsp"> 게시글 목록 보기 </a>
</center>
</body>
</html>
