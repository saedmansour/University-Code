package development;
import java.io.StringReader;
import java.net.Socket;
import java.net.URLEncoder;
import java.util.HashMap;

import org.w3c.dom.*;
import org.xml.sax.*;
import javax.xml.parsers.*;

import org.apache.http.HttpHost;
import org.apache.http.HttpResponse;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.DefaultHttpClientConnection;
import org.apache.http.message.BasicHttpEntityEnclosingRequest;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpParams;
import org.apache.http.protocol.BasicHttpContext;
import org.apache.http.protocol.BasicHttpProcessor;
import org.apache.http.protocol.ExecutionContext;
import org.apache.http.protocol.HttpContext;
import org.apache.http.protocol.HttpRequestExecutor;
import org.apache.http.protocol.RequestContent;
import org.apache.http.protocol.RequestTargetHost;
import org.apache.http.util.EntityUtils;


public class MorphTagger {
	static public HashMap<String, String> tags = new HashMap<String, String>();
	
	public static void main(String[] args){
		TaggedWord[] t  = hebrewPOSTagging("הילד גדול");
		for (int i = 0; i < t.length; i++) {
			System.out.println(t[i].tag);
		}
	}
	
	public static TaggedWord[] getPOStag(String text, Language language){
		if(language == Language.HEBREW){
			return hebrewPOSTagging(text);
		} else if (language == Language.ARABIC) {
			return arabicPOSTagging(text);
		}
		return null;
	}
	
	public static TaggedWord[] arabicPOSTagging(String text)
	{
		//return POSTagging("svmara",text);
		return POSTagging("morph",text);
	}
	

