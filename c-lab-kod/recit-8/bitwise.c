#include <stdio.h>
#include <stdlib.h>
#define BINARY_STR_SIZE 8

/* given n must be less than pow(2, BINARY_STR_SIZE), otherwise increase BINARY_STR_SIZE */
char* convertToBinaryStr(int n) {
	
	/* below line is equal to pow(2, BINARY_STR_SIZE) -> d = 2^8 = 256 */
	int d = 1 << BINARY_STR_SIZE;
	char* result = (char*) malloc( BINARY_STR_SIZE * sizeof(char) );
	int i = 0;
	
	while (d != 0) {
		
		if ((n & d) == d) {
		    result[i] = '1';
		}
		else {
		    result[i] = '0';
		}

		/* divide d by 2 */
		d >>= 1;
		i++;
	}
	result[i] = '\0';


	/*
		lets say n = 60
		d is assigned to 256 (when BINARY_STR_SIZE = 8)

		60 & 256 = 0
		60 & 128 = 0
		60 & 64  = 0
		60 & 32  = 1
		60 & 16  = 1

		60 & 8   = 1
		60 & 4   = 1
		60 & 2   = 0
		60 & 1   = 0

	*/

	/*
		lets say n = 13
		d is assigned to 256 (when BINARY_STR_SIZE = 8)

		13 & 256 = 0
		13 & 128 = 0
		13 & 64  = 0
		13 & 32  = 0
		13 & 16  = 0
		13 & 8   = 1
		13 & 4   = 1
		13 & 2   = 0
		13 & 1   = 1

	*/
	
	return result;

}


int main() {

	unsigned int a = 60;	/* 60 = 0011 1100 */
	unsigned int b = 13;	/* 13 = 0000 1101 */
	int c = 0;

	c = a & b;       /* 12 = 0000 1100 */

	printf("a:\t%s\n", convertToBinaryStr(a));
	printf("b:\t%s\n", convertToBinaryStr(b));
	printf("a & b:\t%s\n", convertToBinaryStr(c));
	printf("Value of (a & b) is %d\n\n", c);

	c = a | b;       /* 61 = 0011 1101 */

	printf("a:\t%s\n", convertToBinaryStr(a));
	printf("b:\t%s\n", convertToBinaryStr(b));
	printf("a | b:\t%s\n", convertToBinaryStr(c));
	printf("Value of (a | b) is %d\n\n", c);

	c = a ^ b;       /* 49 = 0011 0001 */

	printf("a:\t%s\n", convertToBinaryStr(a));
	printf("b:\t%s\n", convertToBinaryStr(b));
	printf("a ^ b:\t%s\n", convertToBinaryStr(c));
	printf("Value of (a ^ b) is %d\n\n", c);

	c = ~a;          /*-61 = 1100 0011 */

	printf("a:\t%s\n", convertToBinaryStr(a));
	printf("~a:\t%s\n", convertToBinaryStr(c));
	printf("Value of (~a) is %d\n\n", c);

	c = a << 2;     /* 240 = 1111 0000 */

	printf("a:\t%s\n", convertToBinaryStr(a));
	printf("a << 2:\t%s\n", convertToBinaryStr(c));
	printf("Value of (a<<2) is %d\n\n", c);

	c = a >> 2;     /* 15 = 0000 1111 */
	
	printf("a:\t%s\n", convertToBinaryStr(a));
	printf("a >> 2:\t%s\n", convertToBinaryStr(c));
	printf("Value of (a>>2) is %d\n\n", c);

	return 0;
}
