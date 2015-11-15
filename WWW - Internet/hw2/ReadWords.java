package hw2.cs236369;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.util.Scanner;

/**
 * <p>
 * The ReadWords class is a very simple class. Given a URL which points to an
 * HTML file, all it does is reading the file and writing to the standard output
 * all the words (tokens) in this file, using the symbol &lt; as a delimiter a
 * word in each line. The class uses the <a
 * href="http://java.sun.com/j2se/1.5.0/docs/api/java/util/Scanner.html"
 * >Scanner</a> class.
 * </p>
 * 
 * @version March 2010
 * @author IIT - CS Faculty, Course 236369 staff
 * 
 */

public class ReadWords {

	/**
	 * <p>
	 * The nextWord method returns the next word in the Scanner object passed as
	 * a parameter.
	 * </p>
	 * 
	 * @param s
	 *            The Scanner to be used.
	 * @return The next word.
	 */
	public static String nextWord(Scanner s) {
		if (s.hasNext())
			return ("<" + s.next());
		return null;
	}

	/**
	 * <p>
	 * This method constructs a new Scanner for the HTML file pointed by the URL
	 * given as a parameter.
	 * </p>
	 * <p>
	 * We define the User-Agent HTTP header for the connection object to imitate
	 * FireFox 3.6
	 * </p>
	 * 
	 * @param urlAddress
	 *            The URL for the Scanner object - assumed to be an HTML file.
	 * @return The Scanner object.
	 */
	protected static Scanner getScanner(String urlAddress) {
		try {
			if (urlAddress != null) {
				String userAgent = "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.2) Gecko/20100115 Firefox/3.6 (.NET CLR 3.5.30729)";
				URLConnection connection = new URL(urlAddress).openConnection();
				connection.setRequestProperty("User-agent", userAgent);
				return new Scanner(connection.getInputStream());
			} else
				return null;
		} catch (IOException e) {
			System.err.println("Couldn't get" + urlAddress);
			return null;
		}
	}

	/**
	 * <p>
	 * The printWords method prints the tokens in the URL address given to it,
	 * using a scanner object with &lt; symbol as a delimiter. Makes use of the
	 * <i>getScanner</i> method.
	 * </p>
	 * 
	 * @param urlAddress
	 *            The URL address to be parsed - assumed to be an HTML file.
	 */

	public static void printWords(String urlAddress) {
		Scanner s = getScanner(urlAddress).useDelimiter("<");
		if (s == null)
			return;

		String str = nextWord(s);
		while (str != null) {
			System.out.println(str);
			str = nextWord(s);
		}
	}

	public static void main(String[] args) {
		if (args.length < 1) {
			System.err.println("Usage: java ReadWords URL_Address");
			return;
		}
		ReadWords.printWords(args[0]);
	}
}