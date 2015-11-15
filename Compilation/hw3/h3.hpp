#ifndef _H3_HPP_
#define _H3_HPP_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <stack>
using namespace std;



void errorLex (int lineno, const char* wrongtext);
void errorSyn (int lineno, const char* wrongtext);
void errorUndef (int lineno, const char* id);
void errorDef (int lineno, const char* id);
void errorMismatch (int lineno, int type1, int type2);
string freshTemp();
void endScope (int depth);
void printVar (const char* id, int type, int offset, bool isValidValue, double value);
void emitAOP (int lvalueOffset, int lvalueType, const char* rvalue1,  char aop,  const char* rvalue2);
void emitAssignment (int lvalueOffset, int lvalueType,  char* rvalue);
void emitId (int idOffset, int idType);
void emitString (char* str);
void emitConst (double val, int type);
const char* typeToString (int type);
char* expToNumber (double value, char buff[]);
char* expToLocation (int offset, char buff[]);




//------------------------------------------------------------------------------
//------- YYSTYPE

typedef struct{
    string 		name;
    int			type;
	double 		val;
	string 		exp_type;
} yystype;
#define YYSTYPE yystype

extern int yylineno;



//------------------------------------------------------------------------------
//------- SymbolTable

struct t_symbol
{
	string 			name;
	unsigned int 	type;
	unsigned int 	offset;
	double 			value;
	bool 			isValidValue;
};
typedef struct t_symbol Symbol;

struct t_SymbolTable
{
	list<Symbol*>* 			symbols;
	struct t_SymbolTable*   parent;
};
typedef struct t_SymbolTable SymbolTable;  

#endif
