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
		HttpSession mysession = request.getSession(true);
		mysession.setAttribute("id", request.getParameter("id"));
		mysession.setAttribute("pwd", request.getParameter("pwd"));
		%>
		
  		세션에 아이디 <%= mysession.getAttribute("id")%>와
  		비밀번호 <%= mysession.getAttribute("pwd")%>를 저장했습니다.<br><br>
  		
  		
  		<%
  		Cookie[] cookies = request.getCookies();
		Cookie NUM = null;
		int cnt = 1;
		
		if(cookies != null) {
			for (Cookie cookie : cookies) {
		           if ("NUM".equals(cookie.getName())) {
		           		NUM = cookie;
		           		cnt = Integer.parseInt(NUM.getValue()) + 1;
		           }
		        }
		}
		 
		 if(cnt == 1){
			 out.print("첫 쿠키를 설정합니다. <br><br>");
			 NUM = new Cookie("NUM", String.valueOf(cnt));
			 NUM.setMaxAge(-1);
			 response.addCookie(NUM);
		 }
		 else {
			 out.print("기존에 쿠키가 설정되어 있었습니다.<br>");
			 out.print("기존 쿠키의 값이 업데이트 되었습니다.<br><br>");
			 response.addCookie(new Cookie("NUM", String.valueOf(cnt)));
		 }
  		%>
  		
  		쿠키 값에 의하면 현재 <%= cnt %>번째 접속입니다.<br><br>
        <a href="GetCookieTest.jsp">쿠키확인</a>
  </body>
</html>