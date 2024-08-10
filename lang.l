%{
#include "lang.tab.h"
#include <string.h>
extern int yylex();
%}

%option noyywrap

%%

[ \t\n]+                /* ignore whitespace */
"/*"([^*]|\*+[^*/])*"*/"    /* ignore comments */
"//".*                  /* ignore single-line comments */
"int"                   { return INT; }
"str"                   { return STR; }
"set"                   { return SET; }
"collection"            { return COLLECTION; }
"input"                 { return INPUT; }
"output"                { return OUTPUT; }
"if"                    { return IF; }
"else"                  { return ELSE; }
"while"                 { return WHILE; }
"for"                   { return FOR; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MUL; }
"/"                     { return DIV; }
"&"                     { return INTERSECT; }
"|"                     { return UNION; }
"=="                    { return EQ; }
"!="                    { return NEQ; }
"<="                    { return LE; }
">="                    { return GE; }
"<"                     { return LT; }
">"                     { return GT; }
"="                     { return ASSIGN; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
"["                     { return LBRACKET; }
"]"                     { return RBRACKET; }
";"                     { return SEMICOLON; }
","                     { return COMMA; }
":"                     { return COLON; }
[0-9]+                  { yylval.ival = atoi(yytext); return NUMBER; }
\"[^\"]*\"              { yylval.sval = strdup(yytext); return STRING_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return IDENTIFIER; }
.                       { printf("Unexpected character: %s\n", yytext); }

%%