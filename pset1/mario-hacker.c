#include <stdio.h>

void printChars(char c, int reps);

int main()
{
	int height, i;

	// get user input
	height = 0;
	while (height < 1 || height > 23) {
		printf("Height: ");
		scanf(" %d", &height);
	}

	for (i = 0; i < height; i++) {
		printChars(' ', height - (i+1));
		printChars('#', i+1);
		printChars(' ', 2);
		printChars('#', i+1);
		printChars(' ', height - (i+1));

		printf("\n");
	}

	return 0;
}

void printChars(char c, int reps)
{
	for (int i = 0; i < reps; i++) {
		printf("%c", c);
	}
}
