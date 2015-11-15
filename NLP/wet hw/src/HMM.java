/*****************************************************************************
 *	 Imports	
 ****************************************************************************/

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;




/*****************************************************************************
 *	 HMM Class	
 ****************************************************************************/

/**
 * 
 * 	<p>This HMM works with a file that it builds its Lambda = (A, B, PI) from.
 * 	This corpus file should be in the form of corpus_development.txt that can
 *  be found in the project folder. This is a manually tagged corpus to learn
 *  from and to construct the HMM's Lambda from.</p>
 *  
 *  <p>This HMM is language independent i.e. for English, Hebrew, Arabic, etc...</p>
 *  
 *  <p>This HMM is based on a homework guidelines in the course Natural Language 
 *  Processing in the Technion.</p>
 */

public class HMM {
	public static String lineSiperator = "start((\\s)+)start((\\s)+)start";
		
	
	/*****************************************************************************
	 * 	Test
	 ****************************************************************************/
		
	public static void test(String[] args){
		HMM hmm = new HMM(0.5);
		String[] tags = hmm.getAllTags();
		
		/**
		 * TEST: PI
		 */
		for (int i = 0; i < tags.length; ++i) {
			for (int j = 0; j < tags.length; ++j) {
					System.out.println("(" + tags[i] + "," + tags[j] + ")" + 
							hmm.getPI(tags[i], tags[j]));
			}
		}
		
		
		
		
		/**
		 * TEST A
		 */
		for (int i = 0; i < tags.length; ++i) {
			for (int j = 0; j < tags.length; ++j) {
				for (int k = 0; k < tags.length; ++k) {
						System.out.println("(" + tags[i] + "," + tags[j] + "," + tags[k] + ")" + 
								hmm.getA(tags[i], tags[j], tags[k]));
				}
			}
		}
		
		
		
		/**
		 * TEST B
		 */
		TagAndObservable[] tagsAndObservables = (TagAndObservable[]) hmm.observables.keySet().toArray(new TagAndObservable[]{});
		for(int i = 0; i < tags.length; ++i){
			for (int j = 0; j < tagsAndObservables.length; ++j){
				if(hmm.getB(tags[i], tagsAndObservables[j].observable) != 0.0) {
					System.out.println(tagsAndObservables[j].observable + " tagged as " + tags[i] + 
							hmm.getB(tags[i], tagsAndObservables[j].observable));
				}
			}
		}
	}
	
	
	
	
	/*****************************************************************************
	 * 	Private Helper Classes: Lambda, StatePair, ToFromStatePair, ToFromOutput,
	 * 						StateTriple, TagAndObservable
	 * 
	 * These classes represents the data structures used in the HMM for making
	 * states that are consisted of two tags or three, or an observable with a tag, 
	 * etc...
	 * 
	 ****************************************************************************/
	private class TagAndObservable{
		public TagAndObservable(String tag, String observable){
			this.tag = tag;
			this.observable = observable;
		}
		public boolean equals(Object other) {
			TagAndObservable otherAsStatePair = (TagAndObservable) other;
			return (otherAsStatePair.tag.equals(this.tag) &&
					otherAsStatePair.observable.equals(this.observable));
		}
		public int hashCode() { 
			return tag.hashCode() + observable.hashCode();
		}
		public String tag;
		public String observable;
	}
	
	private class StatePair{
		public StatePair(String state1, String state2){
			this.state1 = state1;
			this.state2 = state2;
		}
		public boolean equals(Object other) {
			StatePair otherAsStatePair = (StatePair) other;
			return (otherAsStatePair.state1.equals(this.state1) &&
					otherAsStatePair.state2.equals(this.state2));
		}
		public int hashCode() { 
			return state1.hashCode() + state2.hashCode();
		}
		public String state1;
		public String state2;
	}
	
