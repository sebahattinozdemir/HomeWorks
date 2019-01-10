#include <stdio.h>
#include <stdlib.h>

/* Write a function matrixAllocate that takes two integers, m and n and allocate an m by n block of memory. */
void matrixAllocate(int*** Mptr, int n, int m);

int main() {
	int **Matrix = NULL;
	int n = 3;
	int m = 4;
	int i, j;
	matrixAllocate(&Matrix, n, m);

	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			Matrix[i][j] = i * j;
		}
	}

	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			printf("%d ", Matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void matrixAllocate(int*** Mptr, int n, int m) {
	*Mptr = (int**) malloc(m * sizeof(int*));
	int i = 0;
	for (i = 0; i < m; i++) {
		(*Mptr)[i] = malloc(n * sizeof(int));
	}
}
