import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;
import java.util.Queue;
import org.apache.http.HttpResponse;

public class WebServer {

	private String basePath = null;
	private int serverPort;
	private int socketThreadsNum;
	private int requestWorkersNum;
	private int socketQueueSize;
	private int requestQueueSize;
	private Queue<Socket> socketQueue;
	private Queue<Request> requestQueue;
	private boolean initialized =false;
	
	
	
	
    /**
     * Initializes the Web server. This includes the the initialization of the
     * server socket, queues sizes, threads number and specific-type handlers parsing.
     */
    public void initialize() {
    
    	try {
    		//parse the xml config file.
			ParseConfigXML.parse();
			
		} catch (Exception e) {
			System.err.println("couldn't parse the config xml file!");
			System.err.println("Exception msg:"+e.getMessage());
			return;
		}
		
		initialized = true;
		
    	basePath = ParseConfigXML.basePath;
    	serverPort = ParseConfigXML.port;
    	socketThreadsNum = ParseConfigXML.socketReadersMulti;
    	requestWorkersNum= ParseConfigXML.requestHandlersMulti;
    	socketQueueSize=ParseConfigXML.socketQueueSize;
    	requestQueueSize=ParseConfigXML.requestQueueSize;
    	socketQueue  = new LinkedList<Socket>();
    	requestQueue = new LinkedList<Request>();
    	
    	
    }

    /**
     * Starts the server. Within this method, the threads are started and the server
     * socket starts listening.
     */
    
    public void start() {
    	
    	if(!initialized)
    	{
    		System.err.println("Can't run the server if it is not initialized yet.");
    		return;
    	}
    	
		ServerSocket serverSocket=null;
		try {
			serverSocket = new ServerSocket(this.serverPort);
			
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		
		/**
		 * Create the socket reader threads. 
		 */
		for(int i=0;i<socketThreadsNum;i++)
		{
			socketReaderThread sctRdr = new socketReaderThread(socketQueue,requestQueue,requestQueueSize);
			Thread sctRdrTrd= new Thread(sctRdr);
			sctRdrTrd.start();
		}
		
		/**
		 * Create the request handler threads. 
		 */
		for(int i=0;i<requestWorkersNum;i++)
		{
			requestHandlerThread rqstHndlr = new requestHandlerThread(requestQueue,basePath);
			Thread rqstHndlrTrd = new Thread(rqstHndlr);
			rqstHndlrTrd.start();
		}
		
		/**
		 * start listening to incoming connections.
		 */
		while(true)
		{
			try {
				Socket currSocket = serverSocket.accept();
				synchronized(socketQueue)
				{
					
				
				if(!(socketQueue.size()<socketQueueSize && socketQueue.offer(currSocket)))
				{	
					/**
					 * there was no place for the new connection in the socket queue.
					 * tell the user, and close connection.
					 */
					HttpResponse rspns = Helpers.getHtmlResponse("<center>Too much connections to the server<br />try again later..</center>",503,"Service Unavailable");
					Helpers.printResponseToSocket(rspns,currSocket);
					currSocket.close();
					
				}else
				{	
					//awake all the sleeping request handler threads.
					socketQueue.notifyAll();
				}
				
				}
				
				} catch (IOException e) {
					System.err.println("Error handling request:"+e.getMessage());
				}
			
		}
    	
    	
    }
     
    
}