/*************************************************************************** 
* File name: q1.c
*
*
* Exercise :3
* Question :1
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

//integer: to input variables that must be integers
typedef float integer;	

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

char input_error[] = "Input error, please check your input and try again!\n";

/*-------------------------------------------------------------------------
This program inputs a number and calculates its COS.
-------------------------------------------------------------------------*/

//This function calculates the facotiral of n(n!).
double factorial(int num)
{
	int i;
	double factorial_num = 1;

	for(i = 1; i <= num; ++i)
	{
		factorial_num *= i;
	}
	return factorial_num;
}

//Calculate cos by a certain precision
int cos_precision(double num)
{
	double prec, cur_cos=0 , last_cos = 0;
	int n=0;

	printf("Enter precision:");
	do
	{
		if(scanf("%lf", &prec)< 1)
		{
			printf(input_error); 
			return EXIT_FAILURE;
		}
		if(prec <= 0) printf("\nError: precision must be bigger than zero. Try again:");
	}while( prec <= 0);

	do
	{
		last_cos = cur_cos;
		cur_cos += pow(-1,n) * pow(num, 2 * n) /  factorial(2 * n);
		n++;
	}while(!(fabs(last_cos - cur_cos) < prec));

	printf("COS(x) = %.12lf \nNumber of iterations:%d\n", cur_cos, n);
	return EXIT_SUCCESS;
}

//Calculte cos by number of iterations
int cos_iteration(double num)
{
	double last_cos = 0, cur_cos = 0;
	int i;
	integer n;	

	printf("Enter iterations:");
	do 
	{
		if(scanf("%f", &n) < 1)
		{
			printf(input_error); 
			return EXIT_FAILURE;
		}
		if(n < 1) printf("\nError: number of iterations shouldn't be less than 1. Try again:");
	}while(n < 1);
    
	
	for(i = 0; i < n; ++i)
	{ 
		last_cos = cur_cos;
		cur_cos += pow(-1,i) * pow(num, 2 * i) /  factorial(2 * i);
	}
	printf("COS(x) = %.12lf\nAccuracy reached: %.12lf\n ", cur_cos, fabs(last_cos - cur_cos));
	return EXIT_SUCCESS;
}

int main()
{
	integer option;
	double num;
	
	// --- Introduction section ---

	printf("Enter a number(e.g. x) to calculate COS(x):");
	
    // --- Input section ---
	
	if(scanf("%lf",&num) != 1)
	{
		printf(input_error); 
		return EXIT_FAILURE;
	}
	
	printf("Choose one of the following options:\n"
		   "\n\t1.Calculate by precision\n"
		   "\t2.Calculate by iterations\n"
		   ); 
	
	printf("Option:");
	
	while(1)
	{
		if(scanf("%f", &option) < 1)
		{
			printf(input_error); 
			return EXIT_FAILURE;
		}
		if(option == 1 || option == 2) 
			break;
		else
			printf("Invalid input! Please try again:", option);
	} 

	switch((int)option)
	{
		case 1:
				cos_precision(num);
				break;
		case 2:
				cos_iteration(num);
				break;
	}
	return 0;	// Not EXIT_SUCCESS/FAILURE because both are included
}

/**************************************************************************
                         End of file
***************************************************************************/
