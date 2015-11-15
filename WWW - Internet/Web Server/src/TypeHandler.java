import java.io.OutputStream;
import java.util.Map;

/**
 * 
 *  <p>A class that is implemented by any type handler in the web server for example a TSPEngine type
 *      handler.</p>	   
 *
 */
public interface TypeHandler 
{
	/**
	 * <p>Handle the requestedPath and output the XHTML result to the out.</p>
	 * 
	 * @param requestedPath: the requested page to be opened and handled. 
	 * @param queryParams: query string Params that can be used by a TSP page. 
	 * @param out: where the handle should output 
	 */
	void handle(String requestedPath, Map<String, String> queryParams, OutputStream out);
}
