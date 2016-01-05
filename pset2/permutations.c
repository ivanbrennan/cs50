#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char alpha[] = "ab";
static const int alphalen = sizeof(alpha) - 1;

void permute(char* word, int index, int depth)
{
	for (int i = 0; i < alphalen; i++) {
		word[index] = alpha[i];

		if (index == depth - 1) {
			printf("%s\n", word);
		} else {
			permute(word, index + 1, depth);
		}
	}
}

int main(void)
{
	int maxlen = 2;
	char* word = calloc(1, maxlen + 1);

	for (int depth = 1; depth <= maxlen; depth++) {
		memset(word, 0, maxlen + 1); // fill word with NULL bytes
		permute(word, 0, depth);
	}
}
