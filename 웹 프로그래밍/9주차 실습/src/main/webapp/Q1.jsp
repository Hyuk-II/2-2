<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>2021111971 이재혁 Q1</title>
  </head>
  <body>
  <%
    for(int i = 1; i <= 10; i++) {
        for(int j = 0; j < 10 - i; j++) {
            out.print("&nbsp");
        }

        for(int j = 0; j < i; j++) {
            out.print("*");
        }
        out.print("<br>");
    }
  
    for(int i = 10; i >= 1; i--) {
        for(int j = 0; j < 10 - i; j++) {
            out.print("&nbsp");
        }

        for(int j = 0; j < i; j++) {
            out.print("*");
        }
        out.print("<br>");
    }
  %>
  </body>
</html>
