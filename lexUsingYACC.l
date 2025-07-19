%{
#include <stdio.h>
%}

DIGIT      [0-9]
ID         [_a-zA-Z][_a-zA-Z0-9]*
KEYWORD    (if|else|while|int)
OP         (">="|"<="|">"|"<"|"="|"+"|"-"|"*"|"/")
SPECIALCHAR [\{\}\(\)\;\,]

%%

{KEYWORD}      { printf("%s is a keyword\n", yytext); }
{ID}           { printf("%s is an ID\n", yytext); }
{DIGIT}+       { printf("%s is a digit\n", yytext); }
{OP}           { printf("%s is an operator\n", yytext); }
{SPECIALCHAR}  { printf("%s is a Special character\n", yytext); }

%%

int main()
{
    printf("Enter the string:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}

