/******************************************************************************
 * Based on OriginalNQueensSolver.
 *
 * Removed field x since there is no real use for it
 * Removed maxN and used n instead (use malloc to reserve int arrays on heap)
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
	int j = 0; // column
	// loop through all columns 1..n and do dfs on every column
	do {
		j = j + 1; // set column (1..n)
		if (a[j] && b[i + j] && c[i - j + n]) {
			/* Set all array entries associated with this field to false,
			 meaning that we cannot place a queen on fields which are
			 covered by the queen we just put on this field. */
			a[j] = 0;
			b[i + j] = 0;
			c[i - j + n] = 0;
			/* do recursive calls until last row reached */
			if (i < n) {
				/* search for solutions (dfs) on next row */
				try1(i + 1);
			} else {
				count++;
			}
			/* we have searched all n rows for current column j */
			/* FYI: we need to clear state here after we have found a solution,
			 so we have a clean start on the next recursive call. If this is
			 not done here, we would have false in all fields after first full
			 dfs run. */
			a[j] = 1;
			b[i + j] = 1;
			c[i - j + n] = 1;
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
	try1(1); // start recursive backtracking algorithm at first row
	printf("%ld\n", count); // print result (number of solutions found)
	return 0;
}

