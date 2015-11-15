import java.io.PrintStream;
import java.util.Map;

/**
 * <p>This interface is used for TSPEngine class. And is used for the compiled TSP files.</p>
 * 
 */
public interface runnableTsp {
	
	/**
	 * <p>Runs the TSP and outputs the content of a TSP page. </p> 
	 */
	void run();
	
	/**
	 * <p>Sets the out and params variables that can be used in a TSP page. </p>
	 * 
	 * @param out
	 * @param queryParams
	 */
	void setOutAndParams(PrintStream out, Map<String, String> queryParams);
}
