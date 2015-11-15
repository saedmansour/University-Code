
import java.sql.*; 



import java.io.FileInputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.ServerSocket;
import java.net.Socket;


import org.apache.http.*;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.*;
import org.apache.http.message.*;
import org.apache.http.params.*;
import org.apache.http.protocol.*;
import org.apache.http.util.EntityUtils;
import java.util.Date;
import java.util.Properties;
import java.text.DateFormat;
import java.text.SimpleDateFormat;



/**
 * 		<p>The Proxy server class</p>
 * 
 */
public class ProxyServer 
{
	private Connection 	connection;	
	
	private String 		url 		= null;
	private String 		dbName 		= null;
	private String 		userName 	= null;
	private String 		password 	= null;
	private int 		proxyPort;
	private Properties  props    	= null;
	
	private final HttpParams 		params;
	private final HttpService 		httpService;

	private ProxyCache mycache;

	
	public static void main(String[] args)
	{
		ProxyServer server = new ProxyServer();
		
		try 
		{
			server.start();
		} catch (Exception e) {
			System.err.println("Error: couldn't start the server!");			
			e.printStackTrace();
		} 
	}

	
	
	/**
	 * The default Constructor.
	 */
	public ProxyServer() 
	{
		try 
		{ 
			
			 props = new Properties();
			 props.load(new FileInputStream("proxy.properties"));
			 
			 dbName = props.getProperty("DBServer.database");
			 userName =  props.getProperty("DBServer.user");
			 password =  props.getProperty("DBServer.password");
			 url = "jdbc:mysql://"+props.getProperty("DBServer.host")+":"+props.getProperty("DBServer.port")+"/";
			 proxyPort = Integer.parseInt(props.getProperty("proxy.port"));
			 
		} 
		catch (Exception e)
		{
			System.err.println("Error: couldn't load properties");
			e.printStackTrace();
			params = null;
			httpService = null;
			return;
		} 


		try 
		{ 
			Class.forName("com.mysql.jdbc.Driver"); 
			connection = DriverManager.getConnection (url+dbName, userName, password); 
			mycache = new ProxyCache(connection);
		} 
		catch (Exception e)
		{
			connection = null;
			
			System.err.println("Error: couldn't open sql connection");
			e.printStackTrace();
			
		} 



		params = new BasicHttpParams();
		params
		.setIntParameter(CoreConnectionPNames.SO_TIMEOUT, 5000)
		.setIntParameter(CoreConnectionPNames.SOCKET_BUFFER_SIZE, 4096)
		.setBooleanParameter(CoreConnectionPNames.STALE_CONNECTION_CHECK, false)
		.setBooleanParameter(CoreConnectionPNames.TCP_NODELAY, true)
		.setParameter(CoreProtocolPNames.ORIGIN_SERVER, "Eyal's awsome http server");

		// Set up the HTTP protocol processor
		BasicHttpProcessor httpProc = new BasicHttpProcessor();

		httpProc.addInterceptor(new HttpResponseInterceptor() {
			@Override
			public void process(HttpResponse res, HttpContext ctx)
			throws HttpException, IOException {
				
				//handle colors replacements
				//TODO: remove
			/*	try{
				HttpEntity resContent = res.getEntity();
				String typeString = resContent.getContentType().getValue();

				if(typeString.matches(".*text/html.*")||typeString.matches(".*text/css.*")||typeString.matches(".*text/plain.*"))
				{
					System.out.println("changing colors");
					res.setEntity(new StringEntity(ColorReplace.replaceColors(EntityUtils.toString(resContent))));
				}
				}catch(Exception e){System.err.println("Color replacement: Couldn't get the content type!");	}*/
				}
			
			});

		httpProc.addInterceptor(new HttpRequestInterceptor() {

			@Override
			public void process(HttpRequest arg0, HttpContext arg1)
			throws HttpException, IOException {
				
				///don't know if there is any need.
				///
				
				//System.out.println("Hadnaling request (before sending it)");
			}
		});

		HttpRequestHandlerRegistry registry = new HttpRequestHandlerRegistry();
		registry.register("*", new HttpRequestHandler() {

			@Override
			public void handle(HttpRequest req, HttpResponse res, HttpContext ctx)
			throws HttpException, IOException {
				
				
				
				//myLog.add(req.getParams(), requestTime, Destination)
				String path = req.getRequestLine().getUri();
				String HostName = req.getFirstHeader("Host").getValue().split(":")[0];
			    int PortNumber = 80;
			    if(req.getFirstHeader("Host").getValue().split(":").length > 1)
			    {PortNumber = Integer.parseInt(req.getFirstHeader("Host").getValue().split(":")[1]); }
			    
			    Log myLog = new Log(connection);
				myLog.add(ctx.getAttribute("userIp").toString(),getDateTime(),path);
			    
			    
			    //used to detrmine if we have it with the right version in cache.
			    boolean isInCache = false;
			    String tempResponseVal;
			    ProxyCache mycache = null;
			    HttpResponse  finalHttpResponse = null;
			    
			    try{
			     mycache = new ProxyCache(connection); 
			    tempResponseVal = mycache.getResponse(path);
			    }catch(Exception e){
			    	tempResponseVal = null;
			    	System.err.println("Error: Couldn't load cache!");
			    	e.printStackTrace();
			    }
				
				//(+)changed (copy all the if statement).
			   if(tempResponseVal!=null)
			   {
					try{
				    finalHttpResponse  = stringToHttpResponse(tempResponseVal); // change to get from the database
					}catch(Exception e){ 
						System.err.println("Error: Database counatins invalid massage!");
						finalHttpResponse = null;}
			   }
			   
			   
			   Header[] Headers=null;
			   if(finalHttpResponse != null)
			   {
				   Headers=  finalHttpResponse.getAllHeaders();
			   }
			    
			    

			    
			    
			    String lastModifiedDate= findLastModified(Headers);  
			    if(Headers != null && lastModifiedDate == null)
			    {
			    	isInCache = true;
			    }
			    
				
			    if(!isInCache)
			    {
			    	
			    	//
			    	//for the moment it seems to by not-in-cache or need varification
			    	//
			    	
			    	HttpParams myparams = getParams();
			    	

			        BasicHttpProcessor httpproc = new BasicHttpProcessor();
			        // Required protocol interceptors
			        httpproc.addInterceptor(new RequestContent());
			        httpproc.addInterceptor(new RequestTargetHost());
			        /*
			        // Recommended protocol interceptors
			        httpproc.addInterceptor(new RequestConnControl());
			        httpproc.addInterceptor(new RequestUserAgent());
			        httpproc.addInterceptor(new RequestExpectContinue());
			         */
			        
			        
			       
			        
			        try
			        {
			        	HttpRequestExecutor httpexecutor = new HttpRequestExecutor();
			        	HttpContext context = new BasicHttpContext();
					          
					    HttpHost host = new HttpHost(HostName, PortNumber);

					    DefaultHttpClientConnection myconn = new DefaultHttpClientConnection();

					    context.setAttribute(ExecutionContext.HTTP_CONNECTION, myconn);
					    context.setAttribute(ExecutionContext.HTTP_TARGET_HOST, host);
	                    Socket tempsocket = new Socket(host.getHostName(), host.getPort());
						
	                    myconn.bind(tempsocket, myparams);
	                    BasicHttpRequest request = new BasicHttpRequest("GET",path);
	                    
	                    request.setParams(myparams);
	                    
	                   
	                    Header[] reqHeaders = req.getAllHeaders();

	                    for(int i=0;i<reqHeaders.length;i++)
	                    {
	                    	
	                    	if((!reqHeaders[i].getName().equals("Accept-Encoding"))&& (!reqHeaders[i].getName().equals("Connection"))&& (!reqHeaders[i].getName().equals("Keep-Alive"))&& (!reqHeaders[i].getName().equals("Proxy-Connection"))&& (!reqHeaders[i].getName().equals("Cache-Control"))&& (!reqHeaders[i].getName().equals("If-Modified-Since"))&& (!reqHeaders[i].getName().equals("If-None-Match")))
	                    	{
	             	            request.removeHeaders(reqHeaders[i].getName());
	                    		request.addHeader(reqHeaders[i]);
	                    	}
	                    }
	                   

	                    request.addHeader("Connection", "close");

	    			    
	                    if(lastModifiedDate != null)
	                    {
	                    	if(request.containsHeader("If-Modified-Since")) {request.removeHeaders("If-Modified-Since");}
	                    	request.addHeader("If-Modified-Since", lastModifiedDate);
	                    }
	                    
	                    
	                    httpexecutor.preProcess(request, httpproc, context);
	                    HttpResponse response = httpexecutor.execute(request, myconn, context);
	                    response.setParams(myparams);
	                    httpexecutor.postProcess(response, httpproc, context);
	                    
	                    HttpEntity ResCont =  response.getEntity();
	                    response.setEntity(ResCont);
	                    //what is the cause that we can only use getEntity once?!!! I've reseted it to solve this problem - don't know if that works!
	                    
	                
	                    if(response.getStatusLine().getStatusCode() == 304)
	                    {
	                    	System.out.println("Validated and found fresh copy. (from cache)");
	                    	isInCache = true;
	                    	//validated and found to be not-modified, so go get it from cache!
	                    
	                    }else
	                    {
	                    	//modified 
	                    	//retrieve it and cache it if allowed..
	                    	
	                    	
	                    	
	                    	Header tempcacheControl = response.getFirstHeader("Cache-Control");
	                    	String cacheControl = null;
	                    	if(tempcacheControl != null){cacheControl = tempcacheControl.getValue();}
	                    	//(+)changes (the if).
	                    	if(!( (cacheControl != null && (cacheControl.equals("no-cache") || cacheControl.equals("no-store")))||(response.getFirstHeader("Transfer-Encoding")!=null )||(ResCont!=null && ResCont.getContentLength() > 65535)))
	                    	{
	                    		
	                    		if(ResCont!=null&&ResCont.getContentType()!=null && ResCont.getContentType().toString().matches(".*text/.*"))
	                    		{
	                    			String responseAsString = HttpResponseToString(response);
	                    			mycache.removeResponse(path);
	                    			mycache.addResponse(path,responseAsString,findLastModified(response.getAllHeaders()));
	                    			finalHttpResponse = stringToHttpResponse(responseAsString);
	                    			
	                    			System.out.println("Saved in cache");
	                    		}else
	                    		{
	                    			System.out.println("Not a text.");
	                    			finalHttpResponse = response;
	                    			
	                    		}

	                    	}else
	                    	{
	                    		System.out.println("Found header preventing chaching");
	                    		finalHttpResponse = response;
	                    	}
	                    	
	                    	
	                    }
	                    
	            //(+)changed      
	              myconn.flush();
	                    
			        	
			        }catch(Exception e){
			        	res.setStatusLine(new BasicStatusLine(HttpVersion.HTTP_1_1, 500, "Internal Server Error"));
			        	System.err.println("Error ocured while handling the request : "+e.getMessage());
			        	return;
			        }
			        
			        
			        
			    }else
			    {
			    	System.out.println("Got from cache.");
			    }
			    

			    //copy the final result to res!
			    

			    Header[] final_headers =null;
			    try{
			    	
			    final_headers = finalHttpResponse.getAllHeaders();
			    
			    }catch(Exception e){
			    	res.setStatusLine(new BasicStatusLine(HttpVersion.HTTP_1_1, 500, "Internal Server Error"));
		        	//res.setEntity(null);
		        	System.err.println("Error ocured while handling the request : coudn't connect to the resource file.");
		        	return;
		        }


			    if(res.containsHeader("Connection"))
			    {
			    	res.removeHeaders("Connection");
			    }
			    
			    res.addHeader("Connection", "close");
			    
			    for(int i=0;i<final_headers.length;i++)
			    {
			    	res.addHeader(final_headers[i]);
			    }
			    res.setStatusLine(finalHttpResponse.getStatusLine());
			    res.setEntity(finalHttpResponse.getEntity());
			    //finished..
			        
			        
				

			}
		});

		httpService = new HttpService(
				httpProc, 
				new NoConnectionReuseStrategy(), 
				new DefaultHttpResponseFactory());
		httpService.setParams( params);
		httpService.setHandlerResolver(registry);
	}



