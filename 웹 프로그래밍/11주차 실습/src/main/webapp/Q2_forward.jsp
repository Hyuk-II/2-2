<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q2_forward</title>
</head>
<body>
   <c:url var="url" value="Q2_result.jsp">
   		<c:param name="id" value="${list[0]}" />
        <c:param name="name" value="${list[1]}" />
        <c:param name="lecture" value="${list[2]}" />
   </c:url>
   <c:redirect url="${url}"></c:redirect>
</body>
</html>