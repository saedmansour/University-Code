package lab;
import java.sql.*;
import java.util.LinkedList;

/*
 *	User table columns: login , password , name , permissions, usergroup, phoneNumber, active.
 */
public class User {
	
	//Adminstrator only.
	public static boolean addUser(String login, String password, String name, String permissions, String group,
										String phoneNumber, boolean active, boolean admin){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT * FROM users WHERE login = '" + login + "'");
		try {
			if(resultSet.next() == true){
				//unlock
				return false;	//login is already used
			}
		} catch (SQLException e) {
			System.out.println("ERROR: in addUser()");
			e.printStackTrace();
		}
		db.updateQuery("INSERT INTO users (login, password, name, permissions, usergroup, phonenumber, active, admin) VALUES('" + 
				login + "','" + password + "','" + name + "','" + permissions + "','" + group + "','" + phoneNumber + "'," + active + "," + admin + ")");
		
		db.close();
		//unlock
		return true;
	}
	
	//Adminstrator only.
	public static boolean removeUser(String login){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT * FROM users WHERE login = '" + login + "'");
		try {
			if(resultSet.next() != true){
				//unlock
				return false;	//user doesn't exist
			}
		} catch (SQLException e) {
			System.out.println("ERROR: in removeUser()");
			e.printStackTrace();
		}
		db.updateQuery("DELETE FROM users WHERE login = '" + login +"'");
		db.close();
		//unlock
		return true;
	}
	
	public static LinkedList<User> getAllUsers(){
		LinkedList<User> usersList = new LinkedList<User>();
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT login FROM users");
		try {
			while(resultSet.next() == true){
				String login = resultSet.getString("login");
				usersList.add(User.getUser(login));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		db.close();
		return usersList;
	}
	
	
	//getUser
	//getUser method is the way to access this class. The constructor is private. 
	
	//For adminstrators only. Return null if user doesn't exist.
	public static User getUser(String login){
		//lock
		User user = new User(login);
		if(!(user.getValue("login").equals(login))){
			//unlock
			return null;
		}
		//unlock
		return user;
	}
	
	//For non-adminstrator users. Return null if the paramaeters are incorrect or user doesn't exist.
	public static User getUser(String login, String password){
		//lock
		User user = new User(login);
		if(!user.getValue("login").equals(login)){
			//unlock
			return null;
		}
		if(!user.getValue("password").equals(password)){
			//unlock
			return null;
		}
		//unlock
		return user;
	}
	
	//login is "username"
	private String login = null;

	
	//private constructor to be called only from getUser
	private User(String login){
		this.login = login;
	}
	
	
	//Get the value of a column from a table
	public String getValue(String columnName){
		//lock
		String result 	 = null;
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT " + columnName + " FROM users WHERE login = '" + login +"'");
		try {
			if(!resultSet.first()){
				//unlock
				return null;
			}
			result = resultSet.getString(columnName);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		db.close();
		//unlock
		return result;
	}

	//Set the value of a column in a table
	public void setValue(String columnName, String value){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		db.updateQuery("UPDATE users SET " + columnName + " = '" + value + "'  WHERE login = '" + login +"'");
		db.close();
		//unlock
	}
	
	
	//---name----
	public String getName(){
		return getValue("name");
	}
	
	public void setName(String newName){
		setValue("name", newName);
	}
	
	//---password----
	public String getPassword(){
		return getValue("password");
	}
	
	public void setPassword(String newPassword){
		setValue("password", newPassword);
	}
	
	//---login----
	public String getLogin(){
		return this.login;
	}
	
	public void setLogin(String newLogin){
		setValue("login", newLogin);
		this.login = newLogin;
	}
	
	
	//---permissions----
	//returns for example if a user has permissions 1,2,3 as: "1-2-3"
	public String getPermissions(){
		return getValue("permissions");
	}
	
	public void setPermissions(String newPermissions){
		setValue("permissions", newPermissions);
	}
	
	public boolean isPermissioned(String permission){
		String[] permissionsArray = getPermissions().split("-");
		for (String permissionIterator : permissionsArray) {
			if(permissionIterator.equals(permission)){
				return true;
			}
		}
		return false;
	}
	
	//---userGroup----
	public void setGroup(String newGroup){
		setValue("usergroup", newGroup);
	}
	
	public String getGroup(){
		return getValue("usergroup");
	}
	
	//---phoneNumber----
	public void setPhoneNumber(String newPhoneNumber){
		setValue("phonenumber", newPhoneNumber);
	}
	
	public String getPhoneNumber(){
		return getValue("phonenumber");
	}
	
	//---active----
	private void setActive(String newActiveValue){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		db.updateQuery("UPDATE users SET active = " + newActiveValue + "  WHERE login = '" + login +"'");
		db.close();
		//unlock
	}
	public void activate(){
		setActive("true");
	}
	public void deactivate(){
		setActive("false");
	}
	
	public boolean istActive(){
		return getValue("active").equals("1");
	}
	
	//---admin----
	public boolean isAdmin(){
		return getValue("admin").equals("1");
	}
	
	private void setAdmin(String newAdminValue){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		db.updateQuery("UPDATE users SET admin = " + newAdminValue + "  WHERE login = '" + login +"'");
		db.close();
		//unlock
	}
	
	public void makeAdmin(){
		setAdmin("true");
	}
	
	public void makeNotAdmin(){
		setAdmin("false");
	}
}