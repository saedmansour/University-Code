/***************************************************************************
* File name: q2.c
*
* Exercise :2
* Question :2
*
*
**************************************************************************/

/*-------------------------------------------------------------------------
Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>

#define EXIT_SUCCESS 0

/*-------------------------------------------------------------------------
This code analyzes vowels existeness in different languages. And how often they appear in a given text.
-------------------------------------------------------------------------*/


int main(){
	int c, letters_num=0, i, vowels_num=0;
	int vowels[2][5] ={ {0,0,0,0,0} , {'a','e','i','o','u'} } ;  //First line is vowels counter, second to store the letters
	double percents[2][5] = {0};    //First line percents from vowels, second percent from all
    
    //Introduction section
    printf("Please enter a phrase to produce analysis about the vowels in this language:\n");
	
	//Main Program
    while((c = getchar()) != EOF){
		if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ){    //To avoid non-letters
            letters_num++;
    		for(i = 0; i <= 4; ++i)
    			if(c == vowels[1][i] || c == vowels[1][i]-'a'+'A')   //Comparison to lower/upper case
    				vowels[0][i]++;
        }
	}

	for(i = 0; i <= 4; ++i)
		vowels_num += vowels[0][i];
		
	//Percentages calculation
    for(i = 0; i <= 4; ++i){
        if(vowels_num) //To avoid division by zero
              percents[0][i] = (double)vowels[0][i] / vowels_num*100; // % vowel from vowels
        if(letters_num)
              percents[1][i] = (double)vowels[0][i] / letters_num*100; // % vowel from all
    }
    
	//Output section
    for(i = 0; i <= 4; i++)
		printf("%c\\%c%10d%10d%10d%10.2lf%% %10.2lf%%\n", vowels[1][i]-'a'+'A', vowels[1][i], vowels[1][i]-'a'+'A', vowels[1][i], vowels[0][i], percents[0][i], percents[1][i]);

	return EXIT_SUCCESS;
}

/**************************************************************************
                               End of file
***************************************************************************/