	private class StateTriple{
		public StateTriple(String state1, String state2, String state3){
			this.state1 = state1;
			this.state2 = state2;
			this.state3 = state3;
		}
		public boolean equals(Object other) {
			StateTriple otherAsStatePair = (StateTriple) other;
			return (otherAsStatePair.state1.equals(this.state1) &&
					otherAsStatePair.state2.equals(this.state2) &&
					otherAsStatePair.state3.equals(this.state3));
		}
		public int hashCode() { 
			return state1.hashCode() + state2.hashCode() + state3.hashCode();
		}
		public String state1;
		public String state2;
		public String state3;
	}
	
	private class ToFromStatePair {
		public ToFromStatePair(StatePair from, StatePair to){
			this.from 	= from;
			this.to 	= to;	
		}
		public boolean equals(Object other) {
			ToFromStatePair otherAsStatePair = (ToFromStatePair) other;
			return (otherAsStatePair.from.equals(this.from) &&
					otherAsStatePair.to.equals(this.to));
		}
		public int hashCode() { 
			return from.hashCode() + to.hashCode();
		}
		public StatePair from;
		public StatePair to;
	}
	
	private class ToFromOutput{
		public ToFromOutput(ToFromStatePair toFromStatePair, String observable){
			this.toFromStatePair = toFromStatePair;
			this.observable 	 = observable;
		}
		public boolean equals(Object other) {
			ToFromOutput otherAsStatePair = (ToFromOutput) other;
			return (otherAsStatePair.toFromStatePair.equals(this.toFromStatePair) &&
					otherAsStatePair.observable.equals(this.observable));
		}
		public int hashCode() { 
			return observable.hashCode() + toFromStatePair.hashCode();
		}
		ToFromStatePair toFromStatePair;
		String observable;
	}
	
	
	
	
	/***************************************************
	 * 	Lambda Model For HMM
	 * 
	 * Lambda = (A, B, PI)
	 * 
	 ***************************************************/
	private class Lambda {
		
		private HashMap<ToFromStatePair, Double> 	A;
		private HashMap<TagAndObservable, Double> 	B;
		private HashMap<StatePair, Double> 			PI;
		
		private int statesNum;
		private int observablesNum;
		
		public Lambda(int tagsNum, int observablesNum){
			A  	= new HashMap<ToFromStatePair, Double>();
			B 	= new HashMap<TagAndObservable, Double>();
			PI  = new  HashMap<StatePair, Double>();
			this.statesNum = tagsNum * tagsNum;
			this.observablesNum = observablesNum;
		}
		
		public void setA(StatePair from, StatePair to, double probability){
			A.put(new ToFromStatePair(from, to), new Double(probability));
		}
		
		public void setPI(StatePair statePair, double probability){
			PI.put(statePair, probability);
		}
		
		public void setB(String tag, String observable, double probability){
			B.put(new TagAndObservable(tag, observable), probability);
		}
		
		public double getA(StatePair from, StatePair to){
			return A.get(new ToFromStatePair(from, to));
}
		
		public double getPI(StatePair statePair){
			return PI.get(statePair);
		}

		public double getB(String tag, String observable){
			if(B.get(new TagAndObservable(tag, observable)) == null){
				Integer cTag = CTag.get(tag);
				if (cTag == null){
					cTag = 0;
				}
				//return ourFraction/(cTag + tags.size()*corpusSize*ourFraction);
				return ourFraction/(cTag + tags.size()*corpusSize*5*ourFraction);
			}
			return B.get(new TagAndObservable(tag, observable));
		}
	}



	
	/*****************************************************************************
	 * 	Private Members
	 ****************************************************************************/

	private String corpusFilePathForLearning = null;
	private double ourFraction 				 = 0.5;
	private int corpusSize 					 = 0;
	
	/* C(tag) */
	private HashMap<String, Integer> 		CTag 	= new HashMap<String,Integer>();
	
	/* C(tag1, tag2) */
	private HashMap<StatePair, Integer> 	C2Tags 	= new HashMap<StatePair, Integer>();
	
	/* C(tag1, tag2, tag3) */
	private HashMap<StateTriple, Integer> 	C3Tags 	= new HashMap<StateTriple, Integer>();
	
