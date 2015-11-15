package development;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;



//
//
//	This file isn't important it only includes try out code to try code out.
//	It includes the usage of extracting root in Arabic.
//
//

public class Main 
{	
	
	/**
	 * sentenceLastVerbAndNoun
	 */
	
	
	/**
	 * Description: takes a sentence in Hebrew or Arabic and returns the first verb and noun in it.
	 * @param sentence - String - a sentence given in a language 
	 * @param language
	 * @return VerbNoun of type (verb,noun). If verb or noun doesn't exist return null.
	 */
	public static VerbNoun sentenceFirstVerbAndNoun(String sentence, Language language)
	{
		String verb = "";
		String noun = "";
		TaggedWord[] taggedSentence = null;
		if(language == Language.HEBREW){
			taggedSentence = MorphTagger.hebrewPOSTagging(sentence);
			//TEST
			for (TaggedWord taggedWord : taggedSentence) {
				System.out.println(taggedWord.word);
				System.out.println(taggedWord.tag);
			}
			
			
		}
		else if(language == Language.ARABIC){
			taggedSentence = MorphTagger.arabicPOSTagging(sentence);
			//TEST
			
			for (TaggedWord taggedWord : taggedSentence) {
				System.out.println(taggedWord.word);
				System.out.println(taggedWord.tag);
			}
			
		}
		if(taggedSentence == null){
			System.out.println("ERROR: tagging failed.");
		}
		for (TaggedWord taggedWord : taggedSentence) {
			if(taggedWord.tag == Tag.VERB){
				verb =  taggedWord.word;
				break;
			}
			
		}
		for (TaggedWord taggedWord : taggedSentence) {
			if(taggedWord.tag == Tag.NOUN){
				noun = taggedWord.word;
				break;
			}
		}
		VerbNoun verbNoun = new VerbNoun();
		verbNoun.noun = noun;
		verbNoun.verb = verb;
		return verbNoun;
	}

	/**
	 * Test
	 *
	 * @param args
	 * @throws FileNotFoundException 
	 */
	public static void main(String[] args) throws FileNotFoundException{
		
		/**
		 * Test n.1:
		 * 		Input: sentences in Hebrew and Arabic to compare.
		 * 		Output: words that might have the same meaning. 
		 * 		
		 */
		/*
		String[] hebrewSentences = new String[100];
		String[] arabicSentences = new String[100];
		
		arabicSentences[0] = "العالم تغيّر";
		hebrewSentences[0] = "העולם השתנה...";
		arabicSentences[1] = "اشعر بهذا في الماء";
		hebrewSentences[1] = "אני חשה זאת במים...";
		arabicSentences[2] = "أشعر بهذا في الأرض";
		hebrewSentences[2] = "אני חשה זאת באדמה...";
		arabicSentences[3] = "اشعر بهذا في الهواء";
		hebrewSentences[3] = "אני חשה זאת באוויר";
		arabicSentences[4] = "كثيرا فقد";
		hebrewSentences[4] = "הרבה משהיה אבד...";
		arabicSentences[5] = "ثلاثة أُعْطِيَتْ إلى الجن الخالدين الأذكى والأعدل من جميع المخلوقات";
		hebrewSentences[5] = "שלוש ניתנו לאלפים,בני אלמוות, חכמים וגאים מכל חי"; 
		
		for (int i = 0; i < arabicSentences.length; i++){			
			VerbNoun hebrewVerbNoun =  sentenceFirstVerbAndNoun(hebrewSentences[i], Language.HEBREW);
			VerbNoun arabicVerbNoun = sentenceFirstVerbAndNoun(arabicSentences[i], Language.ARABIC);
			System.out.println("Arabic: " + arabicVerbNoun.verb + "\t\tHebrew: " + hebrewVerbNoun.verb);
			System.out.println("Arabic: " + arabicVerbNoun.noun + "\t\tHebrew: " + hebrewVerbNoun.noun);
		}
		*/
		
		
		
		
		/**
		 * 	Test: input from file	
		 */
		
		
		File arabicFile = new File("arabic.txt");
		File hebrewFile = new File("hebrew.txt");
		Scanner inputArabic = new Scanner(arabicFile);
		Scanner inputHebrew = new Scanner(hebrewFile);
		
		String ArabicSentence = inputArabic.nextLine();
		String HebrewSentence = inputHebrew.nextLine();
		while(inputArabic.hasNext() && inputHebrew.hasNext()) 
		{
			System.out.println("\n\n**********************************************************");
			System.out.println(ArabicSentence);
			System.out.println(HebrewSentence);
			
			VerbNoun hebrewVerbNoun =  sentenceFirstVerbAndNoun(HebrewSentence, Language.HEBREW);
			VerbNoun arabicVerbNoun = sentenceFirstVerbAndNoun(ArabicSentence, Language.ARABIC);
			if(arabicVerbNoun.verb != "" && hebrewVerbNoun.verb != ""){
				System.out.println("Arabic: " + arabicVerbNoun.verb + "\t\tHebrew: " + hebrewVerbNoun.verb);
			}
			if(arabicVerbNoun.noun != "" && hebrewVerbNoun.noun != ""){
				System.out.println("Arabic: " + arabicVerbNoun.noun + "\t\tHebrew: " + hebrewVerbNoun.noun);
			}
			
			ArabicSentence = inputArabic.nextLine();
			HebrewSentence = inputHebrew.nextLine();
		}
		inputArabic.close();
		inputHebrew.close();

		
		/**
		 *  	Test n.2: Buckwalter translertation to utf8 arabic.
		 */
		/*
		// from buckwalter to unicode and vice versa
		ArabicText arabicText = new ArabicText("العالم تغيّر");
		System.out.println(arabicText.toBuckwalter());
		System.out.println(ArabicText.fromBuckwalter(arabicText.toBuckwalter()).toString());
		*/
		
		
		
		
		/**
		 * 		Test n.3: Running Perl code in Java
		 */
		/*
		try {
			String word = "AlslAm";
			String cmd2 = "C:/strawberry/perl/bin/perl.exe  saed_root.pl " + word;
			Process x = Runtime.getRuntime().exec(cmd2);
			try {
				x.waitFor();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			BufferedReader input = new BufferedReader(new InputStreamReader(x.getInputStream()));	
			String line;
//			while ((line = input.readLine()) != null) {
//				System.out.println(line);
//			}
			line = input.readLine();
			System.out.println(line);
			//line = input.readLine();
			//input.close();
			String[] roots = line.split("\t");
			System.out.println(roots[0]);
		} catch (IOException e) {
			System.out.println("ERROR: running perl script failed.");
			e.printStackTrace();
		}
		*/
		
		
	}
}
