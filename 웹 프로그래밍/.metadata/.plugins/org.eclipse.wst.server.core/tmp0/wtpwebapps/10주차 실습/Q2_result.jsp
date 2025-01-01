<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q2</title>
</head>
<body>
	<h1>결과</h1>
    ${param.id}님의 취미는<br />
    ${paramValues.hobby[0]}
    ${paramValues.hobby[1]}
    ${paramValues.hobby[2]}
    ${paramValues.hobby[3]}
    입니다. <br /><br />
    두수의 합은 ${param.num1 + param.num2}
    <% %>
</body>
</html>