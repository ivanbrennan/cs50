#include <stdio.h>

int main(void)
{
	int n, j, k;

	// get height
	do
	{
		printf("height: ");
		scanf(" %d", &n);
	}
	while (n < 1 || n > 23);

	// print pyramid
	for (j = 0; j < n; j++)
	{
		// print spaces
		for (k = 0; k < ((n-1) - j); k++)
		{
			printf(" ");
		}
		// print hashes
		for (k = ((n-1) - j); k <= n; k++)
		{
			printf("#");
		}
		// print newline
		printf("\n");
	}

	return 0;
}
