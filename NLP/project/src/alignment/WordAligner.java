package alignment;


import java.util.HashMap;
import java.util.LinkedList;
import java.util.Set;
import development.*;

public class WordAligner {
	
	private String arabicCorpusFilePath;
	private String hebrewCorpusFilePath;
	
	private TaggedWord[][] arabicCorpus;
	private TaggedWord[][] hebrewCorpus;
	
	private TaggedWord[][] arabicCorpusNoCommonWords;
	private TaggedWord[][] hebrewCorpusNoCommonWords;
	
	private Lexicon 	lexicon 	= new Lexicon();
	private Alignment 	alignment 	= new Alignment();
	
	Alignment P_ByOccurencesNum 		= new Alignment();
	Alignment P_ByPOStag 				= new Alignment();
	Alignment P_ByPhoneticSimilarity	= new Alignment();
	Alignment P_ByLength				= new Alignment();
	Alignment P_ByOrder					= new Alignment();
	
	Alignment P_Combined				= new Alignment();
	
	
	// Program Parameters
	int  minTranslationNum = 3;
	
	
	/**
	 * 
	 * @param arabicCorpusFilePath 
	 * 							The file is consisted of separated lines, after each line is the 
	 * 							the tagging of the line, e.g.:
	 * 
	 * 							This is sentence number 1
	 * 							THIS_TAG VERB NOUN NOUN NUMERAL
	 * 							This is sentence number 2
	 * 							THIS_TAG VERB NOUN NOUN NUMERAL
	 * 							.
	 * 							.
	 * 							.
	 * 
	 * @param hebrewCorpusFilePath
	 */
	WordAligner(String arabicCorpusFilePath, String hebrewCorpusFilePath) {
		this.arabicCorpusFilePath 				= arabicCorpusFilePath;
		this.hebrewCorpusFilePath 				= hebrewCorpusFilePath;
		this.arabicCorpus 						= Helper.getFileAsTaggedArray(arabicCorpusFilePath);
		this.hebrewCorpus						= Helper.getFileAsTaggedArray(hebrewCorpusFilePath);
		LinkedList<TaggedWord[][]>  corpusList 	= Helper.deleteCommonWords(this.arabicCorpus, this.hebrewCorpus);
		this.arabicCorpusNoCommonWords 			= corpusList.get(0);
		this.hebrewCorpusNoCommonWords 			= corpusList.get(1);
	}
	
	public void Align() {
		computeP_ByOccurencesNum();
		computeP_ByPOStag();
		computeP_ByPhoneticSimilarity();
		computeP_ByLength();
		computeP_ByOrder();
		
		combineProbabilities();
		
		printBestAlignment(P_Combined);
		
		extractLexicon();
	}

	
	private void extractLexicon() {
		// TODO Auto-generated method stub
		
	}

	private void printBestAlignment(Alignment pCombined) {
		// TODO Auto-generated method stub
		
	}

	private void combineProbabilities() {
		// TODO Auto-generated method stub
		
	}

	private void computeP_ByOrder() {
		// TODO Auto-generated method stub
		
	}

	private void computeP_ByLength() {
		// TODO Auto-generated method stub
		
	}

	private void computeP_ByPhoneticSimilarity() {
		// TODO Auto-generated method stub
		
	}

	private void computeP_ByPOStag() {
		// TODO Auto-generated method stub
		
	}

	private HashMap<String, HashMap<String, Integer>> computeStatistics(String filePath1, String filePath2) {		
		HashMap<String, HashMap<String, Integer>> stat = new HashMap<String, HashMap<String, Integer>>(); 
		
		for (int i = 0; i < this.arabicCorpusNoCommonWords.length; i++) 
		{
			TaggedWord[] lineFromCorpus1 = this.arabicCorpusNoCommonWords[i];
			TaggedWord[] lineFromCorpus2 = this.hebrewCorpusNoCommonWords[i];
			
			for (TaggedWord taggedWord : lineFromCorpus1) {
				if(!stat.containsKey(taggedWord.word)){
					stat.put(taggedWord.word, new HashMap<String, Integer>());
				}
				for (TaggedWord TaggedWord_2 : lineFromCorpus2) {
					Integer numOfAppearances = stat.get(taggedWord.word).get(TaggedWord_2.word);
					if(numOfAppearances == null){
						numOfAppearances = 0;
					}
					stat.get(taggedWord.word).put(TaggedWord_2.word, ++numOfAppearances);
				}
			}
		} 
		
		Set<String> words = stat.keySet();
		for (String word : words) {
			HashMap<String, Integer> translationsHash = stat.get(word);
			Set<String> translationWords = translationsHash.keySet();
			
			int    max 				= 0;
			String bestTranslation  = null;
			for (String translation : translationWords) {
				if(translationsHash.get(translation) > max) {
					max = translationsHash.get(translation);
					bestTranslation = translation;
				}
			}
			if(max >= minTranslationNum) {
				System.out.println("C(word,translation) MATCH " + word + " : " + bestTranslation);
			}
		}
		return stat;	
	}
	
	private void computeP_ByOccurencesNum() {
		HashMap<String, HashMap<String, Integer>> statistics = 
					computeStatistics(arabicCorpusFilePath, hebrewCorpusFilePath);
		
		//foreach sentence
		//		sentence => for each match possible
		//						compute probability for match						
	}
}
