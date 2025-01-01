<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%request.setCharacterEncoding("UTF-8"); %>
<%@page import ="java.util.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Q4_print</title>
</head>
<body>
	<%= request.getParameter("id")%> 님의 취미는<br>
	<%
	String[] list = request.getParameterValues("hobbies");
	for(String hobby : list) {
		out.println(hobby);
	}
	%>
</body>
<%
for(int i = 1; i <= 5; i++) {
%>
<font size="<%=i %>">안녕하세요</font>
<%
}
%>

</html>