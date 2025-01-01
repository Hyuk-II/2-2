<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Q7</title>
</head>
<body>
	<%
	String id = request.getParameter("id");
	String pw = request.getParameter("passwd");
	
	Cookie cookie = new Cookie(id, pw);
	cookie.setMaxAge(60*60);
	response.addCookie(cookie);
	response.sendRedirect("load.jsp");
	%>
</body>
</html>