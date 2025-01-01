<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Beer Recommendation JSP</title>
</head>
<body>
	<center>
		<h1>Beer Recommendation JSP</h1>
	</center>
	try : <%= request.getAttribute("beer1") %><br>
	try : <%= request.getAttribute("beer2") %><br>
</body>
</html>