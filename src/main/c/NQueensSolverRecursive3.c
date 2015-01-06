/******************************************************************************
 * Based on OriginalNQueensSolver.
 *
 * Removed field x since there is no real use for it
 * Removed maxN and used n instead (use malloc to reserve int arrays on heap)
 * Common subexpressions eliminated
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* this is the actual board size to be used */
int n;
/* number of found solutions to the n-queens problem */
long count = 0L;
/* a[x] is true, if a queen can be placed in column x  (x: 1..n) */
int *a;
/* b[y+x] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y-k) for all k.
 "/" antidiagonal line) */
int *b;
/* c[y-x+n] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y+k) for all k.
 "\" diagonal line */
int *c;

/*
 * Search all solutions that start with a queen in the row i.
 */
void try1(int i) {
	int j = 0;
	// Common subexpressions
    int bIndex = i;
    int cIndex = i + n;
	do {
        j++;
        bIndex++;
        cIndex--;
		if (a[j] && b[bIndex] && c[cIndex]) {
			a[j] = 0;
			b[bIndex] = 0;
			c[cIndex] = 0;
			if (i < n) {
				try1(i + 1);
			} else {
				count++;
			}
			a[j] = 1;
			b[bIndex] = 1;
			c[cIndex] = 1;
		}
	} while (j != n);
}

int main(int argc, char *argv[]) {
	if (argc <= 1 || (n = atoi(argv[1])) <= 0) {
		n = 8;
	}
	// make arrays the required size
	a = (int *) malloc((n + 1) * sizeof(int));
	b = (int *) malloc((2 * n + 1) * sizeof(int));
	c = (int *) malloc((2 * n) * sizeof(int));
	// initialize all arrays, set all true
	int i = 1;
	for (i = 1; i <= n; i++) {
		a[i] = 1; // '|' column storage
	}
	for (i = 2; i <= (2 * n); i++) {
		b[i] = 1; // '/' diagonal storage
	}
	for (i = 1; i <= ((2 * n) - 1); i++) {
		c[i] = 1; // '\' diagonale storage
	}
	try1(1);
	printf("%ld\n", count);
	return 0;
}

