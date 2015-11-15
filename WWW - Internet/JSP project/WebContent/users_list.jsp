<?xml version="1.0" encoding="ISO-8859-1" ?>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>

<% 
	//<verify info="there's a user logged in">
	// TODO: 
	//</verify>
	
	//<verify info="user is an admin"> 
	String login = null;	// TODO:  get login from session
	if(!User.getUser(login).isAdmin()) {	//if not admin
 		%><jsp:forward page="view_instruments.jsp"></jsp:forward><%
	}
	//</verify>
%>    
    
    
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">



<%@page import="java.util.LinkedList"%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
<title>Lab: Users</title>
</head>
<body>
	<table>
		<tr>
				<td>Login</td>
				<td>Full Name</td>
				<td>Research Group</td>
				<td>Phone Number</td>
				<td>Permissions List</td>
		</tr>
	<%
		LinkedList<User> usersList = User.getAllUsers();
		for (User user : usersList) {
			%>
			<tr>
				<td><%=user.getLogin() 		 %></td>
				<td><%=user.getName() 		 %></td>
				<td><%=user.getGroup() 		 %></td>
				<td><%=user.getPhoneNumber() %></td>
				<td><%=user.getPermissions().replace("-", " ") %></td>
			</tr>
			<%	
		}
	%>
	</table>
</body>
</html>