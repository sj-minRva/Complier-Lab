#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void main()
{
	char c[100], pre[10], post[10], ne[10];
	int i,j,k,l,m,x,y,z,n;
	
	printf("Enter the expression: ");
	scanf("%s", c);
	
	i=0;
	while (c[i] != '\0')
	{
		if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/')
		{
			j = i - 1;
			k = i + 1;
			
			if (isdigit(c[k]) && isdigit(c[j]))
			{	
				l=0;
				m=0;
				
				while (isdigit(c[k]))
				{
					post[l++] = c[k++];
				}
				post[l] = '\0';
				
				while (isdigit(c[j]))
				{
					pre[m++] = c[j--];
				}
				pre[m] = '\0';
				
				x = atoi(pre);
				y = atoi(post);
				
				switch (c[i])
				{
					case '+': z = x + y; break;
					case '-': z = x - y; break;
					case '*': z = x * y; break;
					case '/': z = x / y; break;
				}
				
				sprintf(ne, "%d", z);
				
				n = 0;
				
				while(ne[n] != '\0')
				{
					c[++j] = ne[n++];
				}
				
				
				i=j;
				j++;
				
				
				while (c[k] != '\0')
				{
					c[j++] = c[k++];
				}
				c[j] = '\0';
			}
		}
		i++;
	}
	printf("Result\n%s\n",c);
}


