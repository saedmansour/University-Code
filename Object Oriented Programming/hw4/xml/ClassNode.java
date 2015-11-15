package hw4.xml;

import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;


public class ClassNode {
	public enum AMBIGUITY_TYPE {
		inherited, coincident, none
	}

	final String name;
	
	final List<MethodNode> methods = new ArrayList<MethodNode>();
	
	Document doc;
			
	public class MethodNode implements XMLConvertable{
		final String name;
		final List<ParamNode> parameters = new ArrayList<ParamNode>();
		final Class<?> returnType;
		AMBIGUITY_TYPE ambiguityType = AMBIGUITY_TYPE.none;
		
		class ParamNode implements XMLConvertable {
			final String name;
			final Class<?> type;
			
			protected ParamNode(String name, Class<?> type){
				this.name = name;
				this.type = type;
			}
			
			@Override
			public Node addToDoc(Document doc) {
				Element ret = doc.createElement("param");
				ret.setAttribute("name", this.name);
				ret.setAttribute("type", this.type.getName());
				return ret;
			}
		}
		
		private Node makeReturnNode(Document doc) {
			Element ret = doc.createElement("return");
			ret.setAttribute("type", returnType.getName());
			return ret;
		}
		
		protected MethodNode(String name, Class<?> returnType ){
			this.name = name;
			this.returnType = returnType;
		}
		
		public MethodNode addParam(String name, Class<?> type){
			ParamNode ret = new ParamNode(name, type);
			parameters.add(ret);
			return this;
		}
		
		public MethodNode addAmbiguityType(AMBIGUITY_TYPE type){
			this.ambiguityType = type;
			return this;
		}

		@Override
		public Node addToDoc(Document doc) {
			Element ret = doc.createElement("method");
			ret.setAttribute("name", name);
			for (ParamNode	param : parameters)
				ret.appendChild(param.addToDoc(doc));
			if ( ambiguityType != AMBIGUITY_TYPE.none )
				ret.setAttribute( "ambiguity", ambiguityType.toString() );
			ret.appendChild(makeReturnNode(doc));
			return ret;
		}

	}
	
	public ClassNode(String name) throws ParserConfigurationException{
		doc = DocumentBuilderFactory.newInstance().newDocumentBuilder()
		.newDocument();
		DocumentBuilderFactory dbfac = DocumentBuilderFactory.newInstance();
		DocumentBuilder docBuilder = dbfac.newDocumentBuilder();
		doc = docBuilder.newDocument();
		this.name = name;
	}
	
	public MethodNode addMethod(String name, Class<?> returnType){
		MethodNode newNode = new MethodNode(name, returnType);
		methods.add(newNode);
		return newNode;
	}

	/**
	 * Appends the node representing the underlaying object to the given DOM document
	 */
//	@Override
	private Node addToDoc(Document doc) {
		Element rootNode = doc.createElement("class");
		Element methodsNode = doc.createElement("methods");
		rootNode.setAttribute("name", name);
		rootNode.appendChild(methodsNode);
		for (MethodNode method : methods)
			methodsNode.appendChild(method.addToDoc(doc));
		doc.appendChild(rootNode);
		return rootNode;
	}

	public void generateXml(OutputStream out) throws TransformerException {
		this.addToDoc(doc);
		// set up a transformer
		TransformerFactory transfac = TransformerFactory.newInstance();
		Transformer trans = transfac.newTransformer();
		trans.setOutputProperty(OutputKeys.INDENT, "yes");
		// create string from xml tree
		StreamResult result = new StreamResult(out);
		DOMSource source = new DOMSource(doc);
		trans.transform(source, result);
	}
	
}
