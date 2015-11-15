/*************************************************************************** 
* File name: q3.c
*
* Exercise :3
* Question :3
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

/*
	OFR: Out Of Range. This value is used to initalize variables with a value that
	is out of the defined/requested/possible range.

	N: Locations number. Possible locations to travel to: 0 -> N-1

	STOP_INPUT: The user ends his list with this value.
	
	integer: To input variables that must be integers.
*/

#define N 12
#define OFR -2
#define STOP_INPUT -1
#define EXIT_SUCCESS 0 
#define EXIT_FAILURE -1

char input_error[] = "\nFatal Error! Input failed, there's a chance you typed a letter\n";

typedef float integer;	
typedef enum boolean{false, true} boolean;

/*-------------------------------------------------------------------------
This program inputs the locations that tourists desire to travel to, and
prints a graph showing how many tourists want to travel to every location.
-------------------------------------------------------------------------*/

//Prints a graph that describes how many tourists traveled to every location.
void print_graph(int loc_num, int loc_details[])
{
	int i, max_passengers = 0, cur_pass;
	
	for(i = 0; i < loc_num; ++i)
		max_passengers = max_passengers > loc_details[i] ? max_passengers: loc_details[i];
	
	cur_pass = max_passengers;
	printf("passengers\n");
	do{
		printf("%3d+ ", cur_pass);
		for(i = 0; i < loc_num; ++i)
		{
			if(loc_details[i] == cur_pass)
				printf(" -   ");
			else if(cur_pass < loc_details[i])
				printf("| |  ");
			else if(cur_pass > loc_details[i])
				printf("     ");     // 5 spaces
		}
		printf("\n");
		cur_pass--;
	} while( cur_pass != STOP_INPUT);	//The user must enter STOP_INPUT at the list's end.
		
	/* Prints a horizantal seperator line of pluses */
	printf("    +");	//4 spaces and +
	for(i = 0; i < loc_num; ++i)
		printf("+++++");	// 5 pluses
	printf("\n");
	
	/* Print the X axis */
	printf("      ");	//6 spaces
	for(i = 0; i < loc_num; ++i)
		printf("%-2d   ", i);	// %2d to left + 3 spaces
	printf("locations\n");
}

int main()
{
	int i, tour_num = 1, loc_details[N] = {0};
	integer prev_location, location;

	// --- Introduction section ---

	printf("Welcome. The possible locations you can travel to are: 0 -> %d,"
		   " please enter them in an ascending order. And don't forget to"
		   " end your list in -1\n", N - 1);

	// --- Input section ---
	
	while(1)
	{
			/*
				OFR: prev_location and location are initialized to OFR to avoid using
				the last values in them. Especially -1 which is inputted at the end.
			*/

			prev_location = OFR;
			location = OFR;
			printf("\n*Tourist number %d*\n", tour_num);
			while(location != STOP_INPUT)
			{
				printf("Enter a location you want to go to:");
				if(scanf("%f", &location) != 1)
				{
					printf(input_error); 
					return EXIT_FAILURE;
				}
				if(prev_location == OFR && location == STOP_INPUT) 
					break;	//The condition to stop input	
				if(location <= prev_location || location >= N || location != (int)location)
				{
					if(location != STOP_INPUT)
						printf("Invalid input! Please try again.\n");
					continue;	//To avoid the two next statement, and in case of STOP_INPUT, the loop ceases.
				}
				prev_location = location;
				loc_details[(int)location]++;
			}
			if(prev_location == OFR && location == STOP_INPUT) 
				break;	//Stop input completely
			tour_num++;
	}

	// --- Output section ---
	
	print_graph(N, loc_details);
	return 0;
}

/**************************************************************************
                         End of file
***************************************************************************/