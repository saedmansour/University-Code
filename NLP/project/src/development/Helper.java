package development;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Set;


public class Helper {
	
	//used in getMatches() 
	private static final int minTranslationNum = 6;
	
	private static final String[] commonHebrewWords = {
		"של", "את", "על", "לא", "כי", "הוא", "אני", "זה", "עם", "גם", "כל", "יש",
		"אם", "היא", "מה", "או", "אבל", "אין", "הם", "כך", "היה", "בין", "יותר",
		"כדי", "רק", "אחד", "ב", "הזה", "זו", "אנחנו", "שלא", "עוד", "זאת", "לפני", 
		"ולא", "מי", "אל", "לאחר", "לי", "לו", "אך", "תודה", "כמו", "אתה", "בכל",
		"אותו", "מאוד", "שהוא", "היו", "להיות", "אלה", "הזאת", "צריך", "כבר", "אלא",
		"יהיה", "פי", "יכול", "ל", "כמה", "ה", "להם", "האם", "כ", "היתה", "שם", "בו", 
		"אפשר", "אותם", "אז", "שיש", "לנו", "אינו", "אף", "אחת", "מיליון", "הרב", "פה",
		"אשר", "וגם", "ללא", "לכל", "אחרי", "בבקשה", "ואני", "מספר", "הרבה", "עכשיו",
		"אותה", "בה", "יודע", "רבים", "שהם", "באופן", "אי", "לפי", "מ", "ש", "במהלך",
		"לה", "האלה", "בעקבות", "כפי", "פעם", "ו", "לכן", "אתם", "למה", "עדיין", "תהיה",
		"אולי", "טוב", "אחרים", "הן", "שאני", "לעבר", "והוא", "שלנו", "ועל", "שהיא",
		"שבו", "איך", "ואת", "שאין", "אחרת", "בהם", "לכך", "לבין", "שזה", "שהיה",
		"בתוך", "אנו", "לגבי", "אינה", "אפילו", "מאז", "בלתי", "הדבר", "הרי",
		"מהם", "שלהם", "בשל", "בפני", "שתי", "אלי", "כזה", "לתת", "שלי", "למרות", "ולכן",
		"אינם", "משום", "בגלל", "כלל", "מתוך", "תוך", "בכך", "בלי", "מול", "עצמו",
		"שאנחנו", "מס'", "שלושה", "קודם", "מנת", "וכן", "בעיקר", "עליו", "שלה",
		"יהיו", "המצב", "וכי", "מכל", "אלו", "לפחות", "לכם", "לעומת", "פחות",
		"הראשונה", "ראשון", "באמת", "כמעט", "ועוד", "מפני", "האחרון", "רבות",
		"ליד", "וזה", "שוב", "השני", "ואם", "לשעבר", "רוב", "ברור", "מדי",
		"האחרונות", "ככל", "הייתי", "בכלל", "כאלה", "א", "שלוש", "סמוך",
		"מעל", "כה", "שכל", "בעת", "דווקא", "הבא", "ואין", 
		"אחר", "כאשר", "רבה", "לך", "כאן"
	};
	
