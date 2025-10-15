#include<stdio.h>
#include<ctype.h>

int main()
{
	char stack[20], input[20], inter ='A', intermediates[20][20], input1[20], op[20];
	int priority[20], priority1 = 0;
	int k=0, i=0, j=0, l=0;
	
	printf("Enter the Input aritmetic expression: ");
	gets(input1);
	
	printf("\nPostfix conversation:\n");
	
	//++++++ Infix to Postfix Conversion ++++++
	op[0] = '(';
	priority[0] = 0;
	l = 1;
	
	while (input1[i] != '\0')
	{
		if (isalnum(input1[i])) {
			input[k] = input1[i];
			k++;
		}
		
		if (input1[i] == '(') {
			op[l] = '(';
			priority[l] = 0;
			l++;
		}
		
		if (input1[i] == '+' || input1[i] == '*' || input1[i] == '/' || input1[i] == '-'){
			if (input1[i] == '*' || input1[i] == '/')
				priority1 = 2;
			else
				priority1 = 1;
			
			while (priority[l-1] >= priority1) {
				l--;
				input[k++] = op[l];
			}
			
			op[l] = input1[i];
			priority[l++] = priority1;
		}
		
		if (input1[i] == ')') {
			while (op[l-1] != '(') {
				l--;
				input[k++] = op[l];
			}
			l--;
		}
		i++;
	}
	
	l--;
	for (i = 0; i < k; i++)
		printf("%c\n", input[i]);
	
	while (l >= 1)
		input[k++] = op[l--];
	
	printf("\nPostfix Expression: ");
	for (i = 0; i < k; i++)
		printf("%c", input[i]);
	
	//+++++++ Intermediate generation ++++++++
	i=0;
	k=0;
	
	while (input[i] != '\0')
	{
		if (isalnum(input[i])) {
			stack[k] = input[i];
			k++;
		}
		if (input[i] == '+' || input[i] == '*' || input[i] == '/' || input[i] == '-') {
			intermediates[j][0] = inter;
			intermediates[j][1] = '=';
			intermediates[j][2] = stack[k-2];
			intermediates[j][3] = input[i];
			intermediates[j][4] = stack[k-1];
			intermediates[j][5] = '\0';
			
			stack[k-1] = ' ';
			stack[k-2] = inter;
			inter++;
			j++;
			k -= 1;
		}
		i++;
	}
	
	printf("\n\nIntermediates:\n");
	for (i = 0; i < j; i++)
		printf("%s\n", intermediates[i]);
	
	return 0;
}
