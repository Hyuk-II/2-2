<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>2021111971 이재혁 Q3</title>
  </head>
  <body>
    <h1>1. 여기에 각 영역 객체에 아래의 출력에 맞는 Attribute 설정하기</h1>
    <% pageContext.setAttribute("scopeName1", "페이지 내부");
    request.setAttribute("scopeName2", "요청 범위");
    session.setAttribute("scopeName3", "세션 유지");
    application.setAttribute("scopeName4", "서버프로그램"); %>
    <hr />
    <h1>
      2. 영역 객체에 저장된 Attribute의 값을 jsp 스크립틀릿(표현식)과 EL 표현의
      출력 비교
    </h1>
    <h1>2-1. 표현식으로 Attribute값 출력</h1>
    page 영역 : <%=pageContext.getAttribute("scopeName1") %><br />
    request 영역 : <%=request.getAttribute("scopeName2") %><br />
    session 영역 : <%=session.getAttribute("scopeName3") %><br />
    application 영역 : <%=application.getAttribute("scopeName4") %><br />
    <h1>2-2. EL 형식으로 출력</h1>
    page 영역 (EL) : ${pageScope.scopeName1}<br />
    request 영역 (EL) : ${requestScope.scopeName2}<br />
    session 영역 (EL) : ${sessionScope.scopeName3}<br />
    application 영역 (EL) : ${applicationScope.scopeName4}<br />
    <hr />
    <h1>3. 쿠키로 "Major"를 "컴공"으로 설정</h1>
    <% Cookie cookie = new Cookie("Major", "컴공");
    cookie.setMaxAge(60*60);
    response.addCookie(cookie); %>
    <hr />
    <h1>4. 로그인 처리</h1>
    <form action="Q3-2.jsp" method="get">
      아이디 : <input type="text" name="id" /> 비밀번호 :
      <input type="password" name="pwd" />
      <input type="submit" value="확인" />
    </form>
  </body>
</html>
