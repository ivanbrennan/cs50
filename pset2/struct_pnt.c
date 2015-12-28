#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char name[21];
	char city[21];
	char phone[21];
	char *comment;
} Addr;

int main()
{
	Addr s;
	char comm[100];

	gets(s.name);
	gets(s.city);
	gets(s.phone);
	gets(comm);

	s.comment = (char *)malloc(sizeof(char[strlen(comm)+1]));
	strcpy(s.comment, comm);
}
