<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁</title>
</head>
<body>
	<%
	HttpSession mysession = request.getSession();
	mysession.invalidate();
	
	Cookie[] cookies = request.getCookies();
    if (cookies != null) {
        for (Cookie cookie : cookies) {
        	cookie.setValue("");
            cookie.setMaxAge(0);
            response.addCookie(cookie);
        }
    }
	%>
	세션과 쿠키가 삭제되었습니다.<br><br>
	<a href="SetCookieTest.html">처음 화면으로</a>
</body>
</html>