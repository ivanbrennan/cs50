#include <stdio.h>

int main(void)
{
	int ht, row, spaces, hashes;

	// get height
	do
	{
		printf("height: ");
		scanf(" %d", &ht);
	}
	while (ht < 1 || ht > 23);

	// print pyramid
	for (row = 0; row < ht; row++)
	{
		/* left-padding shrinks from (ht-1) to 0,
		 * while hashes grow from 2 to (ht+1).
		 *
		 *		...##
		 *		..###
		 *		.####
		 *		#####
		 *
		*/
		spaces = (ht-1) - row;
		hashes = (ht+1) - spaces;

		while (spaces--) {
			printf(" ");
		}
		while (hashes--) {
			printf("#");
		}
		printf("\n");
	}

	return 0;
}
