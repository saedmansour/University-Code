/***************************************************************************
 *
 * File name: q2.c
 *
 *
 *
 * Exercise: 1
 * Question: 2
 *
 *
 **************************************************************************/



/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

#define MIN_RATE 0
#define MAX_RATE 3
#define MIN_MONEY 0
#define PRIME_INTEREST_RATE 0.3



/*-------------------------------------------------------------------------
  The main program. (The program inputs an interest rate and an amount of money for two years, and calculates the NVP. )
 -------------------------------------------------------------------------*/
int main() 
{
	double interest_rate,npv;
	int amount_of_money1,amount_of_money2;

	//Input section
	
	printf("Please enter the interest rate: ");
	if (scanf("%lf" , &interest_rate)!=1)
		return 0;
	printf("Please enter the amount of money in the first year: ");
	if (scanf("%d", &amount_of_money1)!=1)
		return 0;
	printf("Please enter the amount of money in the second year: ");
    if (scanf("%d", &amount_of_money2)!=1)
		return 0;

	//Error checking section
	if (    !(interest_rate < MAX_RATE && interest_rate >= MIN_RATE)  ||  !( amount_of_money1 >= MIN_MONEY ) ||  !( amount_of_money2 >= MIN_MONEY)   ){
	   printf("BAD INPUT!\n");
	} 
	//Main program and Output section
	else {
	   if ( interest_rate > PRIME_INTEREST_RATE )
          interest_rate = PRIME_INTEREST_RATE;
          
       npv = amount_of_money1/(1+ interest_rate) + amount_of_money2 / ((1+ interest_rate) * (1+ interest_rate));
       printf ("The NPV is %.2lf using interest rate of %.2lf!\n ", npv, interest_rate);  
	}

	system("pause");
	return 0;
}


/**************************************************************************
                               End of file
***************************************************************************/
