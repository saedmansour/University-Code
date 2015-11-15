package alignment;

import java.util.HashMap;

public class Lexicon {
	private class Translation {
		Translation(String word, double p){
			this.word = word;
			this.p = p;
		}
		public String word;
		public double p;		//probability
	}
	
	private HashMap<String, Translation> lexicon = new HashMap<String, Translation>();
	
	public void addWord(String word, String translation, double probability){
		lexicon.put(word, new Translation(translation, probability));
	}
}