<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<%request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>2021111971 이재혁 Q1</title>
  </head>
  <body>
    <h1>결과</h1>
    <% String name = request.getParameter("id");
       String[] hobby = request.getParameterValues("hobby");
       int num1 = Integer.parseInt(request.getParameter("num1"));
       int num2 = Integer.parseInt(request.getParameter("num2"));
    %>
    <%= name %>님의 취미는<br />
    <% for(String h : hobby) out.print(h + " ");%>
    입니다. <br /><br />
    두수의 합은 <%= num1+num2 %>
    <% %>
  </body>
</html>
