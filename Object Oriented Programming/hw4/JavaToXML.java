package hw4;

import hw4.xml.ClassNode;
import hw4.xml.ClassNode.AMBIGUITY_TYPE;
import hw4.xml.ClassNode.MethodNode;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.w3c.dom.Document;


public class JavaToXML {
	
	Document doc;
	
	public JavaToXML() throws ParserConfigurationException {
		doc = DocumentBuilderFactory.newInstance().newDocumentBuilder()
		.newDocument();
	}
	
	private static LinkedList<Class<?>> getAllInterfaces(Class<?> c)
	{
		LinkedList<Class<?>> 	classes 			= new LinkedList<Class<?>>();
		
		Class<?> parent = c;
		while (parent != null)
		{	
			Class<?>[] parentInterfaces = parent.getInterfaces();
			for (Class<?> parentInterface : parentInterfaces)
			{	
				Class<?> tempInterface = parentInterface; 
				while (tempInterface != null)
				{
					classes.add(tempInterface);
					
					Class<?>[] tempInterfaceArray = tempInterface.getInterfaces();
					
					if(tempInterfaceArray.length == 0)
					{
						tempInterface = null;
					}
					else
					{
						tempInterface = tempInterfaceArray[0];
					}
				}
			}
			parent = parent.getSuperclass();
		}			
		return classes; 	
	} 
	
	private static Class<?>[] getAllParents(Class<?> c)
	{
		LinkedList<Class<?>> 	classes 			= new LinkedList<Class<?>>();
		Class<?> 				parent				= c.getSuperclass();
		while (parent != null)
		{	
			classes.add(parent);
			parent = parent.getSuperclass();
		}
		
		classes.addAll(getAllInterfaces(c));
		
		Class<?>[] allParentsArray 	= new Class<?>[classes.size()];
		allParentsArray 			= classes.toArray(allParentsArray);
		
		return allParentsArray;
	}
	
	
	private static Class<?>[] getAllParentsWithClass(Class<?> c)
	{
		LinkedList<Class<?>> 	classes 			= new LinkedList<Class<?>>();
		Class<?> 				parent				= c.getSuperclass();
		while (parent != null)
		{	
			classes.add(parent);
			parent = parent.getSuperclass();
		}
		
		classes.addAll(getAllInterfaces(c));
		classes.add(c);
		
		Class<?>[] allParentsArray 	= new Class<?>[classes.size()];
		allParentsArray 			= classes.toArray(allParentsArray);
		
		return allParentsArray;
	}
	
	
	private boolean isClassContainsMethodWithAnnotation(Class<?> c, Method method)
	{
		Method[] methods = c.getDeclaredMethods();
		
		for (Method classMethod : methods)
		{
			if(isCompatibleMethod(classMethod, method))
			{
				if (classMethod.isAnnotationPresent(HW4Method.class))
				{
					return true;
				}
			}
		}
		return false;
	}

	private boolean isHW4MethodAnnotatedInParents(Class<?> c, Method method)
	{
		for (Class<?> classesIterator : getAllParentsWithClass(c))
		{
			if (isClassContainsMethodWithAnnotation(classesIterator, method))
			{
				return true;
			}
		}
		return false;
	}
	
	public static boolean isCompatibleMethod(Method leftMethod, Method rightMethod)
	{
		if(leftMethod.getName() == rightMethod.getName())
		{
			if(leftMethod.getParameterTypes().length == rightMethod.getParameterTypes().length)
			{
				leftMethod.getReturnType();
				if(isSubType(leftMethod.getReturnType(), rightMethod.getReturnType()))
				{
					Class<?>[] leftMethodParameters = leftMethod.getParameterTypes();
					Class<?>[] rightMethodParameters = rightMethod.getParameterTypes();
					
					for(int i = 0; i < leftMethodParameters.length; i++)
					{
						if(! isSubType(rightMethodParameters[i], leftMethodParameters[i]))
						{
							return false;
						}
					}
					return true;
				}
			}
		}
		return false;
	}
	