	/* C(tag1, tag2) that are in sentence betginning */
	private HashMap<StatePair, Integer> 	C2TagsAtSentenceBeginning 	= new HashMap<StatePair, Integer>();;
	
	/* C(tag, observable) */
	private HashMap<TagAndObservable, Integer> observables = new HashMap<TagAndObservable, Integer>();
	
	Set<String> tags = new HashSet<String>();
	
	Set<String> corpusWords = new HashSet<String>();
	
	Lambda lambda = null;
	
	
	
	/*****************************************************************************
	 * 	Public Methods
	 ****************************************************************************/
	
	/**
	 * 	HMM Constructor with file to learn
	 */
	public HMM(String corpusFilePath){
		tags.add("Unknown");
		corpusFilePathForLearning  = corpusFilePath;
		try {
			parseCorpus();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	
	/**
	 * 	HMM Empty Constructor
	 */
	public HMM(double fraction){	
		ourFraction = fraction;
		tags.add("Unknown");
		corpusFilePathForLearning = "corpus_learning.txt";
		//corpusFilePathForLearning = "corpus_development.txt";
		try {
			parseCorpus();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	
	/**
	 * @param tag1   String representing the tag. For example: "noun" tag1
	 * 				 is that latest (newest) tag in the sentence.
	 * @param tag2
	 * @return
	 */
	public double getPI(String tag1, String tag2){
		return lambda.getPI(new StatePair(tag1, tag2));
	}
	
	
	/**
	 * 
	 * @param tag1
	 * @param tag2
	 * @param tag3
	 * @return
	 */
	public double getA(String tag1, String tag2, String tag3){
		return lambda.getA(new StatePair(tag2, tag3), new StatePair(tag1, tag2));
	}
	
	
	/**
	 * 
	 * @param tag1
	 * @param output
	 * @return
	 */
	public double getB(String tag, String observable){
		return lambda.getB(tag, observable);
	}
	
	
	/**
	 * 
	 * @return array of all tags in the Corpus including Unknown
	 */
	public String[] getAllTags(){
		return (String[]) tags.toArray(new String[]{});
	}
	
	
	
	
	/*****************************************************************************
	 * 	Private Methods
	 ****************************************************************************/
	
	/**
	 * Handles each line in the corpus in parsing
	 */
	private void lineHandler(String line, String tag, String oldTag){
		String[] tokens = line.split("((\\s)+)");
		if (tokens.length < 1){
			System.err.println("ERROR: lineHanlder() -line is 0 long");
			return;
		}
		String word 	= tokens[0];
		String lemma 	= null;
		String POSTag	= null;
		
		if(tokens.length >= 3){
			lemma	= tokens[1];
			POSTag 	= tokens[2];
		}
		else if(tokens.length == 2){
			POSTag 	= tokens[1];
		}
		else{
			POSTag = "Unknown";
		}
		
		boolean result = false;
		if(lemma != null){
			result = corpusWords.add(lemma);
		} else {
			result = corpusWords.add(word);
		}
		if(result == true){
			corpusSize++;
		}
		
		if(POSTag == null || POSTag.equals("")){
			System.err.println("ERROR: lineHandler() POSTAG isn't set");
			return;
		}
		tags.add(POSTag);
		
		String wordToAdd = word;
		if (lemma != null) {
			wordToAdd = lemma;
		}
		TagAndObservable tagAndObservable = new TagAndObservable(POSTag, wordToAdd);
		Integer observableByTag = observables.get(tagAndObservable);
		if(observableByTag == null){
			observableByTag = 0;
		}
		++observableByTag;
		observables.put(tagAndObservable, observableByTag);
		
		Integer CtagPOSTagValue = CTag.get(POSTag);
		if(CtagPOSTagValue == null){
			CtagPOSTagValue = 0;
		}
		++CtagPOSTagValue;
		CTag.put(POSTag, CtagPOSTagValue);
		
		if(tag == null) return;
		StatePair newTagPair = new StatePair(POSTag, tag);
		Integer CPairTagValue = C2Tags.get(newTagPair);
		if(CPairTagValue == null){
			CPairTagValue = 0;
		}
		++CPairTagValue;
		C2Tags.put(newTagPair, CPairTagValue);
		
		if(oldTag == null) return;
		StateTriple tripleTags = new StateTriple(POSTag, tag, oldTag);
		Integer CTripleTag = C3Tags.get(tripleTags);
		if(CTripleTag == null){
			CTripleTag = 0;
		}
		++CTripleTag;
		C3Tags.put(tripleTags, CTripleTag);
	}
	
	
	private String getWordTag(String parsedLine){
		String tag = null;
		String[] lineWords = parsedLine.split("((\\s)+)");
		if(lineWords.length >= 3){
			tag = lineWords[2];
		}
		else if(lineWords.length == 2){
			tag = lineWords[1];
		} else {
			tag = "unknown";
		}
		
		return tag;
		//</parse>
	}
	
	/**
	 * Parses the corpus to learn the file and collect statistics.
	 * 
	 * @throws FileNotFoundException
	 */
	private void parseCorpus() throws FileNotFoundException {
		File 	corpusFile 		= new File(corpusFilePathForLearning);
		Scanner corpusScanner 	= new Scanner(corpusFile);

		String  line = corpusScanner.nextLine();
		while (corpusScanner.hasNextLine())
		{
			//<parse info="first word">
			lineHandler(line, null, null);
			String firstWordTag = getWordTag(line);
			//</parse>


			//<parse info="second word">
			if(!corpusScanner.hasNextLine()) { //if no second word in sentence
				break;	
			}
			line = corpusScanner.nextLine();
			if (line.matches(lineSiperator)) {
				System.out.println("WARNING: The sentence contains only one word");
				continue;
			}
			lineHandler(line, firstWordTag, null);
			String secondWordTag = getWordTag(line);
			//</parse>
			
			
			// This is used for PI
			StatePair newTagPair = new StatePair(secondWordTag, firstWordTag);
			Integer CPairTagValue = C2TagsAtSentenceBeginning.get(newTagPair);
			if(CPairTagValue == null){
				CPairTagValue = 0;
			}
			CPairTagValue++;
			C2TagsAtSentenceBeginning.put(newTagPair, CPairTagValue);

			
			//<parse info="third word or more in sentence">
			String tag1 = secondWordTag;
			String tag2 = firstWordTag;
			while (corpusScanner.hasNextLine()){
				line = corpusScanner.nextLine();
				if (line.matches(lineSiperator)) {
					break;	//continue in outer loop to next sentence
				}
				lineHandler(line, tag1, tag2);
				tag2 = tag1;
				tag1 = getWordTag(line);
			}
			//</parse>
		}
		corpusScanner.close();
		

		//<test contents>
		//Ctag, C2tags, C3Tags, tags, 
		//System.out.println(CTag);
		//System.out.println(corpusWords);
		//TagAndObservable[] result = observables.keySet().toArray(new TagAndObservable[]{});
		//</test contents>
		
		computeLambda();
	}
	
	
	/**
	 * 	<p>call after parse() computes the Lambda model after collection the statistics</p>
	 */
	private void computeLambda(){
		if (C3Tags.size() < 1) {
			System.err.println("There is no statistics, please call parse();");
		}
		lambda = new Lambda(tags.size(), observables.size());
		
		computeLambdaA();
		computeLambdaB();
		computeLambdaPI();
	}
	
	
	private void computeLambdaA() {
		double probability;
		
		StateTriple[] triplesOfTags = C3Tags.keySet().toArray(new StateTriple[]{});
		String[] tagsArray  = (String[])tags.toArray(new String[]{});
		
		for (StateTriple tripleTag : triplesOfTags) {
			String tag1 	= tripleTag.state1;
			String tag2 	= tripleTag.state2;
			String tag3 	= tripleTag.state3;
			Integer pairStatesNum = C2Tags.get(new StatePair(tag2, tag3));
			if(pairStatesNum == null){
				pairStatesNum = 0;
			}
			probability = ((double)C3Tags.get(tripleTag) + ourFraction)/ (pairStatesNum + ourFraction*tagsArray.length); 
			lambda.setA(new StatePair(tag2, tag3), new StatePair(tag1, tag2), probability);
		}
		
		for (int i = 0; i < tagsArray.length; ++i){
			for (int j = 0; j < tagsArray.length; ++j){
				for (int k = 0; k < tagsArray.length; ++k){
					StateTriple stateTriple = new StateTriple(tagsArray[i], tagsArray[j], tagsArray[k]);
					if(!C3Tags.containsKey(stateTriple)){
						Integer pairStatesNum = C2Tags.get(new StatePair(tagsArray[j], tagsArray[k]));
						if(pairStatesNum == null) {
							pairStatesNum = 0;
						}
						lambda.setA(new StatePair(tagsArray[j], tagsArray[k]), new StatePair(tagsArray[i], tagsArray[j]),  
								ourFraction/(pairStatesNum + ourFraction*tagsArray.length)   );
					}
				}
			}
		}
	}
	
	
	private void computeLambdaB() { 
		double probability;
		
		TagAndObservable[] tagsAndObservables = (TagAndObservable[]) observables.keySet().toArray(new TagAndObservable[]{});
		String[] tagsArray  = (String[])tags.toArray(new String[]{});
		String[] wordsArray = (String[])corpusWords.toArray(new String[]{});
		
		for (TagAndObservable tagAndObservable : tagsAndObservables) {				
			Integer cTag = CTag.get(tagAndObservable.tag);
			if(cTag == null){
				cTag = 0;
			}
			probability = ((double)observables.get(tagAndObservable) + ourFraction) / (cTag + wordsArray.length*ourFraction);
			lambda.setB(tagAndObservable.tag, tagAndObservable.observable, probability);
		}	
		
		for(int i = 0; i < tagsArray.length; ++i){
			for (int j = 0; j < wordsArray.length; ++j){
				TagAndObservable tagAndObservable = new TagAndObservable(tagsArray[i], wordsArray[j]);
				if(observables.get(tagAndObservable) == null){
					Integer cTag = CTag.get(tagAndObservable.tag);
					if (cTag == null){
						cTag = 0;
					}
					lambda.setB(tagAndObservable.tag, tagAndObservable.observable, 
							ourFraction/(cTag + ourFraction*wordsArray.length));
				}
			}
		}
	}
	
	
	private void computeLambdaPI() {  
		double probability;
		
		StatePair[] statePairsAtSentenceBeginning = (StatePair[]) C2TagsAtSentenceBeginning.keySet().toArray(new StatePair[]{});
		String[] tagsArray = (String[])tags.toArray(new String[]{});
		
		int sentencesNum = 0;
		for (StatePair tagPair : statePairsAtSentenceBeginning) {
			sentencesNum += C2TagsAtSentenceBeginning.get(tagPair);
		}
		
		for (StatePair tagPair : statePairsAtSentenceBeginning) {
			//probability	   	= ((double)C2TagsAtSentenceBeginning.get(tagPair) + ourFraction) 	/ (sentencesNum + tagsArray.length*tagsArray.length*ourFraction);
			probability	   	= ((double)C2TagsAtSentenceBeginning.get(tagPair) + ourFraction) 	/ (sentencesNum*ourFraction + tagsArray.length*ourFraction);
			lambda.setPI(tagPair, probability);
		}
		
		// handle (tag1, tag2) that don't appear in corpus
		for (int i = 0; i < tagsArray.length; ++i){
			for(int j = 0; j < tagsArray.length; ++j){
				StatePair statePair = new StatePair(tagsArray[i], tagsArray[j]);
				if(!C2TagsAtSentenceBeginning.containsKey(statePair)){
					//lambda.setPI(statePair, ourFraction/(sentencesNum + tagsArray.length * tagsArray.length * ourFraction));
					lambda.setPI(statePair, ourFraction/(sentencesNum*ourFraction + tagsArray.length * ourFraction));
				}
			}
		}
	}
}
/*****************************************************************************
 *	 /HMM CLASS END	
 ****************************************************************************/