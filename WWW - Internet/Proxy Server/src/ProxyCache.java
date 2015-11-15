
//------Import--------------------------------------------------------------------------------
import java.sql.*;
//-----/Import---------------------------------------------------------------------------------



//------Class ProxyCache-----------------------------------------------------------------------

/**
 * <p>Manages the proxy cache table.</p>
 * 
 * @author SaEd Mansour
 * @author Adi Omary
 */
public class ProxyCache 
{
	//---Private Fields---------------------------
	//<dataBase constants>
	private Connection databaseConnection;

	private String cacheTable 				 = "cache";
	private String ResponseColumn 	 		 = "Response";
	private String URLColumn 		 		 = "URL";
	private String LastModiefiedColumn 		 = "LastModified";
	//</dataBase constants>
	
	
	
	//---Public Functions-------------------------
	/**
	 * 	<p>Class Constructor</p>
	 */
	public ProxyCache(Connection databaseConnection)
	{
		this.databaseConnection = databaseConnection;  
	}
		
		
	/**
	 * <p>Add a new response to the cache table.</p>
	 * 
	 * @param URL
	 * @param Response	- Headers + Content 
	 * @param LastModifiedHeaderValue
	 * @throws SQLException 
	 */
	public void addResponse(String URL, String Response, String LastModifiedHeaderValue) throws SQLException
	{
		//<prepare query>
		PreparedStatement addResponseQuery = databaseConnection.prepareStatement("INSERT INTO " + this.cacheTable + 
				" (" + this.LastModiefiedColumn + "," + this.ResponseColumn + "," + this.URLColumn + ")" + 
		"VALUES(?,?,?)");
		addResponseQuery.setString(1, LastModifiedHeaderValue);
		addResponseQuery.setString(2, Response);
		addResponseQuery.setString(3, URL);
		//</prepare query>

		
		//<execute query>
		addResponseQuery.executeUpdate();
		//</execute query>
	}
	
		
	/**
	 * <p>Delete a response from the table.</p>
	 * 	
	 * @param URL
	 * @throws SQLException 
	 */
	public void removeResponse(String URL) throws SQLException
	{ 	
		//<prepare query>
		PreparedStatement preparedQueryDeleteContent = databaseConnection.prepareStatement("DELETE FROM "+ this.cacheTable
				+ " WHERE + " + this.URLColumn + " = ?");			
		preparedQueryDeleteContent.setString(1, URL);
		//</prepare query>
		
		
		//<execute query>
		preparedQueryDeleteContent.executeUpdate();
		//</execute query>
	}
		
	
	/**
	 * <p>Get the Content + Headers.</p>
	 * 
	 * @param URL
	 * @return the headers + content of a response.
	 * @throws SQLException 
	 */
	public String getResponse(String URL) throws SQLException
	{
		return getColumnFromCacheTable(URL, this.ResponseColumn);
	}
		
	
	/**
	 * <p>Gets the time the page was Last Modified</p>
	 * 
	 * @param URL
	 * @return the time the page was Last Modified
	 * @throws SQLException 
	 */
	public String getLastModified(String URL) throws SQLException
	{
		return getColumnFromCacheTable(URL, this.LastModiefiedColumn);
	}
		
		
	/**
	 * <p>Makes a select query on the database.</p>
	 * 
	 * @param query of type SELECT
	 * @throws SQLException 
	 */
	public void query(String query) throws SQLException
	{
		//<prepare query and execute>
		PreparedStatement preparedQuery = databaseConnection.prepareStatement(query);
		ResultSet result = preparedQuery.executeQuery();
		//</prepare query and execute>

		
		//<output the result>
		System.out.println("\n***************************************************************");
		System.out.println("poseQuery(" + query + ") result is:\n");
		while(result.next())
		{
			System.out.println("\tURL: " + result.getString(this.URLColumn));
			System.out.println("\tResponse: \n\t\t\t" + result.getString(this.ResponseColumn).replaceAll("\n", "\n\t\t\t"));
			System.out.println("\tLast-Modified: " + result.getString(this.LastModiefiedColumn));
			System.out.println("\n\n--------------------------");
		}
		System.out.println("\n***************************************************************");
		//</output>
	}
		
		
	/**
	 * <p>Construct the tables of the cache and the log.</p>
	 * 	
	 * @throws SQLException
	 */
	public void constructCacheTables() throws SQLException 
	{
		//Construct cache
		//<prepare query and execute>
		PreparedStatement preparedQuery = databaseConnection.prepareStatement("CREATE TABLE " + this.cacheTable
				+ "(" + this.ResponseColumn +  " LONGTEXT character set utf8 collate utf8_bin," +
				this.URLColumn + " TEXT  character set utf8 collate utf8_bin, " + 
				this.LastModiefiedColumn + " TEXT) ENGINE=InnoDB DEFAULT CHARSET=utf8;");
		preparedQuery.executeUpdate();
		//</prepare query and execute>

		
		//Construct Log
		//<prepare query and execute>
		PreparedStatement logQuery = databaseConnection.prepareStatement("CREATE TABLE Log (IP TEXT, RequestTime DATE, URL TEXT);");
		logQuery.executeUpdate();
		//</prepare query and execute>
	}
	
	
	/**
	 * <p>deletes the log and cache tables.</p>
	 * 
	 * @throws SQLException
	 */
	public void deleteCacheTables() throws SQLException 
	{
		//Cache
		//<prepare query and execute>
		PreparedStatement preparedQuery = databaseConnection.prepareStatement("DROP TABLE " + this.cacheTable);
		preparedQuery.executeUpdate();
		//</prepare query and execute>

		//Log
		//<prepare query and execute>
		PreparedStatement logQuery = databaseConnection.prepareStatement("DROP TABLE Log");
		logQuery.executeUpdate();
		//</prepare query and execute>
	}


	//TODO: Q: clear log?
	/**
	 * <p>Clear the cache table(doesn't delete)</p>
	 * 
	 * @throws SQLException
	 */
	public void clearCache() throws SQLException 
	{
		//<prepare query and execute>
		PreparedStatement preparedQuery = databaseConnection.prepareStatement("DELETE FROM " + this.cacheTable);
		preparedQuery.executeUpdate();
		//</prepare query and execute>
	}
	
	
	
	
	//---Private Functions------------------------
	
	/**
	 * <p>Gets a column from the cache table.</p>
	 * 	
	 * @param URL
	 * @param columnName in the table cache
	 * @return	String column's value
	 * @throws SQLException 
	 */
	private String getColumnFromCacheTable(String URL, String columnName) throws SQLException
	{
		PreparedStatement preparedQueryGetHeaders;
		String content = null;

		//<prepare query>
		preparedQueryGetHeaders = databaseConnection.prepareStatement("SELECT " + columnName +
				" FROM " +  this.cacheTable +
				" WHERE + " + this.URLColumn + " = ?");
		preparedQueryGetHeaders.setString(1, URL);
		//</prepare query>

		//<execute query>
		ResultSet contentResultSet = preparedQueryGetHeaders.executeQuery();
		//</execute query>
		
		if(!contentResultSet.first())	//if is empty => no row for this URL
		{ 
			return null;	
		}

		content = contentResultSet.getString(columnName);

		if(columnName == this.LastModiefiedColumn)
		{
			if(content == null)
			{
				return "";
			}
		}
		return content;
	}
}
//-----/Class ProxyCache-----------------------------------------------------------------------
