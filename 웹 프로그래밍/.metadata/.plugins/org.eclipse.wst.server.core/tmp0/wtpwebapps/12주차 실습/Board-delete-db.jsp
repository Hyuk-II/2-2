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
int id;
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

if(request.getParameter("passwd") != null && !passwd.equals(request.getParameter("passwd"))) {
	pageContext.forward("Board-password-failed.jsp");
}
else {
	String delete_sql = "DELETE FROM board_tbl WHERE id = " + id + ";";
	try {
		stmt.executeUpdate(delete_sql);
	} catch(Exception e) {
	    out.println("DB 연동 오류입니다. : " + e.getMessage());
	}
	
}
%>
<center>
<h1>게시글이 삭제되었습니다.</h1>
<img src="image/green_tree.gif">
<a href="Board-list.jsp"> 게시글 목록 보기 </a>
</center>
</body>
</html>