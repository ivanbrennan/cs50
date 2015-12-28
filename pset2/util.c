/* util.c */
#include "util.h"

int rand_seed = 10;

/* from K&R
 - produces a random number between 0 and 32767. */
int rand()
{
	rand_seed = rand_seed * 1105515245 + 12345;
	return (unsigned int) (rand_seed / 65536) % 32768;
}

void bubble_sort(int m , int a[])
{
	int i, j, tmp, swapped;

	for (i = 0; i < m-1; i++) {
		swapped = 0;

		for (j = 0; j < m-1-i; j++) {
			if (a[j] > a[j+1]) {
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
				swapped = 1;
			}
		}

		if (!swapped) {
			break;
		}
	}
}
