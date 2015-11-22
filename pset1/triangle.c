#include <stdio.h>
#define SIZE 4

void print_row(int padding);
void print_repeat(char c, int reps);

int main()
{
	int i, padding;

	for (i = 0; i < SIZE; i++) {
		/* padding recedes from (SIZE-1) to 0;
			...*
			..**
			.***
			****
		*/
		padding = (SIZE-1) - i;
		print_row(padding);
	}

	return 0;
}

void print_row(int padding)
{
	print_repeat(' ', padding);
	print_repeat('*', SIZE - padding);
	printf("\n");
}

void print_repeat(char c, int reps)
{
	while (reps--) {
		printf("%c", c);
	}
}
