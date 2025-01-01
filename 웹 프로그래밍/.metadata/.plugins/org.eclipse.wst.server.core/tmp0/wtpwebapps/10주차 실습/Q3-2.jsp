<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q3</title>
</head>
<body>
	<h1>표현 언어의 문제</h1>
	<h1>1. EL로 pageContext 내장객체의 내용 출력</h1>
	Method : ${pageContext.request.method}<br/>
	URI(requestURL) : ${pageContext.request.requestURI}<br/>
	<hr/>
	
	<h1>1-2. session, application 영역의 내용 출력</h1>
	session 영역 (EL) : ${sessionScope.scopeName3}<br />
    application 영역 (EL) : ${applicationScope.scopeName4}<br />
    <hr/>
    
    <h1>2. 로그인 결과</h1>
    로그인 아이디("id")와 비밀번호("pwd")를 session 객체의 attribute에 저장하고 EL로 출력 <br/>
    <% session.setAttribute("id", request.getParameter("id"));
    session.setAttribute("pwd", request.getParameter("pwd"));%>
    로그인 하신분의 아이디는 ${sessionScope.id}이며, 비밀번호는 ${sessionScope.pwd}입니다.<br/>
    <hr/>
    
    <h1>3. 쿠키("Major")의 내용 출력을 EL로 출력</h1>
    쿠키의 값은 ${cookie.Major.value} 입니다.<br/>
    <a href = "Q3-3.jsp">다음 요청</a>
    
</body>
</html>