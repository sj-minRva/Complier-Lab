


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 20
#define MAX_SYMBOLS 10
#define MAX_FIRST 20
#define MAX_FOLLOW 20
#define MAX_NON_TERMINALS 10

// Grammar storage
int ruleCount;
char nonTerminals[MAX_NON_TERMINALS];
int nonTerminalCount = 0;

char productions[MAX_RULES][MAX_SYMBOLS]; // each production's RHS
char productionHeads[MAX_RULES];          // each production's LHS
int productionSizes[MAX_RULES];

// First and Follow sets
char first[MAX_NON_TERMINALS][MAX_FIRST];
int firstCount[MAX_NON_TERMINALS];

char follow[MAX_NON_TERMINALS][MAX_FOLLOW];
int followCount[MAX_NON_TERMINALS];

int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

int getNonTerminalIndex(char c) {
    for (int i = 0; i < nonTerminalCount; i++) {
        if (nonTerminals[i] == c) return i;
    }
    return -1;
}

int contains(char arr[], int size, char c) {
    for (int i = 0; i < size; i++)
        if (arr[i] == c) return 1;
    return 0;
}

void addToSet(char arr[], int *size, char c) {
    if (!contains(arr, *size, c)) {
        arr[*size] = c;
        (*size)++;
    }
}

void addFirst(char c, int idx);

void computeFirst(int idx) {
    // idx = index of non-terminal
    for (int r = 0; r < ruleCount; r++) {
        if (productionHeads[r] == nonTerminals[idx]) {
            char *prod = productions[r];
            if (prod[0] == '@') { // epsilon
                addToSet(first[idx], &firstCount[idx], '@');
            } else {
                for (int i = 0; prod[i] != '\0'; i++) {
                    if (!isNonTerminal(prod[i])) {
                        addToSet(first[idx], &firstCount[idx], prod[i]);
                        break;
                    } else {
                        int ntIndex = getNonTerminalIndex(prod[i]);
                        if (ntIndex == -1) break;
                        // Recursive call if first set not computed yet
                        if (firstCount[ntIndex] == 0) {
                            computeFirst(ntIndex);
                        }
                        for (int j = 0; j < firstCount[ntIndex]; j++) {
                            if (first[ntIndex][j] != '@')
                                addToSet(first[idx], &firstCount[idx], first[ntIndex][j]);
                        }
                        if (!contains(first[ntIndex], firstCount[ntIndex], '@')) {
                            break;
                        }
                        if (i == (int)strlen(prod) - 1) {
                            addToSet(first[idx], &firstCount[idx], '@');
                        }
                    }
                }
            }
        }
    }
}

void computeFollow(int startIdx) {
    // Initialize Follow(start symbol) with '$'
    addToSet(follow[startIdx], &followCount[startIdx], '$');

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int r = 0; r < ruleCount; r++) {
            char head = productionHeads[r];
            int headIdx = getNonTerminalIndex(head);
            char *prod = productions[r];
            int len = strlen(prod);

            for (int i = 0; i < len; i++) {
                if (isNonTerminal(prod[i])) {
                    int currIdx = getNonTerminalIndex(prod[i]);
                    int oldCount = followCount[currIdx];

                    // Look ahead symbols after prod[i]
                    int foundEpsilon = 1;
                    for (int j = i + 1; j < len && foundEpsilon; j++) {
                        foundEpsilon = 0;
                        if (!isNonTerminal(prod[j])) {
                            addToSet(follow[currIdx], &followCount[currIdx], prod[j]);
                            break;
                        } else {
                            int ntIndex = getNonTerminalIndex(prod[j]);
                            for (int k = 0; k < firstCount[ntIndex]; k++) {
                                if (first[ntIndex][k] != '@')
                                    addToSet(follow[currIdx], &followCount[currIdx], first[ntIndex][k]);
                            }
                            if (contains(first[ntIndex], firstCount[ntIndex], '@')) {
                                foundEpsilon = 1;
                            }
                        }
                    }
                    // If no symbol after or all can produce epsilon, add Follow(head) to Follow(curr)
                    if (i == len - 1 || foundEpsilon) {
                        for (int k = 0; k < followCount[headIdx]; k++) {
                            addToSet(follow[currIdx], &followCount[currIdx], follow[headIdx][k]);
                        }
                    }

                    if (followCount[currIdx] > oldCount) {
                        changed = 1;
                    }
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &ruleCount);
    getchar(); // consume newline

    printf("Enter productions (format: A=xyz), use '@' for epsilon:\n");
    for (int i = 0; i < ruleCount; i++) {
        char line[50];
        fgets(line, sizeof(line), stdin);

        // parse input like "A=xyz"
        if (line[1] != '=' || !isNonTerminal(line[0])) {
            printf("Invalid input format\n");
            return 1;
        }
        productionHeads[i] = line[0];
        strcpy(productions[i], line + 2);
        productions[i][strcspn(productions[i], "\n")] = 0; // remove newline
        productionSizes[i] = strlen(productions[i]);

        // track unique non-terminals
        if (getNonTerminalIndex(productionHeads[i]) == -1) {
            nonTerminals[nonTerminalCount++] = productionHeads[i];
        }
    }

    // Initialize first and follow counts to 0
    for (int i = 0; i < nonTerminalCount; i++) {
        firstCount[i] = 0;
        followCount[i] = 0;
    }

    // Compute First sets
    for (int i = 0; i < nonTerminalCount; i++) {
        computeFirst(i);
    }

    // Compute Follow sets
    computeFollow(0); // assuming first non-terminal is start symbol

    printf("\nFirst sets:\n");
    for (int i = 0; i < nonTerminalCount; i++) {
        printf("First(%c) = { ", nonTerminals[i]);
        for (int j = 0; j < firstCount[i]; j++) {
            printf("%c ", first[i][j]);
        }
        printf("}\n");
    }

    printf("\nFollow sets:\n");
    for (int i = 0; i < nonTerminalCount; i++) {
        printf("Follow(%c) = { ", nonTerminals[i]);
        for (int j = 0; j < followCount[i]; j++) {
            printf("%c ", follow[i][j]);
        }
        printf("}\n");
    }

    return 0;
}
