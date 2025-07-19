%{
    int vow_count=0;
    int const_count=0;
%}
vowel [aeiouAEIOU]
consonant [a-zA-Z]
%%
{vowel}+ {vow_count++;}
[a-zA-Z] {const_count++;}
%%

int main()
{
    printf("enter string");
    yylex();
    printf("number of vowels: %d\n",vow_count);
    printf("number of consonants: %d",const_count);
    yylex();
}
int yywrap()
{
    return(1);
}