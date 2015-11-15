/*************************************************************************** 
* File name: q4.c
*
* Exercise :2
* Question :4
*
*
**************************************************************************/

/*-------------------------------------------------------------------------
Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>

/*=========================================================================
Constants and definitions:
==========================================================================*/

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define WRONG_INPUT -1
#define MAX_BASE 36

/*=========================================================================
Functions:
==========================================================================*/


//This function returns the minimum base of a charchter
int minimum_base(char ch){
	if(ch >= '0' && ch <='9')
		return ch-'0'+1;     //+1 because base=max charchter + 1
	else if(ch >= 'a' && ch <='z')
		return ch-'a'+10+1;
	else
		return WRONG_INPUT; //Later checked in main
}

/*-------------------------------------------------------------------------
Gets a number and calculates its value in the minimum base possible.
-------------------------------------------------------------------------*/

int main(){
	long num_max_base=0,i , c, number = 0; //num_max_base would hold the inputted number in decimal supposing it's in MAX_BASE
	int digit, min_base=0, cur_min_base=0, digits_num = 0;
	
	//Intro Section
	printf("Please type in your number:");

    //Main program
	while( (digit=getchar()) != '\n'){
		
		cur_min_base = minimum_base(digit);	//Put this in a variable so the function would'nt be called twice
		if(cur_min_base == WRONG_INPUT){   //Input Error Handler , EOF check included
			printf("You have entered something other than a digit or a lowercase letter");
			return EXIT_FAILURE;
		}
		min_base = (cur_min_base > min_base) ? cur_min_base : min_base;
		num_max_base = (cur_min_base-1) + num_max_base * MAX_BASE; //cur_min_base - 1 is the current digit in decimal      
		digits_num++;
	}

	for(i=0; i < digits_num; ++i){
		c = num_max_base % MAX_BASE;  //c acts as the digit in the 36 base
		num_max_base /= MAX_BASE;
		number += c * pow(min_base, i);
	}
	
	//Output section
	//Output section
    printf("The smallest possible base for the number is %d\n", min_base);
    printf("The decimal value of that number in base %d is %ld\n", min_base, number);

    return EXIT_SUCCESS;
}

/**************************************************************************
                               End of file
***************************************************************************/
