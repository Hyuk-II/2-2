<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@ page import="java.sql.*" %>
<% request.setCharacterEncoding("utf-8"); %>
<html>
<head><title>게시판</title></head>
<body>
<center><h2>게시글 내용</h2></center>
<center>
<%
int id, ref = 0;
String name = "", e_mail = "", title = "", content = "";
Connection conn = null;
Statement stmt = null;
ResultSet rs = null;

id = Integer.parseInt(request.getParameter("id"));

try {
	Class.forName("com.mysql.jdbc.Driver");
	String url = "jdbc:mysql://localhost:3306/wptest?serverTimezone=UTC";
	conn = DriverManager.getConnection(url, "root", "0000");
	stmt = conn.createStatement();
	String sql = "select * from board_tbl where id = " + id;
	rs = stmt.executeQuery(sql);
} catch(Exception e) {
    out.println("DB 연동 오류입니다. : " + e.getMessage());
}

while(rs.next()) {
    name = rs.getString("name");
    e_mail = rs.getString("e_mail");
    title = rs.getString("title");
    content = rs.getString("content");
    ref = Integer.parseInt(rs.getString("ref"));
}
%>
<table border="0" width="500">
<tr>
    <td width="100"><img src="image/ball.gif"> 글쓴이: </td>
    <td><%= name %></td>
</tr>
<tr>
    <td><img src="image/ball.gif"> 메일주소: </td>
    <td><%= e_mail %></td>
</tr>
<tr>
    <td><img src="image/ball.gif"> 글제목: </td>
    <td><%= title %></td>
</tr>
<tr>
    <td><img src="image/ball.gif"> 내용: </td>
    <td><%= content %></td>
</tr>
</table><br><br>

<img src="image/green_tree.gif">
<a href="Board-insert.jsp?ref=<%= ref %>&flag=r"> 댓글 쓰기 </a>

<img src="image/green_tree.gif">
<a href="Board-modify-pwd.jsp?id=<%= id %>"> 게시글 수정 </a>

<img src="image/green_tree.gif">
<a href="Board-delete-pwd.jsp?id=<%= id %>"> 게시글 삭제 </a>

<img src="image/green_tree.gif">
<a href="Board-list.jsp"> 게시글 목록 보기 </a>
</body>
</html>
