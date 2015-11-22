#include <stdio.h>

int main(void)
{
	int min;

	printf("minutes: ");
	scanf(" %d", &min);

	printf("bottles: %d\n", min * 192 / 16);

	return 0;
}
