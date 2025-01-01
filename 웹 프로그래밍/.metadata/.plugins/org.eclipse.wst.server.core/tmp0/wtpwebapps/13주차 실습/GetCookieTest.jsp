<%@ page language="java" contentType="text/html; charset=UTF-8"
pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>2021111971 이재혁</title>
  </head>
  <body>
  	<%
  		HttpSession mysession = request.getSession();
  	%>
  	<h1>세션과 쿠키를 읽어오는 예제</h1>
  	<h1>세션에 저장된 값</h1>
  	아이디 : <%= mysession.getAttribute("id") %> <br><br>
    비밀번호 : <%= mysession.getAttribute("pwd") %> <br><br>
    =============================================== <br>
    <%
    Cookie[] cookies = request.getCookies();
    if(cookies != null){
    for(Cookie cookie : cookies){
    	if(cookie.getName().equals("NUM")) {
        	out.print("<h1>쿠키가 설정되어있습니다.</h1>");
        }
      }
    }
    %>
    =============================================== <br>
    <%
    if(cookies != null){
    for(Cookie cookie : cookies){
    	if(cookie.getName().equals("NUM")){
    %>
    쿠키 이름 : <%=cookie.getName()%><br>
    쿠키 값 : <%=cookie.getValue()%><br>
    쿠키 Domain : <%=cookie.getDomain()%><br>
    쿠키 MaxAge : <%=cookie.getMaxAge()%><br>
    쿠키 path : <%=cookie.getPath()%><br>
    =============================================== <br>
    <%
    	}
      }
    }
    %>
    
    <%
    if(cookies != null){
    for(Cookie cookie : cookies){
    	if(!cookie.getName().equals("NUM")){
    %>
    쿠키 이름 : <%=cookie.getName()%><br>
    쿠키 값 : <%=cookie.getValue()%><br>
    쿠키 Domain : <%=cookie.getDomain()%><br>
    쿠키 MaxAge : <%=cookie.getMaxAge()%><br>
    쿠키 path : <%=cookie.getPath()%><br>
    =============================================== <br>
    <%
    	}
      }
    }
    %>
    <br>
    <a href="SetCookieTest.html">처음 화면으로</a>
    <a href="DeleteCookieTest.jsp">쿠키 삭제하기</a>
  </body>
</html>
