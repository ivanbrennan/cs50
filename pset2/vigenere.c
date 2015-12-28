#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH	1000

int allalpha(char* keyword)
{
	for (int i = 0, n = strlen(keyword); i < n; i++) {
		if (!isalpha(keyword[i])) {
			return 0;
		}
	}
	return 1;
}

char alpha_origin(char letter)
{
	return (isupper(letter)) ? 'A' : 'a';
}

int key_rotation(char key)
{
	char origin = alpha_origin(key);

	return key - origin;
}

char rotate_char(char plain_char, int rotation)
{
	char origin = alpha_origin(plain_char);

	int old_offset = plain_char - origin;
	int new_offset = (old_offset + rotation) % 26;

	return origin + new_offset;
}

char* vigenere_cipher_text(char* plain_text, char* keyword)
{
	int text_len = strlen(plain_text);
	int key_len  = strlen(keyword);

	char* cipher_text = malloc((text_len+1) * sizeof *cipher_text);

	for (int i = 0, j = 0; i < text_len; i++) {
		char plain_char = plain_text[i];
		char cipher_char;

		if (isalpha(plain_char)) {
			int rotation = key_rotation(keyword[j++ % key_len]);
			cipher_char = rotate_char(plain_text[i], rotation);
		} else {
			cipher_char = plain_char;
		}

		cipher_text[i] = cipher_char;
	}
	return cipher_text;
}

int main(int argc, char* argv[])
{
	if (argc == 2) {
		char* keyword = argv[1];

		if (allalpha(keyword)) {
			char plain_text[MAX_TEXT_LENGTH] = { '\0' };
			printf("What would you like to encrypt?\n");
			gets(plain_text);

			char* cipher_text = vigenere_cipher_text(plain_text, keyword);
			printf("%s\n", cipher_text);
			free(cipher_text);
		} else {
			printf("Your cipher keyword can only contain alphabetic characters\n");
			return 1;
		}
	} else {
		printf("You must supply a cipher keyword\n");
		return 1;
	}
}
