import java.io.File;
import java.io.IOException;
import java.net.Socket;
import java.util.Queue;
import org.apache.http.HttpResponse;
import org.apache.http.ProtocolVersion;
import org.apache.http.entity.FileEntity;
import org.apache.http.message.BasicHttpResponse;


public class requestHandlerThread implements Runnable{
	
	private Queue<Request> requestQueue;
	private Boolean working = true;
	private final String basePath;
	
	/**
	 * @param sreq requests queue that the request handler thread polls the requests from.
	 * @param _basePath the base path of the server.
	 */
	requestHandlerThread(Queue<Request> sreq , String _basePath)
	{
		requestQueue = sreq;
		basePath = _basePath;
	}
	
	/**
	 * <p>the main function of the request handler.</p>
	 * <p>runs the request handler</p>
	 */
	public void run()
	{
		while(working)
		{
			Request req =null;
			synchronized(requestQueue)
			{
				while(requestQueue.size() <= 0){
				try {
					requestQueue.wait();
				} catch (InterruptedException e) {
				}
				}
				
				 req = requestQueue.poll();
				 requestQueue.notifyAll();
			}
			
				String filePath =req.getUrl();
				
				try{
					
					ParseConfigXML.parse();
				
					}catch(Exception e){
						System.err.println("Error: couldn't parse the config xml file!");
						try {
						req.getClientSocket().close();
						} catch (IOException e1) {
						}
					continue;
					}
				
				
				
				//if there is no file path , so let the file path point to welcomeFile.
				if(filePath.equals("/"))
				{
					filePath = "/"+ParseConfigXML.welcomeFile.trim();
				}
				
				

				String[] temp = filePath.split("\\.");
				String handlerClass = ParseConfigXML.fileExtensionTypeHandler.get(temp[temp.length-1]);
				Socket csocket = req.getClientSocket();
				
				
				if(filePath.matches(".*/"))
				{
					//if the file path points to Directory , return with error message.
					
					HttpResponse response = Helpers.getHtmlResponse("You are not authorized to view the folder's content", 401, "Unauthorized");
					Helpers.printResponseToSocket(response, csocket);
					try {
						csocket.close();
					} catch (Exception e) {
			
					}
					continue;
					
				}
				
				
				File file = new File(basePath+filePath);
				
				String realPath = null;
				
				try {
					 realPath = file.getCanonicalPath().toString();
				} catch (IOException e2) {
					realPath = basePath+filePath;
				}
				
				//if the file is not in the servers folder (or sub folder) so we will not allow access to it.
				if(!realPath.toLowerCase().startsWith(basePath.toLowerCase()))
				{
					HttpResponse response = Helpers.getHtmlResponse("You are not authorized to access this file!", 401, "Unauthorized");
					Helpers.printResponseToSocket(response, csocket);
					try {
						csocket.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
					continue;
				}
				
				
				if(!file.exists())
				{
					
					HttpResponse response = Helpers.getHtmlResponse("File not found", 404, "File not found");
					Helpers.printResponseToSocket(response, csocket);
					try {
						csocket.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
					continue;
				}
				
				
				if(handlerClass == null)
				{
				
				String mimetype = ParseConfigXML.fileExtensionMimeMapping.get(temp[temp.length-1]);
				
				//we don't deal with files that we don't know their type , so we return that it is not found.
				if(mimetype == null){
					HttpResponse response = Helpers.getHtmlResponse("File not found", 404, "File not found");
					Helpers.printResponseToSocket(response, csocket);
					try {
						csocket.close();
					} catch (IOException e) {
					}
					continue;
					
				}
	
				HttpResponse response = new BasicHttpResponse(new ProtocolVersion("HTTP",1,1),200,"OK");
				org.apache.http.protocol.HttpDateGenerator dateGenerator = new org.apache.http.protocol.HttpDateGenerator(); 
				response.addHeader("Date", dateGenerator.getCurrentDate());
				response.addHeader("Connection", "close");
				response.addHeader("Content-Type",mimetype);
				response.addHeader("Content-Length", String.valueOf(file.length()));
				response.setEntity(new FileEntity(file, mimetype));
				Helpers.printResponseToSocket(response, csocket);
				try {
					csocket.close();
				} catch (Exception e) {
				}
				
				}else
				{

					try{
					//load specific type Handler
				    Class<?> hndlClass = Class.forName(handlerClass);
				    TypeHandler hndlr = (TypeHandler) hndlClass.newInstance();
				    hndlr.handle(basePath+req.getUrl(),req.getParams(),csocket.getOutputStream());
					
					
					csocket.close();
						
					} catch (Exception e) {
						System.err.println("Error while proccessing request with a special handler");
					
						try {
							csocket.close();
						} catch (IOException e1) {
						
						}
						
					}
				}
				
			}
	}
	
	public void stop()
	{
		working=false;
	}

}
