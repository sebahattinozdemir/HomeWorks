/* Nested Assignment Example */
#include <stdio.h>

int main()
{
  int i=1, j=2, k=3;
  int res;
  i += j = k;
  res = i--j-----k;
  printf("1) i: %d j: %d k: %d\n", i, j, k);
  printf("2) res: %d i: %d j: %d k: %d\n", res, i, j, k);
  printf("3) i: %d j: %d k: %d\n", i, j, k);
}