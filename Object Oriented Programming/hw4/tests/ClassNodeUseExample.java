package hw4.tests;

import hw4.xml.ClassNode;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

public class ClassNodeUseExample {

	public ClassNode genClassNode() throws TransformerException, ParserConfigurationException {
		//Creating a XML tree for a class named 'A'.
		ClassNode cn = new ClassNode("A");
		cn.addMethod("foo", void.class).	//adding a method named 'foo' to 'A'. which returns void
			addParam("p1", int.class).		//prameter addition to foo	
			addParam("p2", String.class);
		//Adding a second method named 'bar', which returns boolean
		cn.addMethod("bar", boolean.class);
		return cn;
	}
	
	public static void main(String[] args) throws TransformerException, ParserConfigurationException {
		new ClassNodeUseExample().genClassNode().generateXml(System.out);
	}
}
