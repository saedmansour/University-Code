/***************************************************************************
 *
 * File name: q4.c
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

#define ADD		    1
#define SUBSTRACT	2
#define QUIT		3




/*-------------------------------------------------------------------------
  The main program. (The program shows how many steps were done and what is the result. The results varies depending on options chosen: add,substract or quit(terminates the program) )
 -------------------------------------------------------------------------*/
int main() 
{
    int result=0, number,option, number_of_actions=0;
    
    do{    
        //Output section
		printf("\n\nThe result is %d, %d actions were done.\n", result, number_of_actions);
        
		//Input section
		printf("\nPlease choose one of the following options:\n 1.Add a number\n 2.Subtract a number\n 3.Quit\n");
        printf("\nWhat would you like to do?\n");
        if (scanf("%d", &option)!=1)
			return 0;

		//Main program section(chooses an option).
    
            switch(option){
                       case ADD:
                            printf("Please enter a number:");
                            if (scanf("%d",&number)!=1)
								return 0;
                            result += number;
                            break;
                       case SUBSTRACT:
                            printf("Please enter a number:");
                            if (scanf("%d",&number)!=1)
								return 0;
                            result -= number;
                            break;
                       case QUIT:
                            printf("\nGoodbye!\n");
                            break;
                       default:
                            printf("Error, there is no such option.\n");
							break;
            }       
    
			number_of_actions++;
    
	}while( option == 1 || option == 2); 
	
	system("pause");
	return 0;
}


/**************************************************************************
                               End of file
***************************************************************************/
