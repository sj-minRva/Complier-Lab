%{
    #include <stdio.h>
%}

EMAIL [a-z0-9._%+-]+@gmail\.com

%%
{EMAIL}    { printf("Valid Gmail address: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter an email address: ");
    fflush(stdout);
    yylex();
    return 0;
}

