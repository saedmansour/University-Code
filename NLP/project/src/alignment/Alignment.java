package alignment;

import java.util.HashMap;
import java.util.LinkedList;


public class Alignment {
	
	private class SentenceMatch {
		SentenceMatch(String[] match, double p) {
				this.match 	  = match;
				this.p 		  = p;
		}		
		public String[] match;
		public double 	p;
	}
	
	private HashMap<String[], LinkedList<SentenceMatch>> alignment = 
								new HashMap<String[], LinkedList<SentenceMatch>>();
	
	public void add(String[] sentence, String[] match, double p)
	{
		if(!alignment.containsKey(sentence)) {
			LinkedList<SentenceMatch> list = new LinkedList<SentenceMatch>();
			list.add(new SentenceMatch(match, p));
			alignment.put(sentence, list);
		} else {
			alignment.get(sentence).add(new SentenceMatch(match, p));
		}
	}
	
}
