#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int main() {

	char s1[MAX] = {}, s2[MAX] = {};

	printf("%d\n", strlen("Tardis"));
	printf("%s\n", strcpy(s1, "Doctor"));
	printf("%s\n", strncpy(s2, "Who?", 3));
	printf("%s\n", strcat(s1, s2));
	printf("%d\n", strncmp(s1 + 6, s2, 3));
	printf("%s\n", strchr(s1, 'o'));

	return 0;
}