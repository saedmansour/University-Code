
//------Import--------------------------------------------------------------------------------
import java.io.*;
import java.util.*;
//-----/Import---------------------------------------------------------------------------------


//------Class Color Replace--------------------------------------------------------------------
/**
 * 	<p>Input = HTML page => output = HTML page with colors(any tag that carries a color) randomly replaced.</p>
 *	
 */
public class ColorReplace 
{
	//---Private Fields---------------------------
	private static String[] colorsArray	= new String[]{"Peru","Pink","Red","Yellow","Blue","YellowGreen","Darkorange","Aquamarine","Aqua"};
	private static String[] colorsReplacment;
	
	
	
	
	//---Public Functions-------------------------
	/**
	 * <p>The "main" function of the class. Replaces the colors in an HTML page.</p>
	 * 
	 * @param begore the HTML page prior to the color replacement.
	 * @return String the HTML page with colors replaced.
	 */
	public static String replaceColors(String before) throws FileNotFoundException, IOException
	{
		String after = before;
		 Properties props = new Properties();
		 props.load(new FileInputStream("proxy.properties"));
		 String[] colorsToReplace =  props.getProperty("proxy.colors").split("\\s");
		 colorsReplacment =  new String[colorsToReplace.length];
		 for(int i=0;i<colorsReplacment.length;i++)
		 {
			 colorsReplacment[i]=getRandomColor();
		 }
		 
		 for(int i=0;i<colorsReplacment.length;i++)
		 {
			 after = after.replaceAll("color:(\\s?)"+colorsToReplace[i], "color:"+colorsReplacment[i]);
			 after = after.replaceAll("color='(\\s?)"+colorsToReplace[i], "color='"+colorsReplacment[i]);
			 after = after.replaceAll("color=\"(\\s?)"+colorsToReplace[i], "color=\""+colorsReplacment[i]);
		 }
		 return after;
	}

	
	
	
	//---Private Functions------------------------
	
	/**
	 * <p>returns a random color</p>
	 * 
	 * @return string returns a random color
	 */
	private static String getRandomColor()
	{
		Random generator = new Random();
		int value = generator.nextInt();
		if(value < 0) {value  = -value;}
		return colorsArray[(value%colorsArray.length)];
	}

}
