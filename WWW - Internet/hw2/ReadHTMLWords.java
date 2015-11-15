package hw2.cs236369;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Set;

public class ReadHTMLWords extends ReadWords {

	/**
	 * 
	 * <p>
	 *  The program gets a URL through standard input and outputs the following: <br />
	 * 		1- For each HTML tag how many times it has appeared. <br />
	 * 		2- An approximate evaluation of the number of HTTP Requests a browser should send upon accessing a certain URL.
	 * </p> 
	 * 
	 * 
	 * @param args arg[0] is the URL
	 */
	public static void main(String[] args) {
		HashMap<String, Integer> hashMap = hashHTML(args[0]);
		
		printHTMLHash(hashMap);
		
		System.out.println("\n\n\n\n\n\n");
		
		evaluateHTTPRequestsNumber(args[0]);
	}
	
	
	
	
	/**
	 * 
	 * @param url  String object containing the url address of an html file 
	 * @return HashMap object which maps the html tag names used in the html file to the number of times they appear in this file   
	 */
	public static HashMap<String, Integer> hashHTML(String url){
		HashMap<String, Integer> hashMap = new HashMap<String, Integer>();
		
		Scanner s = getScanner(url).useDelimiter("<");
		if (s == null)
			return null;

		String str = nextWord(s);
		while (str != null) {
			str = str.toLowerCase();
			if(str.matches("<[a-z](.|\\s)*[\\s>].*\\s*"))
			{
				int tagNum = 0;
				
				str = str.split("[ >]")[0];
				str = str.substring(1);
				if(hashMap.containsKey(str)){
					tagNum = hashMap.get(str);
				}
				tagNum++;
				hashMap.put(str, tagNum);
			}
			str = nextWord(s);
		}
		
		
		return hashMap;
	}
	
	
	/**
	 * 
	 * <p>
	 * 	The output should be valid XHTML with a table element that presents the hash map sorted alphabetically, printed to the standard output.
	 * </p>
	 * 
	 * @param hashMap object   
	 */
	public static void printHTMLHash(HashMap<String, Integer> hashMap){
		Set<String> tagSet= hashMap.keySet();
		
		Object[] tagArray = tagSet.toArray();
		Arrays.sort(tagArray);
		
		String output = "";
		
		output += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
			   +  "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
			   +  "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n"
			   +  "<head><title>Homework 2</title></head>\n"
			   +  "<body>\n"
			   +  "<table>\n";
		
		for(Object tagAsObject: tagArray)
		{
			String tag = (String) tagAsObject;
			int tagNum = hashMap.get(tag);
			output += "<tr><td>" +  tag + "</td><td>" + tagNum	+ "</td></tr>\n";
		}
		
		output += "</table>\n"
			   + "</body>\n"
			   + "</html>\n";
		
		System.out.println(output);
	}
	
	
	/**
	 * 
	 * <p>
	 * 	Prints to the standard output the number of HTTP requests that are caused upon accessing the input URL. <br /><br/>
	 *  The Algorithm: count how many times img, link, embed, iframe have appeared in the XHTML file.
	 * </p>
	 * 
	 * @param url String object containing the url address of an html file   
	 */
	public static void evaluateHTTPRequestsNumber(String url){
		HashMap<String, Integer> hashMap = hashHTML(url);
		
		int HTTPRequestsNum = 1;
		
		String[] HTMLTags = {"img", "link", "embed", "iframe"};
		
		for(String tag: HTMLTags){
			if(hashMap.containsKey(tag)){
				HTTPRequestsNum += hashMap.get(tag);
			}
		}
		
		System.out.println("\n HTTP Requests Number Evaluation: " + HTTPRequestsNum + "\n");
	}		
}