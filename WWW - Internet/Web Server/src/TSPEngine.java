
import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Map;
import org.apache.http.Header;
import org.apache.http.HeaderIterator;
import org.apache.http.HttpResponse;
import org.apache.http.HttpVersion;
import org.apache.http.ParseException;
import org.apache.http.StatusLine;
import org.apache.http.entity.StringEntity;
import org.apache.http.message.BasicHttpResponse;
import org.apache.http.util.EntityUtils;


/**
 * 
 * <p>This class is used to run TSP files.</p>
 *
 */
public class TSPEngine implements TypeHandler 
{
	static int j 		= 0;
	static String lock  = new String("justalock");
	
	
	
	/**
	 * EXCEPTION
	 */
	private static class CompilationError extends Throwable{
		private static final long serialVersionUID = 1L;
		
	}

	
	/**
	 * <p>Helper method, compiles and runs the TSP and return it as a runnableTsp which returns the result</p>
	 * 
	 * @param tspCode
	 * @param queryParams
	 * @param out
	 * @return
	 * @throws Exception
	 * @throws CompilationError 
	 */
	public static runnableTsp handleHelper(String tspCode, Map<String, String> queryParams, PrintStream out) throws Exception, CompilationError 
	{
		int i=0;
		
		synchronized(lock)
		{
			i = j;
			j++;
		}
		
		String newClassName = "tspClass" + i;	//to solve concurrency issues of more than one thread
		String javaCode  = "import java.util.Map; \n" + 
					       "import java.io.PrintStream; \n" +
					       "import java.util.HashMap;\n" + 
						   "public class " + newClassName +" implements runnableTsp{ \n" +
									"private PrintStream out;\n"+
									"private Map params;\n" +
									"public void run(){\n";		
		javaCode 		+= 			tspToJava(tspCode);
		javaCode 		+= 			"}		\n" +
									"public void setOutAndParams(PrintStream out, Map<String, String> params){\n" +
										"this.params = params;" + 
										"this.out = out;" +
									"}" +
							"}";
		
		File javaFile = new File("bin\\" + newClassName + ".java");
	    FileWriter fwriter = new FileWriter(javaFile);
	    fwriter.write(javaCode);    
	    fwriter.close();
	    
	    Process compileProc = Runtime.getRuntime().exec("javac -classpath . " + "bin\\" + newClassName + ".java");
	    compileProc.waitFor(); //Wait for the process to terminate
	    if(compileProc.exitValue()!=0) {
	      System.err.println("Compile exit status: " + compileProc.exitValue());
	      System.err.println("Compile error:");
	      printStream(compileProc.getErrorStream());
	      javaFile.delete();
	      new File("bin\\" + newClassName  + ".class").delete();
	      throw new CompilationError();
	    }
	    
	    Class<?> tspClass = Class.forName(newClassName);
	    
	    javaFile.delete();
	    new File("bin\\" + newClassName  + ".class").delete();
	    
	    runnableTsp engine = (runnableTsp)(tspClass.newInstance());

	    engine.setOutAndParams(out, queryParams);
	    return engine;
	}
	
	
	/**
	 * <p>Helping function.</p>
	 * 
	 * @param stream
	 * @throws IOException
	 */
	private static void printStream(InputStream stream) throws IOException {
		byte read = 0;
		while((read=(byte)stream.read())>=0) {
			System.err.print((char)read);
		}      
	}


