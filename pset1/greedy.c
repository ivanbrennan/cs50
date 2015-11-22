#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
	float change = 0.0;
	int coins[] = { 25, 10, 5, 1 };
	int rem_cents, count, i;
	rem_cents = count = i = 0;

	// get user input
	printf("How much change is owed?\n");
	scanf(" %f", &change);
	rem_cents = roundf(change * 100);

	// calculate result
	for (i = 0; i < sizeof(coins) / sizeof(int); i++)
	{
		while (rem_cents >= coins[i])
		{
			rem_cents -= coins[i];
			count++;
		}

		if (!rem_cents)
		{
			break;
		}
	}

	// print result
	printf("%d\n", count);

	return 0;
}