	public static TaggedWord[] hebrewPOSTagging(String text)
	{
		
		String[][] res = null;
		try {
			res = AdvancedHebMorphAnalyzer(text);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		TaggedWord[] finalRes = new TaggedWord[res.length];
		for(int i=0;i<res.length;i++)
		{
				finalRes[i] = new TaggedWord(res[i][0], stringToTag(res[i][1]));
		}
		return finalRes;
	}
	
	
	
	private  static TaggedWord[] POSTagging(String choice , String text)
	{
		
		String[][] res = getRes(choice,text);
		TaggedWord[] finalRes = new TaggedWord[res.length];
		for(int i=0;i<res.length;i++)
		{
				finalRes[i] = new TaggedWord(res[i][0], stringToTag(res[i][1]));
		}
		return finalRes;
	}
	
	private static String[][] getRes(String choice,String text)
	{
	
		String[][] finalRes=null;
		
		try {
			String result = MorphTagger.makePost(choice, text);
			//System.out.println(result);
			String[] resultSet = result.split("</tr><tr>");
			finalRes = new String[resultSet.length-1][2];
			//System.out.println("the printing("+resultSet.length+"):");
			for(int i=1;i<resultSet.length;i++)
			{
				if(i==(resultSet.length-1)){resultSet[i] = resultSet[i].split("</tr>")[0];}
				
				String[] curr = resultSet[i].split("</td><td>");
				finalRes[i-1][0] = curr[0].replaceAll("<td>", "");
				finalRes[i-1][1] =  curr[3].replaceAll("</td>","");		
			}

		} catch (Exception e) {
			e.printStackTrace();
		}	
		
		return finalRes;
	}
	

	
	private  static String makePost(String choice ,String text) throws Exception 
	{
		  BasicHttpProcessor httpproc = new BasicHttpProcessor();
	      // Required protocol interceptors
	      httpproc.addInterceptor(new RequestContent());
	      httpproc.addInterceptor(new RequestTargetHost());
	      HttpRequestExecutor httpexecutor = new HttpRequestExecutor();
	      HttpContext context = new BasicHttpContext();
		          
		  HttpHost host = new HttpHost("www.mila.cs.technion.ac.il",80);

		  DefaultHttpClientConnection myconn = new DefaultHttpClientConnection();

		  context.setAttribute(ExecutionContext.HTTP_CONNECTION, myconn);
		  context.setAttribute(ExecutionContext.HTTP_TARGET_HOST, host);
	      
		  Socket tempsocket = new Socket(host.getHostName(), host.getPort());
		  HttpParams myparams = new BasicHttpParams();
		  myconn.bind(tempsocket, myparams);
          //BasicHttpRequest request = new BasicHttpRequest("GET","http://www.mila.cs.technion.ac.il/Arabic/tagger.pl");
          BasicHttpEntityEnclosingRequest request = new BasicHttpEntityEnclosingRequest("POST","http://www.mila.cs.technion.ac.il/Arabic/tagger.pl"); 
          String reqcontent = "choice="+choice+"&corpus="+URLEncoder.encode(text,"UTF-8");
          request.addHeader("Content-Type", "application/x-www-form-");
         // request.addHeader("Content-Length",reqcontent.length()+"");
          request.setEntity(new StringEntity(reqcontent));
          request.setParams(myparams);
          httpexecutor.preProcess(request, httpproc, context);
          HttpResponse response = httpexecutor.execute(request, myconn, context);
          response.setParams(myparams);
          httpexecutor.postProcess(response, httpproc, context);
     
          return EntityUtils.toString(response.getEntity()).replaceAll("\\s+", "");
     
	}
	
	public static String[][] hebRootLetters(String text) throws Exception
	{
	    Node document =AdvancedMorpholyzerAsXml(text);
		NodeList nds = document.getChildNodes();
		String[][] finalRes = new String[nds.getLength()][2];
        for(int i=0;i<nds.getLength();i++)
        {
        	Node curr = nds.item(i);
        	finalRes[i][0] = curr.getAttributes().item(1).getTextContent();
        	int k=0;
        	NodeList analyses = curr.getChildNodes();
        	double maxProbab = 0;
        	//int maxInd = 0;
        	for(int t=0;t<analyses.getLength();t++)
        	{
        		double probab = Double.parseDouble(analyses.item(t).getAttributes().item(1).getTextContent());
        		if(probab >maxProbab)
        		{
        			maxProbab = probab;
        		//	maxInd = t;
        		}
        	}
        	
        	
        	Node temp;
        	//(?+?);
        	int counter = 0;
        	do{
        		temp = analyses.item(k).getChildNodes().item(counter);
        		counter++;
        	}while(!temp.hasChildNodes() && counter < analyses.item(k).getChildNodes().getLength());
        	
        	temp = temp.getChildNodes().item(0);
        	if(temp != null && temp.getAttributes().getNamedItem("root") != null)
        	{
        		finalRes[i][1] = temp.getAttributes().getNamedItem("root").getTextContent();
        	}else
        	{
        		finalRes[i][1] = finalRes[i][0];
        	}
        }
        
       

		return finalRes;
	}
	
	public static String[][] AdvancedHebMorphAnalyzer(String text) throws Exception
	{

	    Node document =AdvancedMorpholyzerAsXml(text);
		NodeList nds = document.getChildNodes();
		String[][] finalRes = new String[nds.getLength()][2];
        for(int i=0;i<nds.getLength();i++)
        {
        	Node curr = nds.item(i);
        	finalRes[i][0] = curr.getAttributes().item(1).getTextContent();
        	int k=0;
        	NodeList analyses = curr.getChildNodes();
        	double maxProbab = 0;
        	//int maxInd = 0;
        	for(int t=0;t<analyses.getLength();t++)
        	{
        		double probab = Double.parseDouble(analyses.item(t).getAttributes().item(1).getTextContent());
        		if(probab >maxProbab)
        		{
        			maxProbab = probab;
        	//		maxInd = t;
        		}
        	}
        	
        	Node temp;
        	//(?+?);
        	int counter = 0;
        	do{
        		temp = analyses.item(k).getChildNodes().item(counter);
        		counter++;
        	}while(!temp.hasChildNodes() && counter < analyses.item(k).getChildNodes().getLength());
        	
        	temp = temp.getChildNodes().item(0);
        	if(temp != null)
        	{
        		finalRes[i][1] = temp.getNodeName();
        	}else
        	{
        		finalRes[i][1] = finalRes[i][0];
        	}
        	
        }
        
       

		return finalRes;
	}
	
	
	
	public static Node AdvancedMorpholyzerAsXml(String text) throws Exception
	{
		DocumentBuilderFactory dbf =   DocumentBuilderFactory.newInstance();
	    DocumentBuilder builder = dbf.newDocumentBuilder();

	    String resultContainer = AdvancedMorphAnlyzerPost(text);	
		InputSource is = new InputSource();

        is.setEncoding("UTF-8");
        is.setCharacterStream(new StringReader(resultContainer));
     
        
        Node document = builder.parse(is);
        document =  document.getChildNodes().item(0);
        document =  document.getChildNodes().item(0);
        document =  document.getChildNodes().item(0);
        document =  document.getChildNodes().item(0);
        return document;
	}
	
	public static String AdvancedMorphAnlyzerPost(String text) throws Exception
	{
		 BasicHttpProcessor httpproc = new BasicHttpProcessor();
	      // Required protocol interceptors
	      httpproc.addInterceptor(new RequestContent());
	      httpproc.addInterceptor(new RequestTargetHost());
	      HttpRequestExecutor httpexecutor = new HttpRequestExecutor();
	      HttpContext context = new BasicHttpContext();
		          
		  HttpHost host = new HttpHost("yeda.cs.technion.ac.il",8088);

		  DefaultHttpClientConnection myconn = new DefaultHttpClientConnection();

		  context.setAttribute(ExecutionContext.HTTP_CONNECTION, myconn);
		  context.setAttribute(ExecutionContext.HTTP_TARGET_HOST, host);
	      
		  Socket tempsocket = new Socket(host.getHostName(), host.getPort());
		  HttpParams myparams = new BasicHttpParams();
		  myconn.bind(tempsocket, myparams);
         BasicHttpEntityEnclosingRequest request = new BasicHttpEntityEnclosingRequest("POST","/XMLHmmTagger/processAnalyzerXML.jsp"); 
         String reqcontent = "bsubmit="+URLEncoder.encode("Tag to screen","UTF-8")+"&input_text="+URLEncoder.encode(text,"UTF-8");
         request.addHeader("Content-Type", "application/x-www-form-urlencoded");
        // request.addHeader("Content-Length",reqcontent.length()+"");
         request.setEntity(new StringEntity(reqcontent));
         request.setParams(myparams);
         httpexecutor.preProcess(request, httpproc, context);
         HttpResponse response = httpexecutor.execute(request, myconn, context);
         response.setParams(myparams);
         httpexecutor.postProcess(response, httpproc, context);
    
         return EntityUtils.toString(response.getEntity())/*.replaceAll("\\s+", "")*/;
	
	}
	
	public static Tag stringToTag(String str)
	{
		tags.put(str, str);
		
		str = str.toLowerCase();
		
		if(str.matches(".*conjunction.*") || str.matches(".*preposition.*") || str.matches(".*particle.*") || 
				str.matches(".*determiner.*") || str.matches(".*interjection.*") || str.matches(".*interrogative.*") ||
				str.matches(".*quantifier.*") || str.matches(".*participle.*"))
		{
			return Tag.HELPER_WORD;
		}
		if(str.matches(".*adverb.*"))
		{
			return Tag.ADVERB;
		}
		if(str.matches(".*adjective.*"))
		{
			return Tag.ADJECTIVE;
		}
		if(str.matches(".*numeral.*") || str.matches(".*Number.*"))
		{
			return Tag.NUMBER;
		}
		if(str.matches(".*pronoun.*") || str.matches(".*relativepronoun.*") || str.matches(".*personalpronoun.*") )
		{
			return Tag.PRONOUN;
		}
		if(str.matches(".*verb.*"))
		{
			return Tag.VERB;
		}
		if(str.matches(".*noun.*") || str.matches(".*propernoun.*") || str.matches(".*properName.*") ||  str.matches(".*nounplural.*"))
		{
			return Tag.NOUN;
		}
		return Tag.UNKNOWN;
	}
}

