#include <stdio.h>
#define MAX	10

int main()
{
	FILE *f;
	int x;

	f = fopen("out", "w");
	if (!f) {
		return 1;
	}

	for (x = 0; x < MAX; x++) {
		fprintf(f, "%d\n", x+1);
	}

	fclose(f);
	return 0;
}
