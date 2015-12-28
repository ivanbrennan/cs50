#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH	1000

char rotate_char(char c, int rotation, char alpha_origin)
{
	int old_offset = c - alpha_origin;
	int new_offset = (old_offset + rotation) % 26;

	return alpha_origin + new_offset;
}

char caesar_cipher_char(char plain_char, int key)
{
	if (isalpha(plain_char)) {
		char alpha_origin = isupper(plain_char) ? 'A' : 'a';
		return rotate_char(plain_char, key, alpha_origin);
	} else {
		return plain_char;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("You must specify an integer key!\n");
		return 1;
	} else {
		char plaintext[MAX_TEXT_LENGTH] = { '\0' };
		printf("What would you like to encrypt?\n");
		gets(plaintext);

		int key = atoi(argv[1]);
		for (int i = 0, n = strlen(plaintext); i < n; i++) {
			printf("%c", caesar_cipher_char(plaintext[i], key));
		}
		printf("\n");

		return 0;
	}
}
