
//------Import---------------------------------------------------------------------------------
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
//-----/Import---------------------------------------------------------------------------------




//------Class Log------------------------------------------------------------------------------

/**
 * 		<p>This class manages the Log table in the database.</p>
 * 
 * @author SaEd Mansour
 * @author Adi Omary
 */
public class Log {
	
	
	//---Private Fields---------------------------
	private Connection databaseConnection;
	
	
	
	//---Public Functions-------------------------
	
	/**
	 * <p>Log Constructor. It doesn't create the Log table.</p>
	 * 
	 */
	public Log(Connection databaseConnection)
	{
		this.databaseConnection = databaseConnection;
	}
	
	
	/**
	 * <p>Add a row to the Log table.</p>
	 * 
	 * @param clientIP
	 * @param requestTime
	 * @param Destination	A URL.
	 */
	public void add(String clientIP, String requestTime, String Destination)
	{
		try 
		{ 
			PreparedStatement addQuery = databaseConnection.prepareStatement("INSERT INTO Log (IP, RequestTime," +
					"URL) VALUES(?,?,?)");
			
			addQuery.setString(1, clientIP);
			addQuery.setString(2, requestTime);
			addQuery.setString(3, Destination);
			
			addQuery.executeUpdate();
		} 
		catch (SQLException e) 
		{
			e.printStackTrace();
		} 
	}
}
//-----/Class Log------------------------------------------------------------------------------
