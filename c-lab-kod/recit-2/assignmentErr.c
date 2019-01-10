/* Assignment Errors Example */
#include <stdio.h>

int main()
{
	int a=0, b=1, c=4;
	a = 1; // 1 is assigned to a
	b = c; // value of c is assigned to b
	
	0 = c; // Error! l-value should be a variable that can be examined, altered. Not a constant!
	0 + a = 140;
	a + b = c;
}