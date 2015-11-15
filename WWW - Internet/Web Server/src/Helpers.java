import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.Socket;
import java.util.HashMap;
import org.apache.http.HttpResponse;
import org.apache.http.ProtocolVersion;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.DefaultHttpServerConnection;
import org.apache.http.message.BasicHttpResponse;
import org.apache.http.params.BasicHttpParams;


public class Helpers {
	
	@SuppressWarnings("deprecation")
	/**
	 *@param urlString the url string
	 *@return Map mapping from parameter names to their values.
	 *<p>parses the url and gets the query parameters from it</p> 
	 */
	
	public static HashMap<String, String> parameters(String urlString){
		HashMap<String, String> params = new HashMap<String, String>();
		try {
			java.net.URL url = new java.net.URL("http://www.google.com"+urlString);
			String query = url.getQuery();
			
			if(query == null){return params;}
			
			String[] paramAndValueArray = query.split("&");
			for (String paramAndValue : paramAndValueArray) {
				String[] paramAndValueSplitted = paramAndValue.split("=");
				if(!params.containsKey(java.net.URLDecoder.decode(paramAndValueSplitted[0]))){
					params.put(java.net.URLDecoder.decode(paramAndValueSplitted[0],"UTF-8"),
							java.net.URLDecoder.decode(paramAndValueSplitted[1],"UTF-8")
					);
				}
			}
		} catch (MalformedURLException e) {
			System.err.println("URL creation failed in parameters()");
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			System.err.println("ENCODING failed in parameters()");
			e.printStackTrace();
		}
		return params;
	}
	
	/**
	 * 
	 * @param errorMessage the error message.
	 * @param statusCode the status code to retuen with.
	 * @param reasonPhrase the reasonphase. 
	 * @return HttpResponse the response that contains Html page which contains that error information.
	 */
	public static HttpResponse getHtmlResponse(String errorMessage,int statusCode,String reasonPhrase)
	{
		String html = generateHtmlPage(statusCode, reasonPhrase, errorMessage);
		HttpResponse response = new BasicHttpResponse(new ProtocolVersion("HTTP",1,1),statusCode,errorMessage);
		org.apache.http.protocol.HttpDateGenerator dateGenerator = new org.apache.http.protocol.HttpDateGenerator(); 
		response.addHeader("Date", dateGenerator.getCurrentDate());
		response.addHeader("Connection", "close");
		response.addHeader("Content-Type","text/html");
		response.addHeader("Content-Length", Integer.toString(html.length()));
		try {
			response.setEntity(new StringEntity(html));
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		
		return response;
	}

	
/**
 * 
 * @param currRes the response to print
 * @param currSocket the user scoket to print the response to.
 * <p>prints the given response to the given socket.</p>
 */
	public static void printResponseToSocket(HttpResponse currRes,Socket currSocket)
	{
		DefaultHttpServerConnection conn = new DefaultHttpServerConnection();
		try {
			conn.bind(currSocket, new BasicHttpParams());
			conn.sendResponseHeader(currRes);
			conn.sendResponseEntity(currRes);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * 
	 * @param statusCode the status code.
	 * @param reasonPhrase 
	 * @param errorMessage the message to view in the page.
	 * @return
	 */
	public static String generateHtmlPage(int statusCode, String reasonPhrase, String errorMessage){
		String html = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\"> " + 
		"<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">"  +
		"	<head> " +
		"		<title>ERROR</title>" +  
		"	</head> " +
		"	<body> " + 
		String.valueOf(statusCode) + ":" + reasonPhrase + "<br />" +
		errorMessage +
		"	</body>" +
		"</html>";
		
		return html;
	}
}
