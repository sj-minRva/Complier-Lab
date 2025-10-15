#include <stdio.h>
#include <string.h>

#define MAX_INSTRUCTIONS 100

typedef struct {
    char op[5];    // operation: +, -, *, /
    char arg1[10];
    char arg2[10];
    char result[10];
} TACInstruction;

TACInstruction instructions[MAX_INSTRUCTIONS];
int instruction_count = 0;

// Function to read TAC instructions from user input
void readIntermediateCode() {
    printf("Enter number of TAC instructions: ");
    scanf("%d", &instruction_count);
    getchar(); // consume newline

    printf("Enter TAC instructions in the format:\n");
    printf("result = arg1 op arg2\n");
    printf("For example: t1 = a + b\n\n");

    for (int i = 0; i < instruction_count; i++) {
        char line[50];
        printf("Instruction %d: ", i + 1);
        fgets(line, sizeof(line), stdin);

        // Parse the line
        // Format: result = arg1 op arg2
        sscanf(line, "%s = %s %s %s", instructions[i].result, instructions[i].arg1, instructions[i].op, instructions[i].arg2);

        // Remove any trailing newline in result if present
        int len = strlen(instructions[i].result);
        if (instructions[i].result[len - 1] == '\n')
            instructions[i].result[len - 1] = '\0';
    }
}

// Function to generate assembly code from TAC
void generateAssembly() {
    printf("\nAssembly code generated from TAC:\n");

    for (int i = 0; i < instruction_count; i++) {
        TACInstruction instr = instructions[i];

        if (strcmp(instr.op, "+") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("ADD R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n\n", instr.result);
        } else if (strcmp(instr.op, "-") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("SUB R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n\n", instr.result);
        } else if (strcmp(instr.op, "*") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("MUL R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n\n", instr.result);
        } else if (strcmp(instr.op, "/") == 0) {
            printf("MOV R1, %s\n", instr.arg1);
            printf("DIV R1, %s\n", instr.arg2);
            printf("MOV %s, R1\n\n", instr.result);
        } else {
            printf("Unknown operation: %s\n", instr.op);
        }
    }
}

int main() {
    readIntermediateCode();
    generateAssembly();
    return 0;
}
