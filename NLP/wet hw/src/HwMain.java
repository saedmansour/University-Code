import java.util.LinkedList;


public class HwMain {
	
	public static void main(String[] args)
	{
		HMM hmm = new HMM(0.5);	
		
		String[][][] rightTagging = ParseCorpus.getCorpus("corpus_evaluation.txt");//get tagging!!
		
		Integer wordsNum = ParseCorpus.getWordNum();//get words num
		String[][][] ourTagging = viterbi.viterbiTagger(rightTagging, hmm);
		//(*)
		//System.out.println("tagged");
		//analyze the results , and get errors statistics
		ErrorsInfo errsAnlyze = new ErrorsInfo(ourTagging,rightTagging);
		
		System.out.println("The errors num is: "+errsAnlyze.errsNum + "and the words num is "+errsAnlyze.corpusSize);
		System.out.println("[+] The error pricent is:- "+(((double)errsAnlyze.errsNum)/wordsNum)+"%");
		//print out the resutls (part B).
		System.out.println("[+] The error pricent is:- "+(((double)errsAnlyze.errsNum)/wordsNum)+"%");
		System.out.println("[+] The two most problematic tags is '"+errsAnlyze.maxTwo[0]+"' And '"+errsAnlyze.maxTwo[1]+"'");
		
		String badTag1 = errsAnlyze.maxTwo[0];
		String badTag2 = errsAnlyze.maxTwo[1];
		
		int badTag1ErrNum = errsAnlyze.maxTwoNums[0];
		int badTag2ErrNum = errsAnlyze.maxTwoNums[1];
		
		for(int y=0;y<2;y++){
			System.out.println("[*] Five error places for the tag "+errsAnlyze.maxTwo[y]+":");
			LinkedList<Integer[]> errplaces1 = errsAnlyze.tagErrsPlaces.get(errsAnlyze.maxTwo[y]);
			for(int j=0;j<errplaces1.size();j++)
			{
				String[] errWord = ourTagging[(errplaces1.get(j)[0])][(errplaces1.get(j)[1])];
				System.out.println(" -  Sentence "+errplaces1.get(j)[0]+" word "+errplaces1.get(j)[1]+" : ("+errWord[0]+"tagged as "+errWord[1]+")");
			}
		}
		
		LinkedList<String[]> correctionsList 	= new LinkedList<String[]>();
		boolean isFirstCorrection 				= false;
		int corrections 						= 0;
		
		rightTagging = ParseCorpus.getCorpus("corpus_learning.txt");//get tagging!!
		wordsNum = ParseCorpus.getWordNum();//get words num
		System.out.println("wwwow");
		ourTagging = viterbi.viterbiTagger(rightTagging, hmm);
		System.out.println("wwwew");
		
		errsAnlyze = new ErrorsInfo(ourTagging, rightTagging);
		
		System.out.println("Dalet now");		
		
		if (errsAnlyze.maxSug1 >= errsAnlyze.maxSug2) {
			isFirstCorrection = true;
			corrections = errsAnlyze.maxSug1;
		} else {
			isFirstCorrection = false;
			corrections = errsAnlyze.maxSug2;
		}
		int temp;
		
		do {
			temp = errsAnlyze.errsNum;
			if (corrections >= 2) {
				if(isFirstCorrection){
					corrections = makeCorrections(ourTagging, errsAnlyze.suggestedImprovment1);
					correctionsList.add(errsAnlyze.suggestedImprovment1);
				} else {
					corrections = makeCorrections(ourTagging, errsAnlyze.suggestedImprovment2);
					correctionsList.add(errsAnlyze.suggestedImprovment2);
				}
				errsAnlyze = new ErrorsInfo(ourTagging, rightTagging);
			} 
			
			if (errsAnlyze.maxSug1 >= errsAnlyze.maxSug2) {
				isFirstCorrection = true;
				corrections = errsAnlyze.maxSug1;
			} else {
				isFirstCorrection = false;
				corrections = errsAnlyze.maxSug2;
			}
			
			System.out.println("continue picause corrections is:"+corrections);
			
		} while ((temp -  errsAnlyze.errsNum) > 2);
				
		
		
		
		// OUTPUT OF DALET part 1
		System.out.println("\n\n********************************************");
		System.out.println("Dalet - part 1 - used transformation:");
		int j = 0;
		for (String[] transformation : correctionsList) {
			System.out.println("-----transofmration " + j);
			for(int i = 0; i < transformation.length; i++){
				System.out.println(transformation[i]);
			}
			System.out.println("\n");
			j++;
		}
		System.out.println("********************************************\n\n");
		
		
		
		
		//D2
		rightTagging = ParseCorpus.getCorpus("corpus_evaluation.txt");
		wordsNum = ParseCorpus.getWordNum();
		ourTagging = viterbi.viterbiTagger(rightTagging, hmm);
		
		for(int t=0;t<correctionsList.size();t++)
		{
			makeCorrections(ourTagging,correctionsList.get(t));
		}
		
		errsAnlyze = new ErrorsInfo(ourTagging,rightTagging);
		
	
		//D2.2
		System.out.println("The errors num is: "+errsAnlyze.errsNum + "and the words num is "+wordsNum);
		System.out.println("[+] The error pricent is:- "+(((double)errsAnlyze.errsNum)/wordsNum)+"%");
		
		//D2.3
		//badTag1, badTag2
		 System.out.println("tag1 new error rate: " + errsAnlyze.tagErrsNum.get(badTag1)+", old rate was:"+badTag1ErrNum);
		 System.out.println("tag2 new error rate: " + errsAnlyze.tagErrsNum.get(badTag2)+", old rate was:"+badTag2ErrNum);
		
		//GEMAL HERE
		 hmm = new HMM(0.1);
		 ourTagging = viterbi.viterbiTagger(rightTagging, hmm);
		 ErrorsInfo errsAnlyze2 = new ErrorsInfo(ourTagging,rightTagging);
		 System.out.println("[+] The error pricent is:- "+(((double)errsAnlyze2.errsNum)/wordsNum)+"%");
		 System.out.println("tag1 new error rate: " + errsAnlyze2.tagErrsNum.get(badTag1)+", old rate was:"+badTag1ErrNum);
		 System.out.println("tag2 new error rate: " + errsAnlyze2.tagErrsNum.get(badTag2)+", old rate was:"+badTag2ErrNum);
		
		// DALET.
	}
	
	private static int makeCorrections(String[][][] ourTagging,String[] corr)
	{
		int tabnet = 0;
		if(corr.length > 3){tabnet = 1;}
		int corrections =0;
		for(int i=0;i<ourTagging.length;i++)
		{
			for(int j=0;j<ourTagging[i].length;j++)
			{
				if(j>=1 && tabnet==0)
				{
					if(ourTagging[i][j-1][1].equals(corr[0]) && ourTagging[i][j][1].equals(corr[1]))
					{
						corrections++;
						ourTagging[i][j][1] = corr[2];
					}
				}
				
				if(j>=2 && tabnet==1)
				{
					if(ourTagging[i][j-2][1].equals(corr[0]) && ourTagging[i][j-1][1].equals(corr[1]) && ourTagging[i][j][1].equals(corr[2]))
					{
						corrections++;
						ourTagging[i][j][1] = corr[3];
					}
				}
			}
		}
		return corrections;
	}
	
	
}

 
