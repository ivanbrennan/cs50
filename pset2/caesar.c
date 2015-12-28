// origin = (int) 'A';
// offset = (int) letter;
// cipher_int = ((offset - origin + k) % 26) + origin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH	1000

char rotate_char(char c, int rotation, char alpha_origin)
{
	int old_offset = c - alpha_origin;
	int new_offset = (old_offset + rotation) % 26;

	return alpha_origin + new_offset;
}

char caesar_cipher_char(char plain_char, int key)
{
	char cipher_char;

	if ('A' <= plain_char && plain_char <= 'Z') {
		cipher_char = rotate_char(plain_char, key, 'A');
	} else if ('a' <= plain_char && plain_char <= 'z') {
		cipher_char = rotate_char(plain_char, key, 'a');
	} else {
		cipher_char = plain_char;
	}

	return cipher_char;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("You must specify an integer key!\n");
		return 1;
	} else {
		int key = atoi(argv[1]);
		printf("What would you like to encrypt?\n");

		char plaintext[MAX_TEXT_LENGTH] = { '\0' };
		gets(plaintext);

		for (int i = 0, n = strlen(plaintext); i < n; i++) {
			printf("%c", caesar_cipher_char(plaintext[i], key));
		}
		printf("\n");

		return 0;
	}
}
