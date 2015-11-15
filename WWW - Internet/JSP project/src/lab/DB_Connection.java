package lab;
import java.sql.*;



public class DB_Connection {
	
	public static void main(String[] args){
		DB_Connection db = new DB_Connection();
		db.open();
		db.deleteTables();
		db.createTables();
		db.close();
	}
	
	private Connection 	connection;	

	public void open(){
		try {
			Class.forName("com.mysql.jdbc.Driver");
			connection = DriverManager.getConnection ("jdbc:mysql://127.0.0.1:3306/"+"saedmDB", "saedm", "saedm");
		}
		catch (ClassNotFoundException e) {
			System.err.println("ERROR: mysql JDBC class not found.");
			e.printStackTrace();
		}
		catch (SQLException e) {
			System.err.println("ERROR: SQL connection parameters (username,...) are incorrect.");
			e.printStackTrace();
		}
	}
	
	public void close(){
		try {
			connection.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	public void createTables(){
		String createInstrumentsTable = 	"CREATE TABLE IF NOT EXISTS Instruments " +
											"(id INT AUTO_INCREMENT, type CHAR(100), permission TINYINT, timeslot TINYINT, description VARCHAR(512), PRIMARY KEY (id)) " + 
											"ENGINE = INNODB";
		
		String  createUsersTable = 			"CREATE TABLE IF NOT EXISTS Users " +
											"(login CHAR(30), password CHAR(30), name CHAR(80), permissions CHAR(50), usergroup CHAR(80), phoneNumber CHAR(200), active BOOLEAN, admin BOOLEAN, PRIMARY KEY(login)) " +
											"ENGINE = INNODB";
		
		String createReservesTable = 		"CREATE TABLE IF NOT EXISTS Reserves " +
											"(id INT AUTO_INCREMENT, login CHAR(30), instrumentID INT, startDate DATETIME, endDate DATETIME, PRIMARY KEY (id)) " + 
											"ENGINE = INNODB";
		updateQuery(createInstrumentsTable);
		updateQuery(createReservesTable);
		updateQuery(createUsersTable);
	}
	
	public void deleteTables(){
		updateQuery("DROP TABLE Instruments");
		updateQuery("DROP TABLE Users");
		updateQuery("DROP TABLE Reserves");
	}
	
	public ResultSet selectQuery(String query){
		ResultSet resultSet = null;
		Statement statement = null;
		try {
			statement =  connection.createStatement();
			resultSet  = statement.executeQuery(query);
		} catch (SQLException e) {
			System.err.println("ERROR: SQL query is incorrect.");
			e.printStackTrace();
		}
		return resultSet;
	}
	
	public void updateQuery(String query){
		Statement statement = null;
		try {
			statement =  connection.createStatement();
			statement.executeUpdate(query);
		} catch (SQLException e) {
			System.err.println("ERROR: SQL query is incorrect.");
			e.printStackTrace();
		}
	}
}