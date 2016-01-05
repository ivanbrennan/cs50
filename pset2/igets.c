#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE *words = fopen(argv[1], "r");

	int length = 16;
	char string[length + 1];
	memset(string, 0, length + 1);

	printf("Before fgets()\n");
	for (int i = 0; i < length + 1; i++) {
		printf("int: %d\n", string[i]);
	}
	printf("\n");

	for (int j = 0; j < 2; j++) {
		memset(string, 0, length + 1);

		fgets(string, length + 1, words);

		for (int i = 0; i < length + 1; i++) {
			printf("int: %d\n", string[i]);
		}
		printf("\n");
	}
}
