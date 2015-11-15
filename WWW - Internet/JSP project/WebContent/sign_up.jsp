<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
<%
	String username 	= request.getParameter("username");
	String password 	= request.getParameter("password");
	String name 		= request.getParameter("name");
	String phoneNumber 	= request.getParameter("phoneNumber");
	
	if(username != null && password != null && name != null && phoneNumber != null){
		if(User.getUser(username) != null) {	//username already used
			%>
			<jsp:forward page="sign_up.jsp">
					<jsp:param value="loginExists" name="error"/>
			</jsp:forward>
			<% 
		} else {
			User.addUser(username, password, name, null, null, phoneNumber, true, false);
			//make new session
			%>
			<jsp:forward page="view_instruments.jsp">
				<jsp:param value="<%=session.getId()%>" name="sessionID"/>
			</jsp:forward>
			<%
		}
	}
%>
    
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<title>Sign Up</title>
</head>
<body>
		<form action="sign_up.jsp" method="post">
				Username: <input type="text" 	 name="username" /><br />
				Password: <input type="password" name="password" /><br />
				Full name: <input type="text" 	 name="name" /><br />
				Phone number: <input type="text" name="phoneNumber" /><br />
				<input type="submit" /><br />
		</form>
</body>
</html>