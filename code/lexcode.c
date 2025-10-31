#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    
    char c, str[50];
    int lineno = 1, num, i = 0;

    char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void", "volatile",
        "while"
    };

    FILE *f1 = fopen("C:\\RHEA\\S7\\Complier-Lab\\code\\text.txt", "r");
    if (f1 == NULL) {
        printf("File not found!\n");
        return 0;
    }

    while ((c = getc(f1)) != EOF) {
        if (isdigit(c)) {
            num = c - 48;
            c = getc(f1);
            printf("%d is a number\n", num);
            ungetc(c, f1);  // push back the non-digit character
        }

        else if (isalpha(c) || c == '_') 
        {
            i = 0;
            str[i++] = c;
            c = getc(f1);
            while (isalnum(c) || c == '_') 
            {
                str[i++] = c;
                c = getc(f1);
            }
            str[i] = '\0';

            int isKeyword = 0;
            for (int j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++) 
            {
                if (strcmp(keywords[j], str) == 0) 
                {
                    printf("%s is a keyword\n", str);
                    isKeyword = 1;
                    break;
                }
            }

            if (!isKeyword)
                printf("%s is an identifier\n", str);

            ungetc(c, f1);
        }

        else if (c == '+' || c == '-' || c == '*' || c == '%' || c == '/' ||
                 c == '&' || c == '|' || c == '=' || c == '<' || c == '>') {
            printf("%c is an operator\n", c);
        }

        else if (c == ' ' || c == '\t') {
            continue;
        }

        else if (c == '\n') {
            lineno++;
        }

        else {
            printf("%c is a special symbol\n", c);
        }
    }

    printf("\nTotal lines: %d\n", lineno);
    fclose(f1);
    return 0;
}
