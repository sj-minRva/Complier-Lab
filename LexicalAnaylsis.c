#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100

// Check if the token is already processed
int isDuplicate(char tokens[][50], int count, const char *token) {
    for (int i = 0; i < count; i++) {
        if (strcmp(tokens[i], token) == 0)
            return 1;
    }
    return 0;
}

void lexicalAnalysis(const char *input) {
    char tempInput[200];
    strcpy(tempInput, input);

    char tokens[MAX_TOKENS][50];
    int tokenCount = 0;

    // Use delimiters to separate tokens
    const char *delimiters = " ;=+-*/(){}<>,";
    char *token = strtok(tempInput, delimiters);

    // Handle word tokens
    while (token != NULL) {
        if (!isDuplicate(tokens, tokenCount, token)) {
            strcpy(tokens[tokenCount++], token);

            if (strcmp(token, "int") == 0 || strcmp(token, "float") == 0 ||
                strcmp(token, "if") == 0 || strcmp(token, "else") == 0) {
                printf("Keyword: %s\n", token);
            }
            else if (isalpha(token[0]) || token[0] == '_') {
                printf("Identifier: %s\n", token);
            }
            else if (isdigit(token[0])) {
                printf("Literal: %s\n", token);
            }
            else {
                printf("Unknown token: %s\n", token);
            }
        }

        token = strtok(NULL, delimiters);
    }

    // Handle operators and punctuations separately
    for (int i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        char sym[2] = {ch, '\0'};

        if (strchr("=+-*/", ch)) {
            if (!isDuplicate(tokens, tokenCount, sym)) {
                strcpy(tokens[tokenCount++], sym);
                printf("Operator: %s\n", sym);
            }
        }
        else if (strchr("(){};,", ch)) {
            if (!isDuplicate(tokens, tokenCount, sym)) {
                strcpy(tokens[tokenCount++], sym);
                printf("Punctuation: %s\n", sym);
            }
        }
    }
}

int main() {
    char input[200];
    printf("Enter a line of code: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline

    lexicalAnalysis(input);
    return 0;
}
