#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[10][10];
int n;

void FIRST(char c, int first[]);
void FOLLOW(char c, int follow[]);

int main() {
    int i, ch;
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (E=TX format):\n");
    for (i = 0; i < n; i++)
        scanf("%s", prod[i]);

    do {
        printf("\nEnter non-terminal: ");
        scanf(" %c", &ch);

        int first[256] = {0};
        int follow[256] = {0};

        FIRST(ch, first);
        printf("FIRST(%c) = { ", ch);
        for (i = 0; i < 256; i++)
            if (first[i]) printf("%c ", i);
        printf("}\n");

        FOLLOW(ch, follow);
        printf("FOLLOW(%c) = { ", ch);
        for (i = 0; i < 256; i++)
            if (follow[i]) printf("%c ", i);
        printf("}\n");

        printf("Continue? (1/0): ");
        scanf("%d", &i);
    } while (i == 1);

    return 0;
}

void FIRST(char c, int first[]) {
    if (!isupper(c)) { first[c] = 1; return; }
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (prod[i][2] == '$')
                first['$'] = 1;
            else
                FIRST(prod[i][2], first);
        }
    }
}

void FOLLOW(char c, int follow[]) {
    if (prod[0][0] == c)
        follow['$'] = 1;

    for (int i = 0; i < n; i++) {
        int len = strlen(prod[i]);
        for (int j = 2; j < len; j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0') {
                    int firstNext[256] = {0};
                    FIRST(prod[i][j + 1], firstNext);
                    for (int k = 0; k < 256; k++)
                        if (firstNext[k] && k != '$')
                            follow[k] = 1;
                    if (firstNext['$'])
                        FOLLOW(prod[i][0], follow);
                } else if (prod[i][0] != c)
                    FOLLOW(prod[i][0], follow);
            }
        }
    }
}