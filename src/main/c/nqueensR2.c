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
 * 4.1.2015 (#1) implemented symmetrie check. All mirrored versions along the
 * 		vertical middle line are skipped, and at the end the resulting
 * 		solutions are doubled. Care must be taken if n is odd, then n/2 + 1
 * 		column must be run separate.
 * 5.1.2015 (#2) use 64bit long value and bitmasks instead of integer arrays for
 * 			boolean arrays a,b,c.
 *
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* maximum board size we will process. If long value and bitmask is used for
 the used boolean arrays, this can only be 31 max. */
#define MAXN 31
/* this is the actual board size to be used */
int n;
/* half of the board size */
int mid;
/* only used to init arrays, may instead use e.g. int a[MAXN+1] = {1}; */
int idx;
/* number of found solutions to the n-queens problem */
long count = 0L;
/* a[x] is true, if a queen can be placed in column x  (x: 1..n)
 We use here a int number and bitmask instead of  int a[MAXN + 1] */
int aInt = -2; // all bits 1 except at index 0
/* b[y+x] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y-k) for all k. "/" antidiagonal line
 We use here a long number and bitmask instead of  int b[2 * MAXN + 1] */
long bLong = -4L; // all bits 1 except at index 0 and 1
/* c[y-x+n] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y+k) for all k. "\" diagonal line
 We use here a long number and bitmask instead of  int c[2 * MAXN] */
long cLong = -2L; // all bits 1 except at index 0
/* x[y] has an entry for each row, which tells, in which column the queen is
 put for current partly solution. This is required here ONLY for debug. */
int x[MAXN + 1];

/* Function prototypes */
void try1(int i, int mirrorExit);
void tryMid(int i, int j);

/* get boolean value for a[j] */
int getA(int j) {
	return (aInt & (1 << j));
}

/* set/clear boolean value for a[j] */
void setA(int j, int value) {
	if (value) {
		aInt = aInt | (1 << j);
	} else {
		aInt = aInt & ~(1 << j);
	}
}

long getB(int j) {
	return (bLong & (1 << j));
}

void setB(int j, int value) {
	if (value) {
		bLong = bLong | (1 << j);
	} else {
		bLong = bLong & ~(1 << j);
	}
}

long getC(int j) {
	return (cLong & (1 << j));
}

void setC(int j, int value) {
	if (value) {
		cLong = cLong | (1 << j);
	} else {
		cLong = cLong & ~(1 << j);
	}
}

/*
 * If we have odd number of n, then we have to do an extra run for the n/2 + 1
 * column.
 */
void tryMid(int i, int j) {
	if (getA(j) && getB(i + j) && getC(i - j + n)) {
		setA(j, 0);
		setB(i + j, 0);
		setC(i - j + n, 0);
		try1(i + 1, 1);
		setA(j, 1);
		setB(i + j, 1);
		setC(i - j + n, 1);
	}
}

/*
 * Search all solutions that start with a queen in the row i. If mirrorExit,
 * then we do only columns 1..n/2 . With mirrorExit we control that only 1..n/2
 * is checked on the first row, for all deeper rows we do as usual 1..n.
 */
void try1(int i, int mirrorExit) {
	int j = 0; // column
	// If this is the first row, loop through all columns 1..n/2 and do dfs on
	// every column. Otherwise do columns 1..n .
	do {
		j = j + 1; // set column (1..n or 1..n/2)
		if (mirrorExit && (j > mid)) {
			// Do not count mirrored solutions.
			return;
		}
		if (getA(j) && getB(i + j) && getC(i - j + n)) {
			/* store result: on column j, row i a queen is placed now */
			x[i] = j;
			/* Set all array entries associated with this field to false,
			 meaning that we cannot place a queen on fields which are
			 covered by the queen we just put on this field. */
			setA(j, 0);
			setB(i + j, 0);
			setC(i - j + n, 0);
			/* do recursive calls until last row reached */
			if (i < n) {
				/* search for solutions (dfs) on next row */
				try1(i + 1, 0);
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
			setA(j, 1);
			setB(i + j, 1);
			setC(i - j + n, 1);
		}
	} while (j != n);
}

int main(int argc, char *argv[]) {
	if (argc <= 1 || (n = atoi(argv[1])) <= 0) {
		n = 8;
	}
	mid = n >> 1; // mid = n/2
	// start recursive backtracking algorithm at first row
	try1(1, 1);
	// if we have odd n, we have to do column n/2 + 1 extra
	if ((1 & n) == 1) {
		tryMid(1, (mid + 1));
	}
	// add mirrored solutions (simply double count)
	count = count << 1;
	printf("%ld\n", count); // print result (number of solutions found)
	return 0;
}

