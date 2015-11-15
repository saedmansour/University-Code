package development;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;


public class FileWrite {

	private BufferedWriter out = null;
	
	public FileWrite(String filePath) {
		try {
			out = new BufferedWriter(new FileWriter(filePath));
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}
	
	public void write(String output){
		try {
			out.write(output);
		} catch (IOException e) {
			System.err.println("Writing to file failed");
			e.printStackTrace();
		}
	}
	
	public void writeLine(String output){
		write(output + "\n");
	}
}