	/**
	 * Starts the server work.
	 */
	public void start()
	{
		DefaultHttpServerConnection conn;
		ServerSocket serverSocket;
		try {
			serverSocket = new ServerSocket(this.proxyPort);
		} catch (IOException e1) {
			System.err.println("error starting the server ,maybe the socket is already in use!");
			return;
		}
		conn = new DefaultHttpServerConnection();
		
		System.out.println("Listening for requests");

		while(true)
		{
			
			try{
			conn.bind(serverSocket.accept(),params);
			HttpContext ctx = new BasicHttpContext();
			ctx.setAttribute("userIp", conn.getRemoteAddress().toString());
			httpService.handleRequest(conn, ctx);
			}catch(Exception e){
				System.err.println("server error handling the request:"+e.getMessage());
				e.printStackTrace();
			}finally{
			System.out.println("request done");
			if(conn.isOpen())
			{
				
				try {
					conn.close();
				} catch (IOException e) {
					System.err.println("couldn't close connection with the user!");
				}
			}
			}
			
		}
		
	}
	
	/**
	 * 
	 * @return our default Http parameters.
	 */
	private HttpParams getParams()
	{
		
    	HttpParams myparams = new BasicHttpParams();
        HttpProtocolParams.setVersion(myparams, HttpVersion.HTTP_1_1);
        HttpProtocolParams.setUserAgent(myparams, "HttpComponents/1.1");
        HttpProtocolParams.setUseExpectContinue(myparams, false);
        return myparams;
	}
	

