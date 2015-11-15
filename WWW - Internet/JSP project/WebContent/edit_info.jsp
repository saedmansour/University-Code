<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<% 
	//<verify info="there's a user logged in">
	// TODO: 
	//</verify>
%>    
    
    
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">



<%@page import="java.util.LinkedList"%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<title>Lab: Edit Info</title>
</head>
<body>
	<%  
		User user 		= User.getUser(request.getParameter("user_id"));
		boolean isAdmin = user.isAdmin();
	%>
	<table>
		<tr><td></td><td></td></tr>
		<tr><td></td><td></td></tr>
		<tr><td></td><td></td></tr>
		<tr><td></td><td></td></tr>
		<tr><td></td><td></td></tr>
		<tr><td></td><td></td></tr>
		<%if(isAdmin){ %><tr><td></td><td></td></tr><%} %>
		<%if(isAdmin){ %><tr><td></td><td></td></tr><%} %>
		<tr><td>Save</td><td><input type="submit" /></td></tr>
	</table>
</body>
</html>