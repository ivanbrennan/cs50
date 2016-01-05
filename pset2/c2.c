#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// "static" here means this global variable is only visible within this file.
// "const" means the alphabet may not be modified

static const char alphabet[] =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"0123456789";

static const int alphasize = sizeof(alphabet) - 1;

char* find_password_in_file(FILE* file, int max_length, char* encrypted_password, char* salt)
{
	char* word = calloc(1, max_length + 1); // include space for NULL byte

	while (fgets(word, max_length + 1, file)) {
		size_t length = strlen(word);
		if (word[length - 1] == '\n') {
			word[length - 1] = '\0';
		}

		char *encrypted_word = crypt(word, salt);

		// see if it matches the encrypted password
		if (strcmp(encrypted_word, encrypted_password) == 0) {
			return word;
		} else {
			memset(word, 0, max_length); // fill word with NULL bytes
		}
	}

	free(word);
	return NULL;
}

// try every word in a given dictionary
char* dictionary_attack(char dictionary_path[], char* encrypted_password, char* salt)
{
	FILE *dictionary = fopen(dictionary_path, "r");
	int max_length = 32;
	// read a word from the dictionary
	char* found = find_password_in_file(dictionary, max_length, encrypted_password, salt);

	fclose(dictionary);
	return found;
}

// find a password of given length
char* permutations(char* word, int index, int length, char* encrypted_password, char* salt)
{
	for (int i = 0; i < alphasize; i++) {
		word[index] = alphabet[i];

		if (index == length - 1) {
			printf("%s\n", word);
			char *encrypted_word = crypt(word, salt);
			
			if (strcmp(encrypted_word, encrypted_password) == 0) {
				return word;
			}
		} else {
			char* found = permutations(word, index+1, length, encrypted_password, salt);
			if (found != NULL) {
				return found;
			}
		}
	}
	return NULL;
}

// try every possible word up to a reasonable length
char* brute_force_attack(char* encrypted_password, char* salt)
{
	int max_length = 32;
	char* word = calloc(1, max_length + 1); // include space for NULL byte

	// try shortest to longest possible words
	for (int length = 1; length <= max_length; length++) {
		memset(word, 0, max_length + 1); // fill word with NULL bytes
		// try to find a matching password of given length
		char *found = permutations(word, 0, length, encrypted_password, salt);
		if (found != NULL) {
			return found;
		}
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	if (argc == 2) {
		char *encrypted_password = argv[1];
		char salt[2] = { encrypted_password[0], encrypted_password[1] };
		printf("Cracking %s\n", encrypted_password);

		char passwords_path[] = "most_common_passwords.txt";
		char* word = dictionary_attack(passwords_path, encrypted_password, salt);

		if (word == NULL) {
			char dictionary_path[] = "/usr/share/dict/words";
			word = dictionary_attack(dictionary_path, encrypted_password, salt);
		}
		if (word == NULL) {
			word = brute_force_attack(encrypted_password, salt);
		}

		if (word == NULL) {
			printf("Couldn't find a password\n");
		} else {
			printf("%s\n", word);
			free(word);
		}
	} else {
		printf("Please specify a single encrypted password\n");
		return 1;
	}
}
