import java.util.HashMap;
import org.w3c.dom.*;
import javax.xml.parsers.*;

/**
 * 
 * <p>This class parses the config.xml file. The parsed values are public. Use parse() before reading them.</p>
 *
 */
public class ParseConfigXML {	

	//<configParams>
	public static boolean parsed = false;
	public static  int 	port;
	public static String 	basePath;
	public static int socketQueueSize = 0;
	public static int requestQueueSize = 0;
	public static int socketReadersMulti = 0;
	public static int requestHandlersMulti = 0;
	public static HashMap<String, String> fileExtensionTypeHandler = new HashMap<String, String>();
	public static String welcomeFile = null;
	public static HashMap<String, String> fileExtensionMimeMapping = new HashMap<String, String>();
	//</configParams>
	
	/**
	 * <p>This function should be called before reading the PraseConfigXML public params.</p>
	 */
	public static synchronized void parse() throws Exception 
	{
		
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		factory.setValidating(true);
		factory.setIgnoringElementContentWhitespace(true);
		DocumentBuilder builder = factory.newDocumentBuilder();
		Document doc = builder.parse("config.xml");
		NodeList serverConfigList = doc.getElementsByTagName("server-config");
		
		//<Port+Base>
		Node serverConfigNode = serverConfigList.item(0);
		NamedNodeMap serverConfigNodeAttributes = serverConfigNode.getAttributes();
		port 	 = Integer.valueOf(serverConfigNodeAttributes.getNamedItem("port").getNodeValue());
		basePath = serverConfigNodeAttributes.getNamedItem("base").getNodeValue();
		//</Port+Base>
		
		NodeList configNodeList = serverConfigNode.getChildNodes();
		Node tempNode = null;
		for (int i = 0; i < configNodeList.getLength(); i++) {
			tempNode = configNodeList.item(i);
			String tempNodeName = tempNode.getNodeName();
			if(tempNodeName.equals("threads")){
				NodeList threadsNodeList = tempNode.getChildNodes();
				for (int j = 0; j < threadsNodeList.getLength(); j++) {
					NodeList threadChildList = threadsNodeList.item(j).getChildNodes();
					if(threadsNodeList.item(j).getNodeName().equals("socket-readers")){
						if(threadChildList.item(0).getNodeName().equals("multi")){
							socketReadersMulti = Integer.parseInt(threadChildList.item(0).getTextContent());
						}
					}
					if(threadsNodeList.item(j).getNodeName().equals("request-handlers")){
						if(threadChildList.item(0).getNodeName().equals("multi")){
							requestHandlersMulti = Integer.parseInt(threadChildList.item(0).getTextContent());
						}
					}
				}
			}
			else if(tempNodeName.equals("queues")){
				NodeList queuesNodeList = tempNode.getChildNodes();
				for (int j = 0; j < queuesNodeList.getLength(); j++) {
					NodeList socketRequestQueues = queuesNodeList.item(j).getChildNodes();
					if(queuesNodeList.item(j).getNodeName().equals("socket-queue")){
						if(socketRequestQueues.item(0).getNodeName().equals("size")){
							socketQueueSize = Integer.parseInt(socketRequestQueues.item(0).getTextContent());
						}
					}
					if(queuesNodeList.item(j).getNodeName().equals("request-queue")){
						if(socketRequestQueues.item(0).getNodeName().equals("size")){
							requestQueueSize = Integer.parseInt(socketRequestQueues.item(0).getTextContent());
						}
					}
				}
			}
			else if(tempNodeName.equals("type-handlers")){
				NodeList typeHandlersChildren = tempNode.getChildNodes();
				for (int j = 0; j < typeHandlersChildren.getLength(); j++) {
					String classEngineAttribute = typeHandlersChildren.item(j).getAttributes().getNamedItem("class").getNodeValue();
					if(typeHandlersChildren.item(j).getNodeName().equals("type-handler")){
						NodeList EngineExtensionList = typeHandlersChildren.item(j).getChildNodes();
						for (int k = 0; k < EngineExtensionList.getLength(); k++) {
							fileExtensionTypeHandler.put(EngineExtensionList.item(k).getTextContent(), classEngineAttribute);
						}
					}
				}
			}
			else if(tempNodeName.equals("welcome-file")){
				welcomeFile = tempNode.getTextContent();
				
			}
			else if(tempNodeName.equals("mime")){
				NodeList mimeChildrenNodeList = tempNode.getChildNodes();
				for (int j = 0; j < mimeChildrenNodeList.getLength(); j++) {
					if(mimeChildrenNodeList.item(j).getNodeName().equals("mime-mapping")){
						String extension = null;
						String mimeType = null;
						NodeList mimeMappingChildren = mimeChildrenNodeList.item(j).getChildNodes();
						for (int k = 0; k < mimeMappingChildren.getLength(); k++) {
							
							if(mimeMappingChildren.item(k).getNodeName().equals("extension")){
								extension = mimeMappingChildren.item(k).getTextContent();
							}
							else if(mimeMappingChildren.item(k).getNodeName().equals("mime-type")){
								mimeType = mimeMappingChildren.item(k).getTextContent();
							}
							
						}
						fileExtensionMimeMapping.put(extension, mimeType);
					}
				}
			}
			else{
				System.err.println("ERROR in parsing");
			}

		}		
	}
}
