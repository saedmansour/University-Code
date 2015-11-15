import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.Scanner;


/**
 * This class takes a courpus file and parses it and returns it as an array of string[][][]
 * of sentences and words and tags.
 */
public class ParseCorpus {

	/*
	public static void main(String[] args){
		String[][][] result = ParseCorpus.getCorpus("corpus_evaluation.txt");
		System.out.println();
	}*/
	
	public static String lineSiperator = "start((\\s)+)start((\\s)+)start";
	
	private static int wordsNum = 0;
	
	public static int getWordNum(){
		return wordsNum;
	}
	
	private static String[] lineWordTag(String line){
		String[] tokens = line.split(("((\\s)+)"));
		if (tokens.length < 1){
			System.err.println("ERROR: lineHanlder() -line is 0 long");
			return null;
		}
		String word 	= tokens[0];
		String POSTag	= null;
		
		if(word == null || word.equals("")){
			return null;
		}
		
		if(tokens.length >= 3){
			POSTag 	= tokens[2];
		}
		else if(tokens.length == 2){
			POSTag 	= tokens[1];
		}
		else{
			POSTag = "Unknown";
		}
		if(POSTag == null || POSTag.equals("")){
			System.err.println("ERROR: lineHandler() POSTAG isn't set");
			return null;
		}		
		return new String[]{word, POSTag};
	}
	
	public static String[][][] getCorpus(String filePath) 
	{
		wordsNum =0;
		LinkedList<LinkedList<String[]>> result = new LinkedList<LinkedList<String[]>>();
		
		File 	corpusFile 		= new File(filePath);
		Scanner corpusScanner = null;
		try {
			corpusScanner = new Scanner(corpusFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		LinkedList<String[]> sentence = null;
		
		String  line = corpusScanner.nextLine();
		if (!line.matches(lineSiperator)) {
			System.err.println("ERROR: Corpus file doesn't start with 'start start start'.");
			return null;
		} 
		while (corpusScanner.hasNextLine())
		{
			if(!corpusScanner.hasNextLine()){ 
				System.err.println("ERROR: The sentence doesn't contain words.");
				break;	
			}
			wordsNum++;
			if (line.matches(lineSiperator)) {
				//result.add(sentence);
				sentence = new LinkedList<String[]>();
				result.add(sentence);
				//continue;
			}
			if(lineWordTag(line) != null){
				sentence.add(lineWordTag(line));
			}
			line = corpusScanner.nextLine();
		}		
		//result.add(sentence);
		corpusScanner.close();
		//</parse>

		// linkedList<...> => String[][][]
		String[][][] finalResult = new String[result.size()][][];
		for(int t=0;t<result.size();t++)
		{
			finalResult[t] = new String[result.get(t).size()][];
			finalResult[t] = result.get(t).toArray(finalResult[t]);
		}
		return finalResult;
	}
}