/***************************************************************************
* File name: q3.c
*
*
* Exercise :2
* Question :3
*
*
**************************************************************************/

/*-------------------------------------------------------------------------
Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1 

/*-------------------------------------------------------------------------
This program acts as a semi-calculator
-------------------------------------------------------------------------*/
int main(){
	
    double num = 0, mul = 0;  //num will store the number, mul would contain multiplications
	double before_mul, new_num;  //If necessary new_num would containt the new number
	char scanf_error[] = "\nInput failed!\n";
	int ch;
	
	//Introduction section
    printf("Please enter an expression to be calculated, possible charchters are numbers and * / + -, end your expression with =\n");
	
    //Input and Error checking section
    if(scanf("%lf", &before_mul) < 1) { printf(scanf_error); return EXIT_FAILURE; }
	while((ch = getchar()) == ' '); //This gets the first charchter after spaces if any.                                          
	if(ch == '=' || ch == '+' || ch == '-')num=before_mul;   //To avoid adding num to itself in num+=mul
	
    //Operator Errors, Checking for EOF becomes unnecessary
    //The usage of + instead of OR eliminates the "Lazy Evaluation". "+" acts as logical OR
    if( !( (ch == '=') + (ch == '+') + (ch == '-') + (ch == '*') + (ch == '/') )){  
        printf("\nError:Operator %c cannot be used\n", ch);
        return EXIT_FAILURE;
    }  
    
    
    //Calculation section
    while (ch != '=')
	{
		while ( ch == '*' || ch == '/')			
		{
			if(scanf("%lf", &new_num) < 1){ printf(scanf_error); return EXIT_FAILURE;}
			if(ch == '*') 
                     mul = before_mul * new_num;
			if(ch == '/'){
                     if(new_num == 0){ printf("Error! division by zero occurred!"); return EXIT_FAILURE; }
                     mul = before_mul / new_num;
            }
			before_mul = mul;
			while((ch = getchar()) == ' ');
		}
		
        num += mul;
		
		//This handles +-. It treats the number after the +- as a beginning of a new multiplication
		if( (ch == '+') || (ch == '-') ){
			if(scanf("%lf", &before_mul) < 1){ printf(scanf_error); return EXIT_FAILURE;}
            mul = (ch == '+') ? before_mul: before_mul * (-1);//To distinguish +, - 
            while((ch=getchar()) == ' '); 
            if(ch == '=') num += mul; //So it will be added if the loop ends  
		}
		
		//Operator error Check, EOF becomes unnecessary
        if( !( (ch == '=') + (ch == '+') + (ch == '-') + (ch == '*') + (ch == '/') )) {
            printf("\nError:Operator %c cannot be used\n", ch); return EXIT_FAILURE;
        }
		
	}
	
	//Output Section
	printf("%lf", num);
	
    return EXIT_SUCCESS;
}

/**************************************************************************
                               End of file
***************************************************************************/
