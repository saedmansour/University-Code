import java.util.HashMap;
import java.util.LinkedList;


public class ErrorsInfo {
	
	public HashMap<String,Integer> tagErrsNum;
	public HashMap<String,LinkedList<Integer[]>> tagErrsPlaces;
	public int errsNum=0;
	public String[] maxTwo;
	public String[] suggestedImprovment1;
	public String[] suggestedImprovment2;
	public int corpusSize=0;
	
	public Integer[] maxTwoNums;
	private HashMap<String,Integer> Improvments1Hash;
	private HashMap<String,Integer> Improvments2Hash;
	public int maxSug1=0;
	public int maxSug2=0;
	
	public ErrorsInfo(String[][][] our , String[][][] right)
	{
		int sentnceNum = our.length;
		maxTwoNums =  new Integer[]{0,0};
		maxTwo = new String[]{"",""};
		
		tagErrsNum = new HashMap<String,Integer>();
		tagErrsPlaces = new HashMap<String,LinkedList<Integer[]>>();
		Improvments1Hash = new HashMap<String,Integer>();
		Improvments2Hash = new HashMap<String,Integer>();
		

		for(int i=0;i<sentnceNum;i++)
		{
			for(int j=0;j<our[i].length;j++)
			{
				corpusSize++;
				if(!our[i][j][1].equals(right[i][j][1]))
				{
					errsNum++;
					
					//do maximum checking for errors fixation suggestions
					if(j>=1)
					{
						Integer temp1 = Improvments1Hash.get((our[i][j-1][1]+","+our[i][j][1]+","+right[i][j][1]));
						if(temp1==null)
						{
							temp1 = 0;
						}
						temp1++;
						Improvments1Hash.put((our[i][j-1][1]+","+our[i][j][1]+","+right[i][j][1]), temp1);
						
						if(temp1>maxSug1)
						{
							maxSug1 =temp1;
							suggestedImprovment1 = new String[]{our[i][j-1][1],our[i][j][1],right[i][j][1]};
						}
						
						
						if(j>=2)
						{
							Integer temp2 = Improvments2Hash.get((our[i][j-2][1]+","+our[i][j-1][1]+","+our[i][j][1]+","+right[i][j][1]));
							if(temp2==null)
							{
								temp2 = 0;
							}
							temp2++;
							Improvments2Hash.put((our[i][j-2][1]+","+our[i][j-1][1]+","+our[i][j][1]+","+right[i][j][1]), temp2);
							
							if(temp2>maxSug2)
							{
								maxSug2 =temp2;
								suggestedImprovment2 = new String[]{our[i][j-2][1],our[i][j-1][1],our[i][j][1],right[i][j][1]};
							}
							
						}
					}
					
					
					if(tagErrsNum.get(right[i][j][1])== null)
					{
						tagErrsNum.put(right[i][j][1], 0);
						tagErrsPlaces.put(right[i][j][1], new LinkedList<Integer[]>());
					}
					
					Integer currNum = tagErrsNum.get(right[i][j][1])+1;
					tagErrsNum.put(right[i][j][1],currNum);
					
					
					//a naive way to find max 2..
					if(currNum > maxTwoNums[0] && !(right[i][j][1].equals(maxTwo[0])))
					{
						maxTwoNums[1]=maxTwoNums[0];
						maxTwo[1]=maxTwo[0];
						maxTwoNums[0] = currNum;
						maxTwo[0] = right[i][j][1];
						
					}else
					{
						if(currNum>maxTwoNums[1] && !(right[i][j][1].equals(maxTwo[0])))
						{
							maxTwoNums[1] = currNum;
							maxTwo[1] = right[i][j][1];
						}
					}
					
					if(tagErrsPlaces.get(right[i][j][1]).size() <5)
					{
						tagErrsPlaces.get(right[i][j][1]).add(new Integer[]{i,j});
					}
					
				}
			}
		}
	}

}
