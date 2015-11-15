package lab;
import java.sql.*;


/*
 * Reserves table:
 * 		login 			CHAR(30), 
 * 		instrumentID 	INT, 
 * 		startDate 		DATETIME, 
 * 		endDate 		DATETIME
 */
public class Reserve {
	
	private String id;
	
	public Reserve(String id) {
		this.id = id;
	}
	
	public static boolean addReserve(String login, String instrumentId, String startDate, String endDate) {
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		// TODO: is there an existing reserve between startDate and endDate
		db.updateQuery("INSERT INTO reserves (login, instrumentid, startdate, enddate) VALUES('" + 
				login + "'," + instrumentId + ",'" + startDate + "','" + endDate + "')");
		db.close();
		//unlock
		return true;
	}
	
	public boolean removeReserve(){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT * FROM reserves WHERE id = " + this.id + "");
		try {
			if(resultSet.next() != true){
				//unlock
				return false;	//user doesn't exist
			}
		} catch (SQLException e) {
			System.out.println("ERROR: in removeUser()");
			e.printStackTrace();
		}
		db.updateQuery("DELETE FROM reserves WHERE id = '" + this.id +"'");
		db.close();
		//unlock
		return true;
	}
	
	//Get the value of a column from a table
	private String getValue(String columnName){
		//lock
		String result 	 = null;
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT " + columnName + " FROM reserves WHERE id = " + this.id);
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
	/*
	private void setValue(String columnName, String value){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		db.updateQuery("UPDATE reserves SET " + columnName + " = '" + value + "'  WHERE id = " + this.id );
		db.close();
		//unlock
	}
	*/

	public String getId(){
		return this.id;
	}
	
	public String getInstrumentId(){
		return getValue("instrumentid");
	}
	
	public String getStartDate(){
		return getValue("startdate");
	}
	
	public String getEndDate(){
		return getValue("enddate");
	}
	
	public String getLogin(){
		return getValue("login");
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//Reserve.addReserve("login", "1", "2001-07-01 00:00:00.000", "2001-07-01 00:00:00.000");
		Reserve r = new Reserve("1");
		System.out.println(r.getId());
		System.out.println(r.getInstrumentId());
		System.out.println(r.getLogin());
		System.out.println(r.getStartDate());
		System.out.println(r.getEndDate());
	}
}
