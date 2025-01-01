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
Cookie[] cookies = request.getCookies();
for(Cookie cookie : cookies) {
	cookie.setMaxAge(0);
	response.addCookie(cookie);
}
%>
쿠키가 삭제되었습니다.<br>
<a href="load.jsp">load cookie</a>
</body>
</html>