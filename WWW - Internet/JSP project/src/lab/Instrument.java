package lab;
import java.sql.*;

/*
 *  Instrument table columns: 
 *  	id INT AUTO_INCREMENT, 
 *  	type CHAR(100), 
 *  	permisson TINYINT, 
 *  	timeslot TINYINT, 
 *  	description VARCHAR(512)
 */
public class Instrument {
	
	private String id;

	public Instrument(String id) {
		this.id = id;
	}
	
	public static boolean addInstrument(String type, String permission, String timeslot, String description){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		db.updateQuery("INSERT INTO instruments (type, permission, timeslot, description) VALUES('" + 
				type + "'," + permission + "," + timeslot + ",'" + description + "')");
		
		db.close();
		//unlock
		return true;
	}
		
	public boolean removeInstrument(){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT * FROM instruments WHERE id = " + this.id);
		try {
			if(resultSet.next() != true){
				//unlock
				return false;	//instrument doesn't exist
			}
		} catch (SQLException e) {
			System.out.println("ERROR: in removeUser()");
			e.printStackTrace();
		}
		db.updateQuery("DELETE FROM instruments WHERE id = " + this.id);
		db.close();
		//unlock
		return true;
	}
	
	private void setColumnValue(String column, String value){
		//lock
		DB_Connection db = new DB_Connection();
		db.open();
		db.updateQuery("UPDATE instruments SET " + column + " = '" + value + "'  WHERE id = " + this.id +"");
		db.close();
		//unlock
	}
	
	private String getColumnValue(String column){
		//lock
		String result 	 = null;
		DB_Connection db = new DB_Connection();
		db.open();
		ResultSet resultSet = db.selectQuery("SELECT " + column + " FROM instruments WHERE id = " + this.id +"");
		try {
			if(!resultSet.first()){
				//unlock
				return null;
			}
			result = resultSet.getString(column);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		db.close();
		//unlock
		return result;
	}
	
	public String getType(){
		return getColumnValue("type");
	}
	
	public void setType(String newType){
		setColumnValue("type", newType);
	}
	
	public String getPermission(){
		return getColumnValue("permission");
	}
	
	public void setPermission(String newPermission){
		setColumnValue("permission", newPermission);
	}
	
	public boolean isPermissioned(String permission){
		return getPermission().equals(permission);
	}
	
	public int getTimeslot(){
		return Integer.valueOf(getColumnValue("timeslot"));
	}
	
	public void setTimeslot(String newTimeslot){
		setColumnValue("timeslot", newTimeslot);
	}
	
	public String getDescription(){
		return getColumnValue("description");
	}
	
	public void setDescription(String newDescription){
		setColumnValue("description", newDescription);
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		addInstrument("lll", "1", "14", "Desciripton?!?! no way!");
		Instrument i = new Instrument("2");
		System.out.println(i.getPermission());
		System.out.println(i.getDescription());
		System.out.println(i.getTimeslot());
		System.out.println(i.getType());
		System.out.println(i.isPermissioned("2"));
		i.setDescription("laaaaaaaaaaaaaaaaaaaaaaaa descripiatsion");
		i.setPermission("111");
		i.setTimeslot("10");
		i.setType("notype");
		System.out.println("******************************************");
		System.out.println(i.getPermission());
		System.out.println(i.getDescription());
		System.out.println(i.getTimeslot());
		System.out.println(i.getType());
		System.out.println(i.isPermissioned("2"));
	}
}
