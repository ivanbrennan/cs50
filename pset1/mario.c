#include <stdio.h>

int main(void)
{
	int ht, i, j;

	do
	{
		printf("height: ");
		scanf(" %d", &ht);
	}
	while (ht < 1 || ht > 23);

	for (i = ht; i > 0; i--)
	{
		for (j = 0; j < (ht+1); j++)
		{
			if (j < (i-1))
			{
				printf(" ");
			}
			else
			{
				printf("#");
			}
		}
		printf("\n");
	}
}
