<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Q2_sub</title>
  </head>
  <body>
    <h3>forward 액션 태그</h3>
    <hr />
    <div>이 파일은 Q2_sub.jsp 입니다.</div>
    <hr />
    <div>
      현재 웹 브라우저에 나타난 웹 페이지는 <br />
      Q2_main으로부터 이동되었습니다.
    </div>
    <hr />
    <%
    String m = request.getParameter("message");
    out.print("Q2_main.jsp에서 넘어온 메세지 : " + m); 
     %>
  </body>
</html>
