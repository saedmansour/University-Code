package development;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class FileParser {

	private File 	file;
	private Scanner fileScanner;
	private String  fileLine;
	
	public FileParser(String filePath) {
		file 		 = new File(filePath);
		try {
			fileScanner  = new Scanner(file);
		} catch (FileNotFoundException e) {
			System.err.println("ERROR: file " + filePath + " not found.");
			e.printStackTrace();
		}
	}
	
	public String getNextLine(){
		if(fileScanner.hasNext()){
			fileLine = fileScanner.nextLine();
			return fileLine;
		}
		return null;
	}
	
	protected void finalize() throws Throwable
	{
	  fileScanner.close();
	  super.finalize(); //not necessary if extending Object.
	} 
}
