#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check();
void printResult(int accepted);

int main() {
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
    puts("Enter input string: ");
    gets(a);  
    c = strlen(a);
    strcpy(act, "SHIFT->");
   
    puts("stack \t input \t action");
   
    // Parsing loop
    for ( i = 0, j = 0; j < c; i++, j++) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, a, act);
            check();
        } else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act);
            check();
        }
    }

    // After parsing is done, check if we can reduce the entire stack to 'E'
    if (stk[0] == 'E' && stk[1] == '\0' && a[0] == ' ') {
        printResult(1); // Accepted
    } else {
        printResult(0); // Rejected
    }

    return 0;
}

void check() {
    strcpy(ac, "REDUCE TO E");
   
    // Rule 1: E -> id
    for (z = 0; z < c; z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            j++;
        }
    }

    // Rule 2: E -> E + E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    // Rule 3: E -> E * E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    // Rule 4: E -> ( E )
    for (z = 0; z < c; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }
}

// Function to print the result (Accepted or Rejected)
void printResult(int accepted) {
    if (accepted) {
        printf("\nInput string is ACCEPTED.");
    } else {
        printf("\nInput string is REJECTED.");
    }
}