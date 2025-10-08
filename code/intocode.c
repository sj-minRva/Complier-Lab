#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char stack[20], input[20], inter = 'A', intermediates[20][20], input1[20], op[20];
    int priority[20], priority1 = 0;
    int k = 0, i = 0, j = 0, l = 0;

    printf("Enter the Input arithmetic expression: ");
    scanf("%s", input1);

    printf("\n--- Postfix Conversion ---\n");

    // Initialize operator stack
    op[0] = '(';
    priority[0] = 0;
    l = 1;

    i = 0;
    while (input1[i] != '\0') {
        if (isalnum(input1[i])) {
            input[k++] = input1[i];
        }
        else if (input1[i] == '(') {
            op[l] = '(';
            priority[l] = 0;
            l++;
        }
        else if (input1[i] == '+' || input1[i] == '-' || input1[i] == '*' || input1[i] == '/') {
            if (input1[i] == '*' || input1[i] == '/')
                priority1 = 2;
            else
                priority1 = 1;

            while (priority[l - 1] >= priority1) {
                l--;
                input[k++] = op[l];
            }
            op[l] = input1[i];
            priority[l++] = priority1;
        }
        else if (input1[i] == ')') {
            while (op[l - 1] != '(') {
                l--;
                input[k++] = op[l];
            }
            l--; // Pop '('
        }
        i++;
    }

    // Pop remaining operators
    while (l > 1) {
        l--;
        input[k++] = op[l];
    }
    input[k] = '\0';

    printf("Postfix Expression: %s\n", input);

    // =======================================================
    // ============= Intermediate Code Generation ============
    // =======================================================

    i = 0;
    k = 0;
    j = 0;

    while (input[i] != '\0') {
        if (isalnum(input[i])) {
            stack[k++] = input[i];
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            intermediates[j][0] = inter;
            intermediates[j][1] = '=';
            intermediates[j][2] = stack[k - 2];
            intermediates[j][3] = input[i];
            intermediates[j][4] = stack[k - 1];
            intermediates[j][5] = '\0';

            // Update stack
            k = k - 2;
            stack[k++] = inter;
            inter++;
            j++;
        }
        i++;
    }

    printf("\n--- Intermediate Code ---\n");
    for (i = 0; i < j; i++) {
        printf("%s\n", intermediates[i]);
    }

    return 0;
}
