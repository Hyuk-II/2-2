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
String passwd = "";
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
    passwd=rs.getString("passwd");
}
if(passwd.equals("")) {
	pageContext.forward("Board-delete-db.jsp");
}
%>
<center>
	<h1>패스워드를 입력하시오.</h1>
	<form method = "post" action="Board-delete-db.jsp">
	<table>
		<tr>
			<td><img src="image/ball.gif"> 패스워드 :</td>
    		<td><input type="password" name="passwd" size="40"></td>
		</tr>
	</table>
	<br>
	<input type="hidden" name = "id" value="<%= id %>">
	<input type = "submit" value = "삭제하기"/> <input type="reset" value="다시쓰기"/><br>
	</form>
	<img src="image/green_tree.gif"><a href="Board-read.jsp?id=<%= id %>">삭제 취소</a>
	<img src="image/island.gif" width = "95%">
</center>
</body>
</html>