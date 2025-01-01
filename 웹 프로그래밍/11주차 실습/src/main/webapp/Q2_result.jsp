<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>2021111971 이재혁 Q2_result</title>
</head>
<body>
    <h3>입력한 값</h3>

    <c:if test="${param.id == '12345678'}">
        USER ID : ${param.id}<br/>
    </c:if>

    <c:if test="${param.name == 'Hong Gil Dong'}">
        USER NAME : ${param.name}<br/>
    </c:if>

    <c:if test="${param.lecture == 'Web Programming'}">
        CLASS NAME : ${param.lecture}<br/>
    </c:if>
</body>
</html>
