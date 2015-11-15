package hw4;

import java.lang.reflect.Method;
import java.util.Comparator;

public class MethodComperator  implements Comparator<Method>
{	
	public int compare(Method leftMethod, Method rightMethod) 
	{
		if(leftMethod.getReturnType().getName() == rightMethod.getReturnType().getName())
		{
			return 0;
		}
		else if(JavaToXML.isSubType(leftMethod.getReturnType(), rightMethod.getReturnType()))
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}
