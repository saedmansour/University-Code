<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@page import="lab.User"%>
<%@page import="lab.DB_Connection"%>

<%
	System.out.println("WHAT");

	String error = request.getParameter("error");

	if(error == null || !error.equals("true")){
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		
		if(username != null && password != null){	//if this is a post to the page
			if(User.getUser(username, password) != null) {	//if right details
				//make new sesssion
%>
				<jsp:forward page="view_instruments.jsp">
					<jsp:param value="<%=session.getId()%>" name="sessionID"/>
				</jsp:forward>
<%			
			} else {
%>
				<jsp:forward page="login.jsp">
					<jsp:param value="true" name="error"/>
				</jsp:forward>
<%			
			}
		}
	}
%>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<title>Lab</title>
</head>
<body>
	<% if(error != null && !error.equals("true")) {%>
		The username or password you've entered are incorrect, please try again.<br /> 			
	<% }%>
	<form action="login.jsp" method="post">
		Username: <input type="text" 	 name="username" /><br />
		Password: <input type="password" name="password" /><br />
				  <input type="submit" /><br />
	</form>
</body>
</html>