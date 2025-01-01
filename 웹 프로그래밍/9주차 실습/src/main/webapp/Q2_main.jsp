<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Q2_main</title>
  </head>
  <body>
    <h3>forward 액션 태그</h3>
    <jsp:forward page="Q2_sub.jsp">
      <jsp:param name="message" value="Good luck with your class assignment" />
    </jsp:forward>
  </body>
</html>
