<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>2021111971 이재혁 Q3</title>
  </head>
  <body>
    <h1>String 클래스 사용예제</h1>
    <%String str = "web program"; %>
    <%= "문자열 : " + str %>
    <br>
    <%= "문자열 반환: " + str + "->" + str.substring(5, 10) %>
    <br>
    <%= "문자열 대체: " + str + "->" + str.replace("program", "programming") %>
    <br>
    <%= "문자열 대문자로 변환: " + str + "->" + str.toUpperCase() %>
    <h1>Try-catch문 사용예제</h1>
    <%
    try	{
    	int num;
    	for(int i =5; i >= 0; i--) {
    		num = 30/i;
    		out.print(num + "<br>");
    	}
    }
    catch(Exception e) {
    	out.print("오류가 발생했습니다. <br>");
    	out.print("오류(getMessage) : " + e.getMessage() + " <br>");
    }
    %>
  </body>
</html>
