/******************************************************************************
 * File: nqueens.c
 * Course: Effiziente Programme
 * Date: 31.12.2014
 *
 * The original Java code in nqueens.java is
 * derived from Niklaus Wirth's Pascal program (therefore not idiomatic Java)
 * from "Algorithms + Data Structures = Programs", Prentice-Hall 1976
 * modified to produce and count all solutions
 *
 * Problem: Zaehle die Loesungen fuer folgendes Problem: Setze N Damen
 * auf einem NxN-Schachbrett so, dass keine Dame eine andere schlagen
 * kann.
 *
 * Command-line arguments
 * 1 argument which specifies board size n (and also number of queens).
 *
 * Change History
 * 31.12.2014 converted from java (nqueens.java) to c
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* maximum board size we will process */
#define MAXN 100
/* this is the actual board size to be used */
int n;
/* number of found solutions to the n-queens problem */
long count = 0L;
/* a[x] is true, if a queen can be placed in column x  (x: 1..n) */
int a[MAXN + 1];
/* b[y+x] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y-k) for all k.
 "/" antidiagonal line) */
int b[2 * MAXN + 1];
/* c[y-x+n] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y+k) for all k.
 "\" diagonal line */
int c[2 * MAXN];
/* x[y] has an entry for each row, which tells, in which column the queen is
 put for current partly solution. This is required here ONLY for debug. */
int x[MAXN + 1];

/*
 * Search all solutions that start with a queen in the row i.
 */
void try1(int i) {
	int j = 0; // column
	// loop through all columns 1..n and do dfs on every column
	do {
		j = j + 1; // set column (1..n)
		if (a[j] && b[i + j] && c[i - j + n]) {
			/* store result: on column j, row i a queen is placed now */
			x[i] = j;
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
//				int k = 0;
//				printf("#%ld: \t", count);
//				for (k = 1; k <= n; k++) {
//					printf("%d ", x[k]);
//				}
//				printf("\n");
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

