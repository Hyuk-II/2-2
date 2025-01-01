<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q1.jsp</title>
</head>
<body>
	
	<h3>c:if 커스텀 액션 사용</h3>
	<c:set value = "webp" var="msg"/>
	커스텀 변수 msg에 저장된 값 : <c:out value="${msg}"/> <br>
	클라이언트에서 넘어온 값 : <c:out value="${param.t1}"/> <br>
	<c:if test = "${param.t1 == msg}" var="re">
		두 값의 비교결과 : ${re}
	</c:if>
	<hr>
	
	<h3>c:choose 커스텀 액션 사용</h3>
	게이머, 개발자를 choose로 비교<br>
	클라이언트에서 넘어온 값 : ${param.f1}<br>
	당신의 선택은 : 
	<c:choose>
		<c:when test="${param.f1 eq 'gamer'}">
			게이머 입니다.
		</c:when>
		
		<c:when test="${param.f1 eq 'developer'}">
			개발자 입니다.
		</c:when>
		
		<c:otherwise>
			아무것도 선택하지 않았습니다.
		</c:otherwise>
	</c:choose>
	
	<hr>
	<h3>c:forEach 커스텀 액션 사용</h3>
	입력한 숫자 : ${param.val1}
	1부터 입력한 숫자까지의 합 구하기<br>
	<c:set value="0" var="sum"/>
	<c:forEach var="x" begin="1" end="${param.val1}">
	<c:set value="${sum+x}" var="sum"/>
	</c:forEach>
	1부터 ${param.val1}까지의 합 : <c:out value="${sum}"/>
	<hr>
	<h3>c:import 커스텀 액션 사용</h3>
	<c:import url="test1.jsp">
	</c:import>
	<hr>
</body>
</html>