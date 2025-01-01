<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body>
<%String id = request.getParameter("id"); %>
<center>
	<h1>잘못된 패스워드입니다.</h1>
	<img src="image/green_tree.gif"><a href="Board-read.jsp?id=<%= id %>">뒤로</a><br>
	<img src="image/island.gif" width = "95%">
</center>
</body>
</html>