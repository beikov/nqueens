/******************************************************************************
 * Based on OriginalNQueensSolver.
 *
 * Removed field x since there is no real use for it
 * Removed maxN and used n instead (use malloc to reserve int arrays on heap)
 * Common subexpressions eliminated
 * Symmetrie checking along the vertical middle line
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* this is the actual board size to be used */
int n;
/* half of the board size */
int mid;
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

/* Function prototypes */
void try1(int i, int mirrorExit);
void tryMid(int i, int j);

/*
 * If we have odd number of n, then we have to do an extra run for the n/2 + 1
 * column.
 */
void tryMid(int i, int j) {
	// Common subexpressions
	int bIndex = i + j;
	int cIndex = i - j + n;
	if (a[j] && b[bIndex] && c[cIndex]) {
		a[j] = 0;
		b[bIndex] = 0;
		c[cIndex] = 0;
		try1(i + 1, 1);
		a[j] = 1;
		b[bIndex] = 1;
		c[cIndex] = 1;
	}
}

/*
 * Search all solutions that start with a queen in the row i. If mirrorExit,
 * then we do only columns 1..n/2 . With mirrorExit we control that only 1..n/2
 * is checked on the first row, for all deeper rows we do as usual 1..n.
 */
void try1(int i, int mirrorExit) {
	int j = 0;
	// Common subexpressions
	int bIndex = i;
	int cIndex = i + n;
	do {
		j++;
		if (mirrorExit && (j > mid)) {
			// Do not count mirrored solutions.
			return;
		}
		bIndex++;
		cIndex--;
		if (a[j] && b[bIndex] && c[cIndex]) {
			a[j] = 0;
			b[bIndex] = 0;
			c[cIndex] = 0;
			if (i < n) {
				try1(i + 1, 0);
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
	mid = n >> 1; // mid = n/2
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
	try1(1, 1);
	// if we have odd n, we have to do column n/2 + 1 extra
	if ((1 & n) == 1) {
		tryMid(1, (mid + 1));
	}
	// add mirrored solutions (simply double count)
	count = count << 1;
	printf("%ld\n", count);
	return 0;
}

