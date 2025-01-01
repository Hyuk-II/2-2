<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q2.jsp</title>
</head>
<body>
	<%@page import = "java.util.*" %>
	<% String[] list = new String[3];
    list[0] = request.getParameter("id");
    list[1] = request.getParameter("name");
    list[2] = request.getParameter("2");
    
    request.setAttribute("list", list);
    
    RequestDispatcher dispatcher = request.getRequestDispatcher("Q2_forward.jsp");
    dispatcher.forward(request, response);
    %>
</body>
</html>