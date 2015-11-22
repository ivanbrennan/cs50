#include <stdio.h>

int main(void)
{
	int ht, i, j;

	// get height
	do
	{
		printf("height: ");
		scanf(" %d", &ht);
	}
	while (ht < 1 || ht > 23);

	// print pyramid
	for (i = 0; i < ht; i++)
	{
		// print spaces
		for (j = 0; j < (ht - i - 1); j++)
		{
			printf(" ");
		}
		// print hashes
		for (j = 0; j < (i+2); j++)
		{
			printf("#");
		}
		// print newline
		printf("\n");
	}

	return 0;
}
