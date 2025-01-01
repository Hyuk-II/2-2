<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<% request.setCharacterEncoding("utf-8"); %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<%
int id, ref = 0;
String name = "", e_mail = "", title = "", content = "", passwd = "";
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
    passwd=rs.getString("passwd");
}

if(request.getParameter("passwd") != null && !passwd.equals(request.getParameter("passwd"))) {
	pageContext.forward("Board-password-failed.jsp");
}
%>

<form action = "Board-modify-confirmed.jsp?id=<%= id %>" method = "post">
	<center>
		<table>
		<tr>
			<td><img src="image/ball.gif"> 글쓴이 :</td>
    		<td><input type="text" name="name" size="20" value="<%= name %>"></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 메일주소 :</td>
	    	<td><input type="text" name="e_mail" size="30" value="<%= e_mail %>"></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 글제목 :</td>
    		<td><input type="text" name="title" size="40" value="<%= title %>"></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 글내용 :</td>
    		<td><textarea name="content" cols = "40" rows = "5"><%= content %></textarea></td>
		</tr>
		</table>
		<br>
		<input type = "submit" value = "수정하기"/> <input type="reset" value="다시쓰기"/>
	</center>
</form>
	<br>
<center><img src="image/green_tree.gif"><a href="Board-read.jsp?id=<%= id %>">취소</a></center>
<img src="image/island.gif" width = "95%">
</body>
</html>