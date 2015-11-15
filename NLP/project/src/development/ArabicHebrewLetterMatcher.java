package development;

import java.util.HashMap;

 
public class ArabicHebrewLetterMatcher 
{
	private HashMap<String, String[]> ArabicToHebrewLetterMatch = new HashMap<String, String[]>();
	private HashMap<String, String[]> HebrewToArabicLetterMatch = new HashMap<String, String[]>();
	
	public ArabicHebrewLetterMatcher() 
	{	
		ArabicToHebrewLetterMatch.put("ا", new String[] {"ן", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ئ", new String[] {"ן", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ء", new String[] {"ן", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ى", new String[] {"ן", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ة", new String[] {"ן", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ؤ", new String[] {"ן", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ب", new String[] {"ב", "פ"});
		ArabicToHebrewLetterMatch.put("ت", new String[] {"ת"});
		ArabicToHebrewLetterMatch.put("ة", new String[] {"ת", "ה"});
		ArabicToHebrewLetterMatch.put("ث", new String[] {"ת", "ש"});
		ArabicToHebrewLetterMatch.put("ج", new String[] {"ג"});
		ArabicToHebrewLetterMatch.put("ح", new String[] {"ח"});
		ArabicToHebrewLetterMatch.put("خ", new String[] {"כ", "ח"});
		ArabicToHebrewLetterMatch.put("د", new String[] {"ד"});
		ArabicToHebrewLetterMatch.put("ذ", new String[] {"ד"});
		ArabicToHebrewLetterMatch.put("ر", new String[] {"ר"});
		ArabicToHebrewLetterMatch.put("ز", new String[] {"ז"});
		ArabicToHebrewLetterMatch.put("س", new String[] {"ס", "ש"});
		ArabicToHebrewLetterMatch.put("ش", new String[] {"ש", "ס"});
		ArabicToHebrewLetterMatch.put("ص", new String[] {"ס", "א", "י", "ה"});
		ArabicToHebrewLetterMatch.put("ض", new String[] {"ד"});
		ArabicToHebrewLetterMatch.put("ط", new String[]{"ט", "ס"});
		ArabicToHebrewLetterMatch.put("ظ", new String[]{"ד", ""});
		ArabicToHebrewLetterMatch.put("ع", new String[]{"ע"});
		ArabicToHebrewLetterMatch.put("غ", new String[]{"ג", "ע"});
		ArabicToHebrewLetterMatch.put("ف", new String[]{"פ", "ף", "ב"});
		ArabicToHebrewLetterMatch.put("ق", new String[]{"כ", "ק"});
		ArabicToHebrewLetterMatch.put("ك", new String[]{"כ", "ק"});
		ArabicToHebrewLetterMatch.put("ل", new String[]{"ל"});
		ArabicToHebrewLetterMatch.put("م", new String[]{"ם", "מ"});
		ArabicToHebrewLetterMatch.put("ن", new String[]{"נ", "ן"});
		ArabicToHebrewLetterMatch.put("ه", new String[]{"א", "ה"});
		ArabicToHebrewLetterMatch.put("و", new String[]{"ו", "א"});
		ArabicToHebrewLetterMatch.put("ي", new String[]{"י"});
		
		
		HebrewToArabicLetterMatch.put("א", new String[]{"ا"});
		HebrewToArabicLetterMatch.put("ב", new String[]{"ب"});
		HebrewToArabicLetterMatch.put("ג", new String[]{"ج"});
		HebrewToArabicLetterMatch.put("ד", new String[]{"د"});
		HebrewToArabicLetterMatch.put("ה", new String[]{"ه", "ا"});
		HebrewToArabicLetterMatch.put("ו", new String[]{"و", "ؤ"});
		HebrewToArabicLetterMatch.put("ז", new String[]{"ز"});
		HebrewToArabicLetterMatch.put("ח", new String[]{"ح"});
		HebrewToArabicLetterMatch.put("ט", new String[]{"ط", "ت"});
		HebrewToArabicLetterMatch.put("י", new String[]{"ي"});
		HebrewToArabicLetterMatch.put("כ", new String[]{"ق", "ك"});
		HebrewToArabicLetterMatch.put("ך", new String[]{"ق", "ك"});
		HebrewToArabicLetterMatch.put("ל", new String[]{"ل"});
		HebrewToArabicLetterMatch.put("מ", new String[]{"م"});
		HebrewToArabicLetterMatch.put("ם", new String[]{"م"});
		HebrewToArabicLetterMatch.put("ן", new String[]{"ن"});
		HebrewToArabicLetterMatch.put("נ", new String[]{"ن"});
		HebrewToArabicLetterMatch.put("ס", new String[]{"س", "ص"});
		HebrewToArabicLetterMatch.put("ע", new String[]{"ع", "غ"});
		HebrewToArabicLetterMatch.put("פ", new String[]{"ف"});
		HebrewToArabicLetterMatch.put("ף", new String[]{"ف"});
		HebrewToArabicLetterMatch.put("צ", new String[]{"ص"});
		HebrewToArabicLetterMatch.put("ץ", new String[]{"ص"});
		HebrewToArabicLetterMatch.put("ק", new String[]{"ق", "ك"});
		HebrewToArabicLetterMatch.put("ר", new String[]{"ر"});
		HebrewToArabicLetterMatch.put("ש", new String[]{"ش", "س"});
		HebrewToArabicLetterMatch.put("ת", new String[]{"ت"});
	}
	
	public  boolean ArabicLetterHebrewLetterMatch(String arabicLetter, String hebrewLetter) 
	{	
		if(ArabicToHebrewLetterMatch.containsKey(arabicLetter))
		{
			String[] hebrewMatchedLetters = ArabicToHebrewLetterMatch.get(arabicLetter);
			
			for (String hebrewLetterIterator : hebrewMatchedLetters) {
				if(hebrewLetterIterator.equals(hebrewLetter)){
					return true;
				}
			}
		}
		return false;
	}
	
	// returns "percentage" of match
	public  double ArabicToHebrewWordMatchPercent(String arabicWord, String hebrewWord) 
	{
		double totalMatches = 0;
		
		char[] arabicWordCharArray  = arabicWord.toCharArray();
		char[] hebrewWordCharArray  = hebrewWord.toCharArray();
		
		
		for (char arabicLetter : arabicWordCharArray) {
			for (char hebrewLetter : hebrewWordCharArray) {
				if(ArabicLetterHebrewLetterMatch(Character.toString(arabicLetter), 
						Character.toString(hebrewLetter)))
				{
					totalMatches++;
					break;
				}
			}
		}
		
		return totalMatches/arabicWord.length();
	}
	
	public static void main(String[] args){
		ArabicHebrewLetterMatcher matcher = new ArabicHebrewLetterMatcher();
		
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("كلب", "כלב")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("ثور", "שור")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("هتا", "פה")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("ولد", "ילד")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("سائد", "סאאיד")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("عدي", "עדי")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("شمس", "שמש")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("تحرك", "זוז")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("ضفة", "גדה")
		);
		System.out.println(
				matcher.ArabicToHebrewWordMatchPercent("فرودو", "פרודו")
		);
	}
}
