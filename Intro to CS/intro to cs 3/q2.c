/*************************************************************************** 
* File name: q2.c
*
* Exercise :3
* Question :2
*
*
**************************************************************************/

/*-------------------------------------------------------------------------
Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*=========================================================================
Constants and definitions:
==========================================================================*/

typedef float integer;	//To input variables that must be integers.
typedef enum boolean{false,true} boolean;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MAX_TRIES 12
#define DIGITS_NUM 4
#define TRUE 1
#define FALSE 0
#define BOOL 0
#define PGIAA 1

char input_error_message[] = "\n\n**Input error! please check your input and try again!**\n\n";

/*-------------------------------------------------------------------------
This is a game: The computer randomizes a number and the user tries to guess it.
-------------------------------------------------------------------------*/

//This function compares between the player's guess and the randomized number
void compare(int num[], int player_guess, int results[]){
	int i, j, guess_arr[DIGITS_NUM];
	for(i = 0; i < DIGITS_NUM; ++i)
	{
		guess_arr[i] = player_guess % 10;
		player_guess /= 10;
	}
	for(i = 0; i < DIGITS_NUM; ++i)
	{
		if(num[i] == guess_arr[i])
			results[BOOL]++;
		for(j = 0; j < DIGITS_NUM; ++j)
		{
			if( i == j ) continue;
			if(num[i] == guess_arr[j])
				results[PGIAA]++;
		}
	}
}

//This function randomizes a number
void random_number(int num[]){
	int i,j;
	for(i = 0; i < DIGITS_NUM; ++i)
	{
		num[i] = rand()%9 + 1;
		for(j = 0; j < i;  ++j)
			while(num[i] == num[j]){
				num[i] = rand()%9 + 1;
				j = 0;
			}
	}
}

//This function returns how many digits a number has.
int digits_num(int num){
	int digits_num = 0;
	do{
		num /= 10;
		digits_num++;
	} while(num != 0);
	return digits_num;
}


//This function raises power ten to a number
int pow_10(int num){
	int result = 1, i;
	for(i = 0; i<  num; ++i)
		result *= 10;
	return result;
}


//This function checks if the digits of a number are different.
boolean is_differ(int num){
	int i, j, temp;
	
	for(j = 0 ; j < DIGITS_NUM-1; ++j){
		temp = num;
		for( i = j; i < DIGITS_NUM-1; ++i){
            if(i==j) temp/=pow_10(j+1);
			if ( num / pow_10(j) % 10 ==  temp % 10)
				return false;
			temp/=10;
        }
	}
	return true;
}


//This function checks if the number's digits contain zeros.
boolean contains_zeros(int player_guess)
{
	int i, guess_arr[DIGITS_NUM];
	for(i = 0; i < DIGITS_NUM; ++i)
	{
		guess_arr[i] = player_guess % 10;
		player_guess /= 10;
	}
	for(i = 0; i < DIGITS_NUM; ++i)
		if(guess_arr[i] == 0)
			return true;
	return false;
}
int main(){
	
	integer player_guess;
	int tries_num, i, errors = 0, result;
	int comp_num[DIGITS_NUM] = {0}, results[2] = {0};

	srand(time(0));
	
		// --- Introduction section ---
	
	printf("Welcmome to \"BULL PGIAA\"!\n"
		   "The computer has chosen a %d digit number and you have to guess it.\n"
		   "Are you smart enough to do it in %d tries?\n", DIGITS_NUM, MAX_TRIES
		   );
	
		// --- Input & Main Program section ---

	random_number(comp_num);	//Randomize a number

    for(tries_num = 1; tries_num <= MAX_TRIES; tries_num++)
	{
		printf("\nTry no.%d\n", tries_num);
		printf("\nEnter your guess(%d digits):", DIGITS_NUM);
		while(true){
			if(scanf("%f", &player_guess) != 1)
			{
				printf(input_error_message);
				return EXIT_FAILURE;
			}
			/*if(errors += (player_guess != (int)player_guess))
				{ printf("You've typed a fractional number! Try again:");errors =0; continue;  }
			*/
			if(errors += (player_guess <= 0))
				{printf("You must type a positive number! Try again:");errors =0; continue;}
			if(errors += (digits_num((int)player_guess) != DIGITS_NUM))
				{printf("You must type a number with %d digits(or you typed the right number of"
						" digits but first digit zero) Try again:", DIGITS_NUM);errors =0; continue;  }
			if(errors += (is_differ((int)player_guess) == FALSE))
				{printf("You've typed a number that's digits aren't different. Try again:");errors =0; continue;  }
			if(errors += (contains_zeros(player_guess) == true) )
				{printf("The numeber you typed contains zeros. Try again:"); errors = 0; continue; }
			if(errors == 0)
				break;
		}
		results[0] = 0;	//Re - initalize
		results[1] = 0;
		compare(comp_num, (int)player_guess, results);
		
		/* This commented code prints the computer's guess
          for(i = DIGITS_NUM-1; i >= 0; --i)
			printf("%d",comp_num[i]);  
		*/
			
		printf("\n");
		
			// --- Output section ---
		
		printf("\n\t you have %dB %dP\n", results[0], results[1]);
		if( results[0] == DIGITS_NUM )
		{
			printf("***************************************************\n"
				   "Congratulations! you have guessed the number right!\n"
				   "***************************************************\n"
				   );
			break;
		}
	}
	if(results[0] != DIGITS_NUM)
		printf("You lose, you aren't as smart as you thought you were\n");

	return EXIT_SUCCESS;
}
/**************************************************************************
                         End of file
***************************************************************************/