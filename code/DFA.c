#include <stdio.h>
#include <string.h>
#define MAX 100

int main() {
    char input[MAX];
    int i, state = 0;
    int length;

    printf("Enter the binary string: ");
    scanf("%s", input);

    length = strlen(input);

    for (i = 0; i < length; i++) {
        char symbol = input[i];

        // Validate input symbol
        if (symbol != '0' && symbol != '1') {
            printf("Invalid input: only 0 and 1 are allowed.\n");
            return 1;
        }

        // DFA transitions
        switch (state) {
            case 0:
                if (symbol == '0')
                    state = 1;
                else
                    state = 0;
                break;

            case 1:
                if (symbol == '0')
                    state = 1;
                else
                    state = 2;
                break;

            case 2:
                if (symbol == '0')
                    state = 1;
                else
                    state = 0;
                break;
        }
    }

    // Final acceptance check
    if (state == 2)
        printf("The string is ACCEPTED by the DFA.\n");
    else
        printf("The string is NOT ACCEPTED by the DFA.\n");

    return 0;
}