	private AMBIGUITY_TYPE checkAmbiguity(Class<?> c, Method method)
	{
		LinkedList<Class<?>> ambiguityParents 	= new LinkedList<Class<?>>();
		LinkedList<Method> ambiguityMethods 	= new LinkedList<Method>(); 
	
		Class<?>[] classParents = getAllParents(c);
				
		for(Class<?> superClass : classParents)
		{
			Method[] methods = superClass.getDeclaredMethods();
			for(Method superClassMethod : methods)
			{
				if (superClassMethod.isAnnotationPresent(HW4Method.class))
				{
					if(isCompatibleMethod(method, superClassMethod))
					{

						ambiguityMethods.add(superClassMethod);
						ambiguityParents.add(superClass);
						break;
					}
				}
			}
		}
		
		if(ambiguityParents.isEmpty())
		{
			return AMBIGUITY_TYPE.none;
		}
		
		
		Class<?>[] classParentsWithAmbiguity 	= new Class<?>[ambiguityParents.size()];
		classParentsWithAmbiguity 				= ambiguityParents.toArray(classParentsWithAmbiguity);
		Method[] ambiguityMethodsArray 			= new Method[ambiguityParents.size()];
		ambiguityMethodsArray 					= ambiguityMethods.toArray(ambiguityMethodsArray);
		
		for (int i = 0; i < classParentsWithAmbiguity.length; i++)
		{
				for (int j = i + 1; j < classParentsWithAmbiguity.length
							&& classParentsWithAmbiguity[i] != null; j++)
				{
					if (classParentsWithAmbiguity[j] == null)
					{
						continue;
					}
					if(isSubType(classParentsWithAmbiguity[i], classParentsWithAmbiguity[j]))
					{
						classParentsWithAmbiguity[j] = null;
					}
					else if(isSubType(classParentsWithAmbiguity[j], classParentsWithAmbiguity[i]))
					{
						classParentsWithAmbiguity[i] = null;
					}
				}
		}
		
		LinkedList<Class<?>> 	ambiguityParentsNew 	= new LinkedList<Class<?>>();
		LinkedList<Method>	 	ambiguityMethodsNew	 	= new LinkedList<Method>();
		
		for (int i = 0; i < classParentsWithAmbiguity.length; i++){
			if(classParentsWithAmbiguity[i] != null)
			{
				ambiguityParentsNew.add(classParentsWithAmbiguity[i]);
				ambiguityMethodsNew.add(ambiguityMethodsArray[i]);
			}
		}
		
		classParentsWithAmbiguity 				= new Class<?>[ambiguityParentsNew.size()];
		classParentsWithAmbiguity 				= ambiguityParentsNew.toArray(classParentsWithAmbiguity);
		ambiguityMethodsArray 					= new Method[ambiguityParentsNew.size()];
		ambiguityMethodsArray 					= ambiguityMethods.toArray(ambiguityMethodsArray);
		
		
		if (classParentsWithAmbiguity.length < 2)
		{
			return AMBIGUITY_TYPE.none;
		}
		
		for (int i = 0; i < classParentsWithAmbiguity.length; i++)
		{
			for (int j = i + 1; j < classParentsWithAmbiguity.length; j++)
			{
				for(Class<?> parentA : getAllInterfaces(classParentsWithAmbiguity[i]))
				{
					if (isSubType(classParentsWithAmbiguity[j], parentA))
					{
						for (Method parentAMethod : parentA.getDeclaredMethods())
						{
							if (isCompatibleMethod(ambiguityMethodsArray[i], parentAMethod) 
									&& isCompatibleMethod(ambiguityMethodsArray[j], parentAMethod))
							{
								return AMBIGUITY_TYPE.inherited;
							}
						}
					}
				}
			}
		}
		
		return AMBIGUITY_TYPE.coincident;
	}
	
	
	public static boolean isSubType(Class<?> leftClass, Class<?> rightClass)
	{
		Class<?>[] leftClassParents =  getAllParentsWithClass(leftClass);
		
		for(Class<?> parentClass: leftClassParents)
		{
			if(parentClass.getName() == rightClass.getName())
			{
				return true;
			}
		}		
		return false;
	}
	
	
	private boolean isSameBucket(Method leftMethod, Method rightMethod)

	{
		if(leftMethod.getName() == rightMethod.getName())
		{
			if(leftMethod.getParameterTypes().length == rightMethod.getParameterTypes().length)
			{
				if(isSubType(leftMethod.getReturnType(), rightMethod.getReturnType()))
				{
					Class<?>[] leftMethodParameters = leftMethod.getParameterTypes();
					Class<?>[] rightMethodParameters = rightMethod.getParameterTypes();
					
					for(int i = 0; i < leftMethodParameters.length; i++)
					{
						if(! (leftMethodParameters[i].getName() == 
								rightMethodParameters[i].getName()))
						{
							return false;
						}
					}
					return true;
				}
			}
		}
		return false;
	}
	
	
	public void convert(Class<?> c) throws ParserConfigurationException, TransformerException
	{
		if (!c.isAnnotationPresent(HW4Class.class))
		{
			return;
		}
		
		String filePath = c.getAnnotation(HW4Class.class).value();
		OutputStream outputStream = null;
		
		if(!filePath.equals("Unknown"))
		{
			try { 
				outputStream = new FileOutputStream(filePath); 
			} catch (FileNotFoundException e) {
				return;
			}
		}
		else
		{
			outputStream = System.out;
		}
		ClassNode classXML = new ClassNode(c.getName());
		

		//<get the methods>
		Method[] candidateMethods = c.getDeclaredMethods();
		
		
		LinkedList<LinkedList<Method>> methodBucekets = new LinkedList<LinkedList<Method>>();
		boolean hasBucket = false;
		for(Method method: candidateMethods)
		{
			for(List<Method> bucket: methodBucekets)
			{
				Method firstMethodInList = bucket.get(0);
				if(isSameBucket(firstMethodInList, method))
				{
					bucket.add(method);
					hasBucket = true;
				}
			}
			if(!hasBucket)
			{
				LinkedList<Method> newBucket = new LinkedList<Method>();
				newBucket.add(method);
				methodBucekets.add(newBucket);
			}
			hasBucket = false;
		}
		
		//<getting one method out of a bucket>
		candidateMethods = new Method[methodBucekets.size()]; 
		
		int i = 0; 
		for(List<Method> bucket: methodBucekets) 
		{  
			Collections.sort(bucket, new MethodComperator()); 
			candidateMethods[i++] = bucket.get(0); 
		} 
		//</getting one method out of a bucket>
		//</get the methods>		
		
		for (Method method : candidateMethods) 
		{ 
			if(isHW4MethodAnnotatedInParents(c, method))
			{
					//<getMethodInfo>
					Class<?>[] parameterTypes 	= method.getParameterTypes();
					//</getMethodInfo>
					
					AMBIGUITY_TYPE result = checkAmbiguity(c, method);
										
					//<creatingXML>
					i = 0;
					
					MethodNode methodNode = classXML.addMethod(method.getName(), method.getReturnType());
					
					methodNode.addAmbiguityType(result);

					for (Class<?> paramClass : parameterTypes) {
						methodNode.addParam("p" + i, paramClass);
						i++;
					}
					//</creatingXML>
			}
		}
		classXML.generateXml(outputStream);
	}
}