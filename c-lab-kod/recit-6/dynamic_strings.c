#include <stdio.h>
#include <stdlib.h>

/* Store the string given by the user */

int main() {
	char c;
	char* str;
	int i;

	i = 0;
	str = (char*) malloc((i+1) * sizeof(char));
	while ((c = getchar()) != EOF) {
		str[i++] = c;
		str = (char*) realloc(str, (i+1) * sizeof(char));
	}
	
	printf("%s\n", str);

	return 0;
}