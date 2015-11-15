import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.SocketException;
import java.util.Queue;



public class socketReaderThread  implements Runnable{
	private Queue<Socket> socketQueue;
	private Queue<Request> requestQueue;
	private int maxAllowed;
	private Boolean working=true;
	
	
	/**
	 * 
	 * @param squeue the socket queue from which the socket reads takes the sockets to read.
	 * @param rQueue the request queue that the socket reads pushes the request to it.
	 * @param umaxAllowed the maximum length of the request queue;
	 */
	socketReaderThread(Queue<Socket> squeue,Queue<Request> rQueue,int umaxAllowed)
	{
		socketQueue = squeue;
		requestQueue = rQueue;
		maxAllowed = umaxAllowed;
	}
	
	
	/**
	 *<p> the main method of the socket read</p>
	 * <p>this methods starts the socket reader.</p>
	 */
	public void run()
	{
		Socket tempSocket=null;
		while(working)
		{
			synchronized(socketQueue)
			{
				while(socketQueue.size() == 0) //could be changed to tempSocket==null with some more changes
				{
					try {
						
						
						socketQueue.wait();
						
						
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
				tempSocket = socketQueue.poll();
			}
			
			
			/*
			 * set time out to 7 seconds , if the reader couldn't get the  request from the user in 7 seconds it closes the connection.
			 */
			
			try {
				tempSocket.setSoTimeout(7000);
			} catch (SocketException e1) {
				System.err.println("Error:couldn't set socket time out");
				try {
					tempSocket.close();
				} catch (Exception e) {
					System.err.println("couldn't close connection with user!");
				}
				continue;
			}
			
			String requestLine = null;
			
			try {
				BufferedReader in = 
					new BufferedReader(new InputStreamReader(tempSocket.getInputStream()));
				requestLine = in.readLine();
			} catch (Exception e) {
				try {
					tempSocket.close();
				} catch (Exception e1) {
				}
				System.err.println("Error: couldn't get the request from user!");
				continue;
			}
			
			String uri = requestLine.split(" ")[1];
			uri=uri.replaceAll("http://", "");
			uri = uri.substring(uri.indexOf("/"));
			String fileUri = null;
			if(uri.contains("?"))
			{
				fileUri = uri.substring(0,uri.indexOf("?"));
			}else
			{
				fileUri = uri;
			}
			
			
			
			
		
		Request tempRequest = null;
		
		 try {
			tempRequest = new Request(Helpers.parameters(uri),fileUri,tempSocket);
			
		 } catch (Exception e) {
			System.err.println("Error: couldn't parse query params!");
			try {
				tempSocket.close();
			} catch (Exception e1) {
				System.err.println("couldn't close connection with user!");
			}
			continue;
		} 
		
	
			
		synchronized(requestQueue)
		{
			while(requestQueue.size() >= maxAllowed)
			{
				try {
					requestQueue.wait();
					
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			
			requestQueue.offer(tempRequest);
			requestQueue.notifyAll();	
		}
		
		}
	}
	
	
	
	/**
	 *<p>stops the socket reads.</p>
	 */
	public void stop()
	{
		working=false;
	}
	

}
