/***************************************************************************
 *
 * File name: q3.c
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

#define POWER 4



/*-------------------------------------------------------------------------
  The main program. (The program checks whether an inputted number is a power of another number(here four) )
 -------------------------------------------------------------------------*/
int main() 
{
     int num,initial_num ;
     int exponent = 0 ;

	//Input section
    printf("Enter an integer number: ");
    if (scanf("%d", &num)!=1)
		return 0;

	//Error checking section
    if ( !(num >= 1) ){
              printf("Invalid number!\n");
              system("pause");
              return 0;
    }
    
	//Main program and Output section
	initial_num = num ;
    while (num % 4 == 0) {
          num /= 4;
          exponent++;
    } 
    if (num == 1 ) 
            printf("%d is a power of %d, exponent=%d\n", initial_num, POWER, exponent);
    else 
            printf ("%d is not a power of %d\n", initial_num , POWER);
	

	system("pause");
	return 0;
}


/**************************************************************************
                               End of file
***************************************************************************/
