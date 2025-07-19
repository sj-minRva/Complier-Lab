%{
    #include <stdio.h>
    int number = 0;
%}

NUMBER [0-9]+

%%

{NUMBER} {
    sscanf(yytext, "%d", &number);
    if (number % 2 == 0)
        printf("%d is even\n", number);
    else
        printf("%d is odd\n", number);
}
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter a number: ");
    fflush(stdout); // Ensure prompt is shown before input
    yylex();
    return 0;
}

