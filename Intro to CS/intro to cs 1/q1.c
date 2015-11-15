/***************************************************************************
 *
 * File name: q1.c
 *
 *
 * Exercise: 1
 * Question: 1
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



/*-------------------------------------------------------------------------
  The main program. (The program inputs an interest rate and an amount of money. And calculate the NVP whereas F1=F2, T=2 )
 -------------------------------------------------------------------------*/
int main() 
{
	double interest_rate,npv ;
	int amount_of_money ;

	//Input section
	
	printf("Please enter the interest rate: ");
	if (scanf("%lf" , &interest_rate)!=1)
		return 0;
	printf("Please enter the amount of money: ");
	if(scanf("%d", &amount_of_money )!=1)
		return 0;

	//Error checking section
	if(  !(interest_rate < MAX_RATE && interest_rate >= MIN_RATE)  ||  !( amount_of_money >= MIN_MONEY) ) {
       printf("BAD INPUT!\n");
	} 
	else {
    //Main program and Output section
	npv = ( amount_of_money / (1+ interest_rate) ) 
		+ ( amount_of_money / ((1+ interest_rate) * (1+ interest_rate)) );
	printf ("The NPV is %.2lf!\n" , npv);
	}

    system("pause");
	return 0;
}


/**************************************************************************
                               End of file
***************************************************************************/
