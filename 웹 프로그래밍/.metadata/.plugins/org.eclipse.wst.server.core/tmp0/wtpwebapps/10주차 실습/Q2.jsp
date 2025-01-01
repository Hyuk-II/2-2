<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>2021111971 이재혁 Q2</title>
</head>
<body>
	<form method="post" action="Q2_result.jsp">
      아이디 : <input type="text" name="id" /><br /><br />
      -회원님이 관심있는 스포츠를 선택하세요 <br />
      축구<input type="checkbox" name="hobby" value="축구" /> 농구<input
        type="checkbox"
        name="hobby"
        value="농구"
      />
      야구<input type="checkbox" name="hobby" value="야구" /> 골프<input
        type="checkbox"
        name="hobby"
        value="골프"
      />
      <br /><br />
      -계산을 위한 두 수를 입력하세요. <br />
      <input type="text" name="num1" /><input type="text" name="num2" /><br />
      <input type="submit" value="확인" /><input type="reset" value="취소" />
    </form>
</body>
</html>