	/**
	 * 
	 * @param response the Text of the response.
	 * @return the Response as an object.
	 * @throws UnsupportedEncodingException
	 */
	private HttpResponse stringToHttpResponse(String response) throws UnsupportedEncodingException
	{		
		// TODO: check if this work in minimal headers etc...
		String[] headersAndContent 			= response.split("\r\n\r\n", 2);
		String[] statusLineAndHeaders 		= headersAndContent[0].split("\r\n");
		String 	 statusLineString 			= statusLineAndHeaders[0];
		

		
		
		// TODO: verify
		String[] statusLineArray =  statusLineString.split(" ");
		
		
		//<addStatusLine>
		HttpResponse result = new BasicHttpResponse(HttpVersion.HTTP_1_1, 
								Integer.parseInt(statusLineArray[1]), statusLineArray[2]);
		//</addStatusLine>
		
		if(headersAndContent.length > 1)	//has content
		{
			String	 contentString	= headersAndContent[1];
			//<addContent>
			result.setEntity(new StringEntity(contentString));
			//</addContent>
		}
		
		
		//<addHeaders>
		for(int i = 1; i < statusLineAndHeaders.length; i++)
		{
			//split boo:foo:foo with limit = 2 returns "boo" and "foo:foo"
			String[] headerNameAndValue = statusLineAndHeaders[i].split(":", 2);	
			String headerName			 = headerNameAndValue[0].trim();
			String HeaderValue 			 = headerNameAndValue[1].trim();
			
			result.addHeader(headerName, HeaderValue);
		}
		//</addHeaders>
		
		return result;
	}
	
	
	/**
	 * 
	 * @param httpResponse the response to convert to string.
	 * @return the Response as a text.
	 * @throws ParseException When the response in not a legal one.
	 * @throws IOException
	 */
	private String HttpResponseToString(HttpResponse httpResponse) throws ParseException, IOException
	{
		String SP 	= " ";
		String CRLF = "\r\n";
		
		StatusLine statusLine = httpResponse.getStatusLine();
		
		//Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
		String result = 	statusLine.getProtocolVersion() + SP +  
							statusLine.getStatusCode() 		+ SP +
							statusLine.getReasonPhrase() 	+ CRLF;
		
		HeaderIterator headersIterator = httpResponse.headerIterator();
		while(headersIterator.hasNext())
		{
			Header currentHeader = headersIterator.nextHeader();
			result += currentHeader.getName() + ":" + currentHeader.getValue() + CRLF;
		}
		
		result += CRLF;
		
		result += EntityUtils.toString(httpResponse.getEntity());
		
		return result;
	}
	
	
	/**
	 * 
	 * @param Headers the Headers of the httpResponse Object
	 * @return the last modified header value.
	 */
	private String findLastModified(Header[] Headers)
	{
	
		String lastModifiedDate=null;  
    	
	    if((Headers != null))
	    {
	    	for(int i=0;i<Headers.length;i++)
	    	{
	    		if(Headers[i].getName().equals("Last-Modified"))
	    		{
	    			lastModifiedDate = Headers[i].getValue();
	    		}
	    	}
	    }
	    return lastModifiedDate;
		
	}
	
	
	/**
	 * 
	 * @return String the current time and date.
	 */
    private String getDateTime() {
        DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
        Date date = new Date();
        return dateFormat.format(date);
    }
    
    
    
	public void terminate()
	{
		try{
			if(connection!=null && !connection.isClosed())
			{
				connection.close();
			}
		}catch(Exception e){
			
			System.err.println("Error: clouldn't close the connection to database");
		}
	}
	
	
	
    /**
     * Constructs the tables of the cache.
     */
    public void constructCacheTables() {
    	try {
			mycache.constructCacheTables();
		} catch (SQLException e) {
			System.out.println(e.getMessage());
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    }

    /**
     * Deletes the tables of the cache.
     */
    public void deleteCacheTables() {
    	try {
			mycache.deleteCacheTables();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }

    /**
     * Clears the content of the cache (the tables are NOT deleted).
     */
    public void clearCache() {
    	try {
			mycache.clearCache();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
    
    /**
     * Receives an SQL query, poses it over the tables of the cache and prints the results.
     * @param query an SQL query to be posed over the tables of the cache.
     */
    public void poseQuery(String query) {
    	try {
			mycache.query(query);
		} catch (SQLException e) {
		System.err.println("Error: query failed!");
		}
    }

    
    
	
	
	
}