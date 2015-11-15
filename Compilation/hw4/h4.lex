
%{
#include "h4.hpp"
#include "h4.tab.hpp"
%}
%option noyywrap
%option yylineno
%%



[\n\t ]						{yylval.name = yytext ;}
"//"[^\n]*\n					{yylval.name = yytext ;}

"if" 						{yylval.name = yytext; return _if_;}
"else" 						{yylval.name = yytext; return _else_;}
"while" 						{yylval.name = yytext; return _while_;}
"break" 						{yylval.name = yytext; return _break_;}

"show" 						{yylval.name = yytext ;return _show_;}
[kK]ilogram|kg				    	{yylval.name = yytext ;yylval.type = _kg_;return _kg_;}
[gG]ram|g					{yylval.name = yytext ;yylval.type = _gram_;return _gram_;}
[mM]illigram|mg				{yylval.name = yytext ;yylval.type = _mg_;return _mg_;}

[kK]ilometer|km				{yylval.name = yytext ;yylval.type = _km_;return _km_;}
[mM]eter|m					{yylval.name = yytext ;yylval.type = _meter_;return _meter_;}
[cC]entimeter|cm			    	{yylval.name = yytext ;yylval.type = _cm_;return _cm_;}

[kK]ilometer^2|km^2			    	{yylval.name = yytext ;yylval.type = _km2_;return _km2_;}
[mM]eter^2|m^2				{yylval.name = yytext ;yylval.type = _meter2_;return _meter2_;}
[cC]entimeter^2|cm^2		    		{yylval.name = yytext ;yylval.type = _cm2_;return _cm2_;}

[kK]ilometer^3|km^3			    	{yylval.name = yytext ;yylval.type = _km3_;return _km3_;}
[mM]eter^3|m^3				{yylval.name = yytext ;yylval.type = _meter3_;return _meter3_;}
[cC]entimeter^3|cm^3		    		{yylval.name = yytext ;yylval.type = _cm3_;return _cm3_;}


\+						{yylval.name = yytext ;return _plus_;}
\-						{yylval.name = yytext ;return _minus_;}
\*						{yylval.name = yytext ;return _mult_;}
\/						{yylval.name = yytext ;return _div_;}

">"						{yylval.name = yytext ;return _greater_;}
">="						{yylval.name = yytext ;return _greater_equals_;}
"<"						{yylval.name = yytext ;return _less_;}
"<="						{yylval.name = yytext ;return _less_equals_;}
"=="						{yylval.name = yytext ;return _equals_;}
"!="						{yylval.name = yytext ;return _not_equals_;}

"and"						{yylval.name = yytext ;return _and_;}
"or" 						{yylval.name = yytext ;return _or_;}
"not"						{yylval.name = yytext ;return _not_;}
"true"						{yylval.name = yytext ;return _true_;}
"false"						{yylval.name = yytext ;return _false_;}


\"[^"]*\"					    	{yylval.name = yytext; return _string_; }


\(						{yylval.name = yytext ;return _leftP_;}
\)						{yylval.name = yytext ;return _rightP_;}
\{						{yylval.name = yytext ;return _blockStart_;}
\}						{yylval.name = yytext ;return _blockEnd_;}
\;						{yylval.name = yytext ;return _end_;}
,						{yylval.name = yytext ;return _comma_;}
\=						{yylval.name = yytext ;return _assign_;}
[1-9][0-9]*|0|[0]\.[0-9]+|[1-9][0-9]*\.[0-9]+	{yylval.name = yytext ;yylval.val = atof(yytext); return _number_;}
[a-z][a-zA-Z0-9_]*	    			{yylval.name = yytext ; return _id_;}
.						{errorLex(yylineno, yytext); exit(1);}
%%