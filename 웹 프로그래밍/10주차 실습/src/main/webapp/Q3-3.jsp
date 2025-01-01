<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q3</title>
</head>
<body>
	<h1>표현 언어의 사용예제3 - 파라미터 값 처리</h1><br/><br/>
	
	<h1>EL로 로그인 유지화면</h1>
	<h1>1. 로그인 정보를 EL로 출력 </h1>
	로그인 하신분의 아이디는 ${sessionScope.id}이며, 비밀번호는 ${sessionScope.pwd}입니다.<br/>
    <hr/>
    <h1>3. 쿠키("Major")의 내용 출력을 EL로 출력</h1>
    쿠키의 값은 ${cookie.Major.value} 입니다.<br/>
</body>
</html>