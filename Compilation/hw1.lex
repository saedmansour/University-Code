%{
#include <stdio.h>

void showToken(char* s);
void handleVar();
int isVarExist(char* s);
void addVar(char* s);
void printVarList();
void freeVars();
int isEND = 0;
char* vars[32];
int varsNum = 0;
#define MAXLEN 17
%}

%option yylineno
%option noyywrap

%%

"END"		showToken("END");

"<"[a-zA-Z][a-zA-Z0-9]*([\t\n ]+[a-zA-Z][a-zA-Z0-9]*=\"[a-zA-Z0-9]*\")*">"		showToken("StartTag");

"</"[a-zA-Z][a-zA-Z0-9]*">"		showToken("EndTag");

([0-9]*\.[0-9]+)|([0-9]*[1-9][0-9]*(e("+"|"-")?)[0-9]+)|([0-9]*\.[0-9]+e("+"|"-")?[0-9]+)	showToken("Real");

(0|[1-9][0-9]*)		showToken("Integer");

[Vv][Aa][Rr]" "[a-zA-Z]([a-zA-Z]|[0-9])*		handleVar();		/* to make a wrap function that add the var to the ds*/																	

[a-zA-Z]+		showToken("String");

"<!--"(([^-])|(\-[^-])|(\-{2,}[^->]))*(\-{2,}">") 		showToken("Comment"); 

[\t\n ]		;

.					showToken("ERROR");


%%
void showToken(char* s)
{	
	if(strcmp(s,"END") == 0){
		isEND = 1;
		printVarList();
		freeVars();
		return;
	}
	if(!isEND){
		if(strcmp(s,"ERROR") == 0){
			printf("Error at line %d: %c\n", yylineno, yytext[0]);
			return;
		}
		if(strcmp(s,"Variable") == 0){
			printf("%s %s at line %d\n",s, yytext+4, yylineno);
			
		}else{
			printf("%s %s at line %d\n",s, yytext, yylineno);
		}
	}
}

void handleVar()
{
	if (isVarExist(yytext+4)){
		printf("Redefinition of existing variable \"%s\" at line %d\n",yytext+4, yylineno);
	}else{
		addVar(yytext+4);
		showToken("Variable");
	}
}

int isVarExist(char* s)
{
	int i;
	for (i = 0; i < varsNum; i++){
		if(strcmp(s,vars[i]) == 0){
			return 1;
		}
	}
	return 0;
}

void addVar(char* s)
{
	vars[varsNum] = (char*)malloc(MAXLEN);
	strcpy(vars[varsNum], s);
	varsNum++;
}

void printVarList()
{
	int i;
	printf("\nTotal number of vars = %d :\n", varsNum);
	for (i = 0; i < varsNum; i++){
		printf("We have a variable named %s\n",vars[i]);
	}
}

void freeVars()
{
	int i;
	for (i = 0; i < varsNum; i++){
		free(vars[i]);
	}
}
