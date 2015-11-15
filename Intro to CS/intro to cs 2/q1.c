/*************************************************************************** 
* File name: q1.c
*
*
**************************************************************************/

/*-------------------------------------------------------------------------
Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>

/*=========================================================================
Constants and definitions:
==========================================================================*/

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define MONTHS_PERIOD 6
#define MIN(x,y) ( (x)<(y)?(x):(y) )
#define SALE 15
#define MAX_INVEST_PERCENT 12
#define MIN_INVEST_PERCENT 0
#define MIN_SHARE_PRICE 0
#define MIN_SALARY 0
#define ZERO_DIV -1

/*-------------------------------------------------------------------------
This program inputs Moshon's salary, share price of his company, at the beginning
of a period, at the end of it and the percentage of investment which Moshe chooses.
Then calculates and prints his profit of selling these shares at the end of the period.
-------------------------------------------------------------------------*/


//This function calculates all the necessary calculations and prints the result
	
int print_output(int salary, int invest_percent, double share_price_begin, double share_price_end){

	double saved_amount, min_share,profit, share_price, left_amount, total;
	int shares_num;

	saved_amount = (invest_percent / 100.0) * salary * MONTHS_PERIOD;
	min_share = MIN(share_price_end, share_price_begin);
	share_price =  min_share*(100-SALE) / 100.0;
	if(share_price == 0) return ZERO_DIV;   //Avoid zero division
    shares_num = saved_amount / share_price;
	left_amount = saved_amount - shares_num*share_price; 
	profit = (share_price_end - share_price) * shares_num;
	total = share_price_end*shares_num + left_amount;

	printf("Moshon, you saved %.2lf NIS, your profit is %.2lf NIS and the total amount is %.2lf NIS.\n",saved_amount, profit, total);
    return 0;
}

int main(){

	int salary, invest_percent, s_err=0;	//s_err is a helping variable if scanf fails
	double share_price_begin,share_price_end;
	char input_error[] = "Error! Please verify your input and try again: ";

	//Input and error Section
	
	//Note: Checking for floats is no more necessary according to the course's staff
	
	printf("What is your salary Moshon? ");
	while( (s_err=scanf("%d", &salary)) < 1 || !(salary > MIN_SALARY) ){ 
		printf(input_error); 
		if(s_err<1) return EXIT_FAILURE;	//Quit if scanf fails
	}
	printf("How much percents[%d,...,%d] from your salary would you like to invest? ",MIN_INVEST_PERCENT,MAX_INVEST_PERCENT);
	while( (s_err= scanf("%d", &invest_percent)) < 1 || !(invest_percent>=MIN_INVEST_PERCENT && invest_percent<=MAX_INVEST_PERCENT) ){
		 printf(input_error);
		 if(s_err<1) return EXIT_FAILURE;
	}
	printf("What was the share price at the beginning of the period? ");
	while( (s_err=scanf("%lf", &share_price_begin)) < 1 || !(share_price_begin > MIN_SHARE_PRICE)) { 
		printf(input_error); 
		if(s_err<1) return EXIT_FAILURE;
	}	
	printf("What is the share price at the end of the period? ");
	while( (s_err=scanf("%lf", &share_price_end)) < 1  || !(share_price_end > MIN_SHARE_PRICE) ) { 
		printf(input_error); 
		if(s_err<1) return EXIT_FAILURE;
	}
	
	// Output Section

	if(print_output(salary, invest_percent, share_price_begin, share_price_end) == ZERO_DIV)
         printf("Error! Division by Zero occurred. Please check your input.");

	return EXIT_SUCCESS;
}

/**************************************************************************
                         End of file
***************************************************************************/
