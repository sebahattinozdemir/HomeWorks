/* Logical Operators Example */
#include <stdio.h>

int main()
{
  int expr1 = 0, expr2 = 0;
  printf("and: %d or: %d not(expr1): %d not(expr2): %d\n",
  expr1&&expr2, expr1||expr2, !expr1, !expr2);
  expr1 = 0; expr2 = 1;
  printf("and: %d or: %d not(expr1): %d not(expr2): %d\n",
  expr1&&expr2, expr1||expr2, !expr1, !expr2);
  expr1 = 1; expr2 = 0;
  printf("and: %d or: %d not(expr1): %d not(expr2): %d\n",
  expr1&&expr2, expr1||expr2, !expr1, !expr2);
  expr1 = 1; expr2 = 1;
  printf("and: %d or: %d not(expr1): %d not(expr2): %d\n",
  expr1&&expr2, expr1||expr2, !expr1, !expr2);
}