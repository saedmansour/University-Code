<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    
<% 
	//<verify info="there's a user logged in">
	// TODO: 
	//</verify>
	
	//<verify info="user is not an admin"> 
	String login = null;	// TODO:  get login from session
	if(User.getUser(login).isAdmin()) {	//if admin
 		%><jsp:forward page="view_instruments.jsp"></jsp:forward><%
	}
	//</verify>
%>        
    
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<title>Insert title here</title>
</head>
<body>
	<%
		//User.getAllReserves();
	%>
</body>
</html>