#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
	char name[128] = { '\0' };
	char initials[64] = { '\0' };

	printf("Type your name: \n");
	gets(name);

	for (int i = 0, j = 0, n = strlen(name); i < n; i++) {
		if ((i == 0 || isspace(name[i-1])) && !isspace(name[i])) {
			initials[j++] = toupper(name[i]);
		}
	}

	printf("%s\n", initials);
}