	private static final String[] commonArabicWords = {"لكن", "فى", "في", "أو", "لم", "و",
	"في", "من", "على", "ان", "الى", "التي", "عن", "الذي", "مع", "هذا", "هذه", 
	"ما", "لا", "بين", "أن", "ذلك", "كان", "بعد", "كل", "لم", "إلى", "بن", "كما",
	"او", "هو", "خلال", "انه", "حيث", "وفي", "قد", "وقد", "من", "في"} ;
	
	
	public static void hebrewSubtitleToSeperatedLines(){
		
		File hebrewFile = new File("hebrew_sub.txt");
		
		BufferedWriter out = null;
		
		try {
			out = new BufferedWriter(new FileWriter("hebrew_new.txt"));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	    
		Scanner inputHebrew = null;
		try {
			inputHebrew = new Scanner(hebrewFile);
			String line = inputHebrew.nextLine();
			while(inputHebrew.hasNext()) 
			{
				if(line.length() != 0 && !line.matches("[0-9]*") && !line.matches(".*-->.*")) {
					System.out.println(line);
					try {
						out.write(line+"\n");
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				line = inputHebrew.nextLine();
			}
			inputHebrew.close();
			try {
				out.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void arabicSubtitleToSeperatedLines(){
		
		File hebrewFile = new File("arabic_sub.txt");
		
		BufferedWriter out = null;
		
		try {
			out = new BufferedWriter(new FileWriter("arabic_new.txt"));
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		Scanner inputArabic = null;
		try {
			inputArabic = new Scanner(hebrewFile);
			String line = inputArabic.nextLine();
			while(inputArabic.hasNext()) 
			{
				if(line.length() != 0) {
					String newLine = line.split("}")[2];
					System.out.println(newLine);
					try {
						out.write(newLine +"\n");
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				line = inputArabic.nextLine();
			}
			inputArabic.close();
			try {
				out.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private static int getFileLinesNum(String fileName) {
		int linesNum = 0;
		try {
			File file = new File(fileName);
			Scanner fileScanner = new Scanner(file);
			while(fileScanner.hasNext()){
				fileScanner.nextLine();
				linesNum++;
			}
		} catch (FileNotFoundException e) {
			System.err.println("ERROR: getFileLinesNum: file doesn't exist. ");
			e.printStackTrace();
		}
		return linesNum;
	}
	
	public static String[][] fileToArray(String fileName){
		int fileLinesNum 	= getFileLinesNum(fileName);
		
		String[][] fileAsArray = new String[fileLinesNum][];
		try {
			File 	file 		 = new File(fileName);
			Scanner fileScanner  = new Scanner(file);
			int i = 0;
			while(fileScanner.hasNext()) 
			{
				String fileLine 	 = fileScanner.nextLine();
				String[] fileWords = fileLine.split(" +|\\t+");
				fileAsArray[i] = fileWords;
				i++;
			}
			fileScanner.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		return fileAsArray;
	}
		
	public static void editFileAndTag(String inputFilePath, String outputFilePath, Language language){
		try {
			File 	file 		 = new File(inputFilePath);
			Scanner fileScanner  = new Scanner(file);
			String fileLine 	 = fileScanner.nextLine();
			
			BufferedWriter out = null;
			try {
				out = new BufferedWriter(new FileWriter(outputFilePath));
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			
			while(fileScanner.hasNext()) 
			{
				fileLine = fileLine.trim();
				fileLine = fileLine.replaceAll("\\|", "\n");
				fileLine = fileLine.replaceAll("و ", "و");
				fileLine = fileLine.replaceAll(" +|\\p{Punct}|؟|–", " ");
				fileLine = fileLine.replaceAll(" +", " ");
				fileLine = fileLine.trim();

				try {
					String[] lines = fileLine.split("\n");
					for (String line : lines) {
						out.write(line+"\n");
						int wordsNum = line.split(" +").length;
						
						
						
						//UNKNOWN TAG
						String tagLine = "";
						for(int i = 0; i < wordsNum; i++) {
							tagLine += "UNKNOWN ";
						}
						
						
						// *****
						
						//TAGGED MORPHO
						/*TaggedWord[] taggedLine = MorphTagger.getPOStag(line, language);
						String tagLine = "";
						for (TaggedWord taggedWord : taggedLine) {
							tagLine += taggedWord.tag + " ";
						}
						tagLine = tagLine.trim();
						*/
						
						
						out.write(tagLine + "\n");
						// *****
						out.flush();
					}
				} catch (IOException e) {
					e.printStackTrace();
				}
				fileLine 	 = fileScanner.nextLine();
			}
			fileScanner.close();
			try {
				out.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	public static TaggedWord[][] getFileAsTaggedArray(String fileName){
		String[][] filesAsArray 		= fileToArray(fileName);
		TaggedWord[][] fileTagged 		= new TaggedWord[filesAsArray.length/2][];
		for (int i = 0, k = 0; i < filesAsArray.length; i+=2, k++) {
			fileTagged[k] = new TaggedWord[filesAsArray[i].length];
			for (int j = 0; j < filesAsArray[i].length && j < filesAsArray[i+1].length; j++) {
				fileTagged[k][j] = new TaggedWord(filesAsArray[i][j], MorphTagger.stringToTag(filesAsArray[i+1][j]));
			}
		}
		return fileTagged;
	}
	
	public static String toExpression(TaggedWord[] array){
		String result = "";
		for (TaggedWord taggedWord : array) {
			result += taggedWord.word + " ";
		}
		return result.trim();
	}

	
	public static IndexedWord getFirst(TaggedWord[] taggedSentence, Tag tag) {
		for (int i = 0; i < taggedSentence.length; i++) {
			if(taggedSentence[i].tag == tag){
				return new IndexedWord(taggedSentence[i].word, i);
			}
		}
		return null;
	}
	
	//tagged corpus
	public static void getMatches(String fileName1, String fileName2){
		TaggedWord[][] corpus1 = getFileAsTaggedArray(fileName1);
		TaggedWord[][] corpus2 = getFileAsTaggedArray(fileName2);
		LinkedList<TaggedWord[][]>  l = deleteCommonWords(corpus1, corpus2);
		corpus1 = l.get(0);
		corpus2 = l.get(1);
		
		HashMap<String, HashMap<String, Integer>> stat = new HashMap<String, HashMap<String, Integer>>(); 
		
		int j = 0;
		
		for (int i = 0; i < corpus1.length; i++) 
		{
			TaggedWord[] lineFromCorpus1 = corpus1[i];
			TaggedWord[] lineFromCorpus2 = corpus2[i];
			
			
			// collect word statistics
			// TODO: delete duplicated words from lineFromCorpus1
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
			
			
			
			int[] match = new int[lineFromCorpus1.length];
			
			IndexedWord firstNoun1 = getFirst(lineFromCorpus1, Tag.NOUN);
			IndexedWord firstNoun2 = getFirst(lineFromCorpus2, Tag.NOUN);
			IndexedWord firstVerb1 = getFirst(lineFromCorpus1, Tag.VERB);
			IndexedWord firstVerb2 = getFirst(lineFromCorpus2, Tag.VERB);
			 
			//if one sentence is consisted of one word
			if(lineFromCorpus1.length == 1 || lineFromCorpus2.length == 1) {
				j++;
				System.out.println("1-MATCH\t" + toExpression(lineFromCorpus1) + " : " + toExpression(lineFromCorpus2) + "\t line1: " + toExpression(lineFromCorpus1) + " - line 2: " + toExpression(lineFromCorpus2));
				continue;
			}
			
			//first noun match
			if(firstNoun1 != null && firstNoun2 != null){
				j++;
				System.out.println("NOUN MATCH\t" + firstNoun1.word + " : " + firstNoun2.word + "\t line1: " + toExpression(lineFromCorpus1) + ": line 2" + toExpression(lineFromCorpus2));
				match[firstNoun1.index] = firstNoun2.index;
				
				//2 length sentence: if first noun match and there are other words => match the rest

				/*if(!(firstVerb1 != null && firstVerb2 != null)) {
					if(lineFromCorpus1.length == 2 || lineFromCorpus1.length == 2) {
						System.out.println("2-MATCH\t " + toExpression(lineFromCorpus1).replaceAll(firstNoun1.word, "") + 
								" : " + toExpression(lineFromCorpus2).replaceAll(firstNoun2.word, ""));
						continue;
					}
				}
				*/
				
			}
			
			//first verb match
			if(firstVerb1 != null && firstVerb2 != null){
				j++;
				System.out.println("VERB MATCH\t" + firstVerb1.word + " : " + firstVerb2.word + "\t line1: " + toExpression(lineFromCorpus1) + ": line 2" + toExpression(lineFromCorpus2));
				match[firstVerb1.index] = firstVerb2.index;
				
				//2 length sentence: if first verb match and there are other words => match the rest
				/*if(!(firstNoun1 != null && firstNoun2 != null)) {
					if(lineFromCorpus1.length == 2 || lineFromCorpus1.length == 2) {
						System.out.println("2-MATCH\t " + toExpression(lineFromCorpus1).replaceAll(firstVerb1.word, "") + 
								" : " + toExpression(lineFromCorpus2).replaceAll(firstVerb2.word, ""));
						continue;
					}
				}*/				
			}
		} // for end
		
		//stat
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
				j++;
				System.out.println("C(word,translation) MATCH " + word + " : " + bestTranslation);
			}
		}
		System.out.println("**** matched words = " + j);
	}
	
	
	
	
	public static void getMatchesByOccurence(String fileName1, String fileName2){
		TaggedWord[][] corpus1 = getFileAsTaggedArray(fileName1);
		TaggedWord[][] corpus2 = getFileAsTaggedArray(fileName2);
		LinkedList<TaggedWord[][]>  l = deleteCommonWords(corpus1, corpus2);
		corpus1 = l.get(0);
		corpus2 = l.get(1);
		
		HashMap<String, HashMap<String, Integer>> stat = new HashMap<String, HashMap<String, Integer>>(); 
		
		int j = 0;
		
		for (int i = 0; i < corpus1.length; i++) 
		{
			TaggedWord[] lineFromCorpus1 = corpus1[i];
			TaggedWord[] lineFromCorpus2 = corpus2[i];
			
			
			// collect word statistics
			// TODO: delete duplicated words from lineFromCorpus1
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

		//statistics
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
				j++;
				System.out.println("C(word,translation) MATCH " + word + " : " + bestTranslation);
			}
		}
		System.out.println("**** matched words = " + j);
	}
	
	
	
	
	
	
	
	
	
	
	public static LinkedList<TaggedWord[][]> deleteCommonWords(TaggedWord[][] corpus1, TaggedWord[][] corpus2) {
		LinkedList<LinkedList<TaggedWord>> corpus1NewAsList = new LinkedList<LinkedList<TaggedWord>>();
		LinkedList<LinkedList<TaggedWord>> corpus2NewAsList = new LinkedList<LinkedList<TaggedWord>>();
		
		for (int i = 0; i < corpus1.length && i < corpus2.length; i++) {
			LinkedList<TaggedWord> sentence1 = new LinkedList<TaggedWord>();
			LinkedList<TaggedWord> sentence2 = new LinkedList<TaggedWord>();
			
			sentence1 = deleteCommonWordsFromArray(corpus1[i]);
			sentence2 = deleteCommonWordsFromArray(corpus2[i]);
			
			if(!sentence1.isEmpty() && !sentence2.isEmpty()){
				corpus1NewAsList.add(sentence1);
				corpus2NewAsList.add(sentence2);
			}
		}
		LinkedList<TaggedWord[][]>res = new LinkedList<TaggedWord[][]>();
		res.add(0, listToCorpus(corpus1NewAsList));
		res.add(1, listToCorpus(corpus2NewAsList));
		return res;
	}

	private static TaggedWord[][] listToCorpus(LinkedList<LinkedList<TaggedWord>> list) {
		TaggedWord[][] result = new TaggedWord[list.size()][];
		int i = 0;
		for (LinkedList<TaggedWord> linkedList : list) {
			TaggedWord[] temp = new TaggedWord[linkedList.size()];
			TaggedWord[] sentence = linkedList.toArray(temp);
			result[i] = sentence;
			i++;
		}
		return result;
	}

	private static boolean isInArray(String[] array, String str){
		for (String string : array) {
			if(str.equals(string)){ return true;};
		}
		return false;
	}
	
	private static LinkedList<TaggedWord> deleteCommonWordsFromArray(TaggedWord[] taggedWords) {
		LinkedList<TaggedWord> result = new LinkedList<TaggedWord>();
		for (TaggedWord taggedWord : taggedWords) {
			if (!isInArray(commonArabicWords, taggedWord.word) &&
				!isInArray(commonHebrewWords, taggedWord.word)) {
				result.add(taggedWord);
			}
		}
		return result;
	}

	// Convert an array of strings to one string.
	// Put the 'separator' string between each element.
	private static String arrayToString(String[] a) {
		String separator = " ";
	    StringBuffer result = new StringBuffer();
	    if (a.length > 0) {
	        result.append(a[0]);
	        for (int i=1; i<a.length; i++) {
	            result.append(separator);
	            result.append(a[i]);
	        }
	    }
	    return result.toString();
	}
	
	public static void tagCorpus(String corpusFilePath, String outputFilePath, Language language){
		FileWrite  writer = new FileWrite(outputFilePath);
		
		String[][] lines = fileToArray(corpusFilePath);
		for (int i = 0; i < lines.length; i+=2 /* Skips tags */) {	
			TaggedWord[] taggedLine = MorphTagger.getPOStag((arrayToString(lines[i])), language);
			writer.writeLine(arrayToString(lines[i]));
			String tagLine = "";
			for (TaggedWord taggedWord : taggedLine) {
				tagLine += taggedWord.tag + " ";
			}
			writer.writeLine(tagLine.trim());
		}
	}
	
	public static void frequentFileConvert() {
		String[][] f = fileToArray("corpus/hebrew/frequent_words.txt");
		for (String[] strings : f) {
			System.out.print("\"" + strings[0]  + "\", ");
		}
	}
		
	public static void main(String args[]) {
		// TEST: match two POS tagged files.
		//System.out.println("PART1");
		//getMatches("corpus/arabic/tagged/part1.txt", "corpus/hebrew/tagged/part1.txt");
		//System.out.println("\n\n\n\n\nPART2");
		//getMatches("corpus/arabic/tagged/part2.txt", "corpus/hebrew/tagged/part2.txt");
		
		
		
		//getMatches("corpus/arabic/tagged/part1_2.txt", "corpus/hebrew/tagged/part1_2.txt");
		
		
		// TEST: separated-line file => tagged
		// PART1: Arabic subtitles file
		// editFileAndTag("corpus/arabic_sub_edited_part2.txt", "corpus/arabic_tagged_part2.txt");
		// PART2: Hebrew subtitles file
		//editFileAndTag("corpus/hebrew_sub_edited_part2.txt", "corpus/hebrew_tagged_part2.txt");
		
		
		// TEST: tag a corpus automatically
		//tagCorpus("corpus/arabic/pre_tagged/part2.txt", "corpus/arabic/tagged/part2.txt", Language.ARABIC);
		//tagCorpus("corpus/hebrew/pre_tagged/part2.txt", "corpus/hebrew/tagged/part2.txt", Language.HEBREW);
		//Set<String> tags = MorphTagger.tags.keySet();
		//System.out.println(tags.toString());
		
		//frequency
		//frequentFileConvert();
		
		
		/*
		 *  GIZA file table => choose only best probability translation
		 * 
		try {
			System.setOut(new PrintStream("corpus/giza.i10.t_H.final_large_bestP"));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		String[][] file = fileToArray("corpus/giza.i10.t_H.final_large");
		int i = 0;
		while (i < file.length)
		{
			String word 		= file[i][1];
			double maxCurrP 	= Double.parseDouble(file[i][3]);
			String translation 	= file[i][2];  
			while(file[i][1].equals(word))
			{
				if(Double.parseDouble(file[i][3]) > maxCurrP) {
					maxCurrP = Double.parseDouble(file[i][3]);
					translation = file[i][2];
				}
				i++;
			}
			System.out.println(translation + ":" + word);
			//i++;
		} 
		*/
		
		
		
		
		/*
		 *		TEST:  
		 */
		
		/**/ 
		String[][] file = fileToArray("corpus/giza_verify");
		int i = 0;
		for (String[] strings : file) {
			for (String string : strings) {
				if(string.matches(".*\\*.*")){
					i++;
				}
			}
		}
		System.out.println(i);
		/**/
		
		
		
		
		//6 movies hebrew and arabic => tag as unkonwn
		
		/*
		
		editFileAndTag("corpus/arabic/non_tagged/movies/1.txt", 
					"corpus/arabic/tagged/movies/1.txt", null);
		editFileAndTag("corpus/arabic/non_tagged/movies/2.txt", 
				"corpus/arabic/tagged/movies/2.txt", null);
		editFileAndTag("corpus/arabic/non_tagged/movies/3.txt", 
				"corpus/arabic/tagged/movies/3.txt", null);
		editFileAndTag("corpus/arabic/non_tagged/movies/4.txt", 
				"corpus/arabic/tagged/movies/4.txt", null);
		editFileAndTag("corpus/arabic/non_tagged/movies/5.txt", 
				"corpus/arabic/tagged/movies/5.txt", null);
		editFileAndTag("corpus/arabic/non_tagged/movies/6.txt", 
				"corpus/arabic/tagged/movies/6.txt", null);
		

		editFileAndTag("corpus/hebrew/non_tagged/movies/1.txt", 
				"corpus/hebrew/tagged/movies/1.txt", null);
		editFileAndTag("corpus/hebrew/non_tagged/movies/2.txt", 
			"corpus/hebrew/tagged/movies/2.txt", null);
		editFileAndTag("corpus/hebrew/non_tagged/movies/3.txt", 
			"corpus/hebrew/tagged/movies/3.txt", null);
		editFileAndTag("corpus/hebrew/non_tagged/movies/4.txt", 
			"corpus/hebrew/tagged/movies/4.txt", null);
		editFileAndTag("corpus/hebrew/non_tagged/movies/5.txt", 
			"corpus/hebrew/tagged/movies/5.txt", null);
		editFileAndTag("corpus/hebrew/non_tagged/movies/6.txt", 
			"corpus/hebrew/tagged/movies/6.txt", null);
		
		
		*/
		
		/*
		 * EACH BY ITS OWN
		 * 
		try {
			for(int i = 1; i <= 6; i++){
				System.setOut(new PrintStream("corpus/result" + i + ".txt"));
				getMatchesByOccurence("corpus/arabic/tagged/movies/"+  i + ".txt", "corpus/hebrew/tagged/movies/" + i + ".txt");
			}
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
		
		
		
		/*
		try {
			System.setOut(new PrintStream("corpus/combined_result_6.txt"));
			getMatchesByOccurence("corpus/arabic/tagged/movies/combined.txt", "corpus/hebrew/tagged/movies/combined.txt");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
		 
		
		
	}
}
