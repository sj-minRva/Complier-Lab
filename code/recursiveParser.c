//Recursive Descent Parser 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h>

char input[100]; 
int i = 0; 
int error = 0; 

void E(void);
void Eprime(void);
void T(void);
void Tprime(void);
void F(void);

int main(void)
{
    printf("Enter input string: ");
    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }
    /* strip newline */
    int len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    i = 0;
    error = 0;
    E();

    if (input[i] == '\0' && error == 0) {
        printf("Input accepted.\n");
    } else {
        printf("Error!\nInput rejected.\n");
    }
    return 0;
}

void E(void) {
    T();
    Eprime();
}

void Eprime(void) {
    if (input[i] != '\0' && input[i] == '+') {
        i++;
        T();
        Eprime();
    }
}

void T(void) {
    F();
    Tprime();
}

void Tprime(void) {
    if (input[i] != '\0' && input[i] == '*') {
        i++;
        F();
        Tprime();
    }
}

void F(void) {
    if (input[i] != '\0' && isalpha((unsigned char)input[i])) 
    {
        i++;
    } 
    else if (input[i] == '(') 
    {
        i++;
        E();
        if (input[i] == ')') {
            i++;
        } else {
            error = 1;
        }
    } 
    else 
    {
        error = 1;
    }
}