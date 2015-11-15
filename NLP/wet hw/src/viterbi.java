
public class viterbi{
	
	public static String[]  getBestTagging(String[] wordsSeq,HMM hmmModel)
	{
		String[] tags = hmmModel.getAllTags();
		
		double[][][] delta = new double[tags.length][tags.length][wordsSeq.length];
		int[][][] road = new int[tags.length][tags.length][wordsSeq.length];
		
		
		
		//intialize delta and road.
		
		for(int i=0;i<tags.length;i++)
		{
			for(int j=0;j<tags.length;j++)
			{
				//System.out.println("pi is"+hmmModel.getPI(tags[i], tags[j])+"and B is"+hmmModel.getB(tags[j],wordsSeq[1]));
				delta[i][j][1] = Math.log(hmmModel.getPI(tags[j], tags[i]))+Math.log(hmmModel.getB(tags[i], wordsSeq[0]))+Math.log(hmmModel.getB(tags[j],wordsSeq[1]));
			}
		}
		
		
		
		//start the "recuresion".
		for(int k=2;k<wordsSeq.length;k++)
		{
			for(int i=0;i<tags.length;i++)
			{
				for(int j=0;j<tags.length;j++)
				{
					int max = -1;
					Double maxP = null;
					for(int t=0; t<tags.length;t++)
					{
						double currp = Math.log(hmmModel.getA(tags[j], tags[i], tags[t]))+delta[t][i][k-1]+Math.log(hmmModel.getB(tags[j],wordsSeq[k]));
						if((maxP == null) || currp > maxP)
						{
							max = t;
							maxP= currp;
						}
					}
					
					
					delta[i][j][k] = maxP;
					road[i][j][k]=max;
				}
			}
		}
		
		//find The bestWay;
		int curri=0,currj=0;
		String[] finalRes = new String[wordsSeq.length];
		Double maxP = null;
		for(int i=0;i<tags.length;i++)
		{
			for(int j=0;j<tags.length;j++)
			{
				
				if((maxP==null) || delta[i][j][wordsSeq.length-1]>maxP)
				{
					curri = i;
					currj = j;
					maxP = delta[i][j][wordsSeq.length-1];
				}
			}
		}
		
		finalRes[wordsSeq.length-1]=tags[currj];
		finalRes[wordsSeq.length-2]=tags[curri];
		
		for(int k=wordsSeq.length-1;k>1;k--)
		{
			int temp = currj;
			currj = curri;
			curri = road[curri][temp][k];
			finalRes[k-2] = tags[curri];
		}
		
		return finalRes;
	}
	
	
	
	public static String[][][] viterbiTagger(String[][][] rightTagging,HMM hmm)
	{
		//(*)
		//System.out.println("will start tagging "+rightTagging.length+" sentences");
		String[][][] ourTagging = new String[rightTagging.length][][];
		
		//get our tagging 
		
		for(int t=0;t<rightTagging.length;t++)
		{
			ourTagging[t] = new String[rightTagging[t].length][];
			
			String[] sentence = new String[rightTagging[t].length];
			
			for(int s=0;s<sentence.length;s++)
			{
				sentence[s] = rightTagging[t][s][0];
			}
			
		
		
			String[] tagging = viterbi.getBestTagging(sentence, hmm);
			String[][] temp = new String[tagging.length][];
			
			for(int s=0;s<sentence.length;s++)
			{
				temp[s] = new String[]{sentence[s],tagging[s]};
			}
			
			ourTagging[t] = temp;
			
			
			//(*)
			//System.out.println("["+t+"] sentence ("+sentence.length+")was tagged as: ");
			//for(int m=0;m<temp.length;m++){System.out.print(" " +temp[m][1]);}
			//System.out.println("\n\n");
		}
		return ourTagging;
	}

}
