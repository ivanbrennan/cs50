#include <stdio.h>
#include <stdlib.h>

void shift_leading_whitespace(char **str_start);
void chop_trailing_whitespace(char *chrs);
char * last_group(char *chrs, _Bool whitespace);
void upper_str(char *str, char *new_str);
char * without_leading_word(char *str);

int main()
{
	char *names, *upper_names, *without_first;
	char **ptr;

	upper_names = (char *)malloc(100 * sizeof(char));
	gets(names);

	ptr = &names;
	shift_leading_whitespace(ptr);

	chop_trailing_whitespace(names);
	upper_str(names, upper_names);

	without_first = without_leading_word(names);

	printf("Full name: %s\n", names);
	printf("FULL NAME: %s\n", upper_names);
	printf("...without first: %s\n", without_first);
	printf("Last name: %s\n", last_group(names, 0));

	free(upper_names);

	return 0;
}

void shift_leading_whitespace(char **str_start)
{
	while (**str_start == ' ' || **str_start == '\t') {
		(*str_start)++;
	}
}

void chop_trailing_whitespace(char *chrs)
{
	char *str_end;

	if ((str_end = last_group(chrs, 1))) {
		*str_end = 0;
	}
}

char * last_group(char *chrs, _Bool whitespace)
{
	char *group, c;
	group = 0;

	// iterate through characters
	while ((c = *chrs)) {
		// detect whitespace/word
		if ((c == ' ' || c == '\t') == whitespace) {
			// set group if not already set
			if (!group) {
				group = chrs;
			}
		} else {
			group = 0;
		}
		chrs++;
	}

	return group;
}

void upper_str(char *str, char *new_str)
{
	int i, to_upper, change;
	char c;

	i = 0;
	to_upper = 'A' - 'a';

	while((c = str[i])) {
		if ('a' <= c && c <= 'z') {
			change = to_upper;
		} else {
			change = 0;
		}
		new_str[i++] = c + change;
	}
}

char * without_leading_word(char *str)
{
	char c;
	_Bool past_first = 0;

	while ((c = *str)) {
		if (c == ' ' || c == '\t') {
			past_first = 1;
		} else if (past_first) {
			break;
		}
		str++;
	}

	return str;
}
