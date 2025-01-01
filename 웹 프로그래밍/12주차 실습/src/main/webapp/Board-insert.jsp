<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>게시판 입력</title>
</head>
<body>
	<center><h1>게 시 판</h1></center>
	<form action = "Board-insert-db.jsp" method = "post">
	<%
	String flag = request.getParameter("flag");
	String reply;
	if(flag != null && flag.equals("r")){
		reply = "y";
	}
	else {
		reply = "n";
	}
	%>
	<center>
		<table>
		<tr>
			<td><img src="image/ball.gif"> 글쓴이 :</td>
    		<td><input type="text" name="name" size="20"></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 메일주소 :</td>
	    	<td><input type="text" name="e_mail" size="30"></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 글제목 :</td>
    		<td><input type="text" name="title" size="40"></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 글내용 :</td>
    		<td><textarea name="content" cols = "40" rows = "5"></textarea></td>
		</tr>
		<tr>
			<td><img src="image/ball.gif"> 패스워드 :</td>
    		<td><input type="password" name="passwd" size="15"></td>
		</tr>
		<input type="hidden" name="reply" value="<%= reply %>">
		<input type="hidden" name="ref" value="<%= request.getParameter("ref") %>">
		</table>
		<br>
		<input type = "submit" value = "등록하기"/> <input type="reset" value="다시쓰기"/>
	</center>
	</form>
	
	<br>
	<center><img src="image/green_tree.gif"><a href="Board-list.jsp"> 게시글 목록 보기 </a></center>
	<img src="image/island.gif" width = "95%">
</body>
</html>