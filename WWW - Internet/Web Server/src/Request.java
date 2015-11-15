import java.net.Socket;
import java.util.Map;

public class Request {
	
	private Map<String,String> Params;
	
	private String Url;
	private Socket ClientSocket;
	
	
	Request(Map<String,String> uParams,String uUrl,Socket conn)
	{
		Params = uParams;
		Url=uUrl;
		ClientSocket = conn;
	}
	
	
	public void setUrl(String url) {
		Url = url;
	}
	
	public String getUrl() {
		return Url;
	}
	
	public void setClientSocket(Socket clientSocket) {
		ClientSocket = clientSocket;
	}
	
	public Socket getClientSocket() {
		return ClientSocket;
	}
	
	public void setParams(Map<String,String> params) {
		Params = params;
	}
	
	public Map<String,String> getParams() {
		return Params;
	}

}