	/**
	 * <p>Handles a TSP page, and outputs the result (headers + content) to the outStream.</p>
	 */
	@Override
	public void handle(String requestedPath, Map<String, String> queryParams, OutputStream outStream)
	{
		String tspCode = null;
		String result = null;
		
		PrintWriter out = new PrintWriter(outStream);

		try {
			tspCode = readFileAsString(requestedPath);
			ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
			PrintStream stringOutputStream = new PrintStream(byteArrayOutputStream);
			runnableTsp engine = handleHelper(tspCode, queryParams, stringOutputStream);
			engine.run();
			result = generateStringHttpResponse(byteArrayOutputStream.toString("utf-8"), "OK", 200);
		}
		catch(FileNotFoundException e){
			System.err.println("ERROR: file " + requestedPath +  " wasn't found");
			String reasonPhrase = "Not Found";
			int statusCode = 404;
			String fileNotFoundHtml = Helpers.generateHtmlPage(statusCode, reasonPhrase, "Requested file " + requestedPath + " wasn't found");
			try {
				result = generateStringHttpResponse(fileNotFoundHtml, reasonPhrase, statusCode);
			} catch (ParseException e1) {
				e1.printStackTrace();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}
		catch (Throwable e) {
			e.printStackTrace();
			System.err.println("ERROR: handle() failed - compile error.");
			String reasonPhrase = "Internal Server Error";
			int statusCode = 500;
			String fileNotFoundHtml = Helpers.generateHtmlPage(statusCode, reasonPhrase, "ERROR in compiling " + requestedPath);
			try {
				result = generateStringHttpResponse(fileNotFoundHtml, reasonPhrase, statusCode);
			} catch (Exception e1) {
				System.err.println("ERROR in generating response to client.");
				e1.printStackTrace();
			}
		} 
		
		out.print(result);
		out.flush();
	}
	
	
	/**
	 * <p>Convert a file to string.</p>
	 * 
	 * @param filePath
	 * @return
	 * @throws java.io.IOException
	 */
	private static String readFileAsString(String filePath) throws java.io.IOException, FileNotFoundException{
		if(filePath == null){
			throw new FileNotFoundException(); 
		}
		File file = new File(filePath);
		if(!file.exists()){
			throw new FileNotFoundException();
		}
	    byte[] buffer = new byte[(int) file.length()];
	    
	    BufferedInputStream f = new BufferedInputStream(new FileInputStream(filePath));
	    f.read(buffer);
	    return new String(buffer);
	}
	
	
	/**
	 * <p>Takes a TSP code and converts it into a valid Java code.</p>
	 * 
	 * @param tsp a TSP string
	 * @return the java code to insert in a method
	 */
	public static String tspToJava(String tsp)
	{
		String javaCode = "";
		
		String[] tspSplitted = tsp.split("<%");		// tspSplitted[0] <% tspSplitted[1] <% tspSplitted[2] <% ...
		if(tspSplitted.length <= 1){
			return "out.print(\"" + tsp + "\");";
		}
		
		//<tspSplitted[0]>
		if(!(tspSplitted[0].equals("") || tspSplitted[0].matches("[\r\n\f\b\t]*")  )){
			javaCode += "out.print(\"" + tspSplitted[0].replace("\\", "\\\\").replace("\"", "\\\"").replaceAll("[\r\n]*", "")  + "\");";
		}
		//</tspSplitted[0]>
		
		for (int i = 1; i < tspSplitted.length; i++) {
			String[] javaCodeAndHtml = tspSplitted[i].split("%>");
			String tspCodeTag = javaCodeAndHtml[0]; // <% tspCodeTag %>
			javaCode += tspCodeTag + "\n";
			if(javaCodeAndHtml.length > 1){
				String tspHtml = javaCodeAndHtml[1];	// <% ... %> tspHtml <% ...
				if(!(tspHtml.equals("") || tspHtml.matches("[\r\n\f\b\t]*")  ))
				{
					javaCode += "out.print(\"" + tspHtml.replace("\\", "\\\\").replace("\"", "\\\"").replaceAll("[\r\n]*", "") + "\");";
				}
			}
		}
		return javaCode;
	}

	
	/**
	 * <p>Generate an HttpResponse to a client. if the content is string use: new StringEntity(String content);</p>
	 * <p>
	 * 		http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html#sec10
	 * 		200:OK
	 * 		401:Unauthorized
	 * 		404:Not Found
	 * 		500:Internal Server Error
	 * </p>
	 * 
	 * @param content: if an error happens send a stringEntity with error message only 
	 * @param ReasonPhrase
	 * @param StatusCode
	 * @return
	 * @throws IOException 
	 * @throws ParseException 
	 */
	private String generateStringHttpResponse(String content, String reasonPhrase, int statusCode) throws ParseException, IOException
	{
		//<addStatusLine>
		HttpResponse result = new BasicHttpResponse(HttpVersion.HTTP_1_1, statusCode, reasonPhrase);
		//</addStatusLine>
		
		//<addContent>
		result.setEntity(new StringEntity(content));
		result.removeHeaders("Content-Length");
		result.removeHeaders("Content-Type");
		//</addContent>
		
		//<addHeaders>
		org.apache.http.protocol.HttpDateGenerator dateGenerator = new org.apache.http.protocol.HttpDateGenerator(); 
		result.addHeader("Date", dateGenerator.getCurrentDate());
		result.addHeader("Connection", "close");
		result.addHeader("Content-Type", "text/html");
		result.addHeader("Content-Length", String.valueOf(content.length()));
		//</addHeaders>
		
		return HttpResponseToString(result);
	}

	
	/**
	 * <p>convert an HttpResponse to a String</p>
	 * 
	 * @param httpResponse
	 * @return
	 * @throws ParseException
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
}
