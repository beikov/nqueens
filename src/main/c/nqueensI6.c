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
 * 3.1.2015 converted from recursive to interative program.
 * 4.1.2015 (#1) implemented symmetrie check. All mirrored versions along the
 * 		vertical middle line are skipped, and at the end the resulting
 * 		solutions are doubled. Care must be taken if n is odd, then n/2 + 1
 * 		column must be run separate.
 * 4.1.2015 (#2) implement clearQueens inline where necessary.
 * 			(#3) replace 'struct field f' with simple integers
 * 			(#4) replace integers with chars in the 'struct field' definition
 * 			FYI: reorder of 'for' loops makes it worse (contrary to the non-
 * 			symmetrie checking, where it improved performance a lot)
 * 5.1.2015 (#5) use 64bit long value and bitmasks instead of integer arrays for
 * 			boolean arrays a,b,c.
 * 			(#6) implement all getter methods for a,b,c arrays inline
 * 			FYI: implement setter methods inline for a,b,c inline made it worse,
 * 			so this was not done.
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* maximum board size we will process. If long value and bitmask is used for
 the used boolean arrays, this can only be 31 max. */
#define MAXN 31
/* this is the actual board size to be used */
int n;
/* half of n */
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
/* x[y] has an entry for each row which tells, in which column the queen is
 put for current partly solution. Init with all 0.
 FYI: We NEED this here for backtracking, so we can clean up queens when
 going backwards in the search tree. (this is all done "automatically"
 when using recursion) */
int x[MAXN + 1] = { 0 };

struct field {
	char col;
	char row;
};

/* Stack */
struct field stack[MAXN * MAXN];

/* Pointer to next free entry on top of Stack. If 0, the stack is empty. */
int last = 0;

/* set/clear boolean value for a[j] */
void setA(int j, int value) {
	if (value) {
		aInt = aInt | (1 << j);
	} else {
		aInt = aInt & ~(1 << j);
	}
}

void setB(int j, int value) {
	if (value) {
		bLong = bLong | (1 << j);
	} else {
		bLong = bLong & ~(1 << j);
	}
}

void setC(int j, int value) {
	if (value) {
		cLong = cLong | (1 << j);
	} else {
		cLong = cLong & ~(1 << j);
	}
}

/*
 * Return true only if a queen can savely be placed in column x and row y.
 * This is Niklaus Wirth's validation algorithm.
 */
int isValid(int x, int y) {
	if ((aInt & (1 << x)) && (bLong & (1 << (y + x)))
			&& (cLong & (1 << (y - x + n)))) {
		return 1;
	} else {
		return 0;
	}
}

void printSolution(void) {
	int k = 0;
	printf("#%ld: \t", count);
	for (k = 1; k <= n; k++) {
		printf("%d ", x[k]);
	}
	printf("\n");
}

/*
 * Do iterative DFS for every field in the first row.
 */
void try(void) {
	int j = 1; // main column counter (1..n)
	int jt = 1; // temporary column counter
	int y = 1; // start row for cleaning up queens
	int ccol = 1; // col number of current processed field
	int crow = 1; // row number of current processed field
// Do not count mirrored solutions, so only count up to the middle column.
	int odd = n & 1;
	int outerEnd = mid + odd;

	for (j = 1; j <= outerEnd; j++) {
		// do DFS for a queen placed in first (topmost) row on column j (1..n)
		// mark queen placed in field of first row (j,1)
		x[1] = j;
		setA(j, 0);
		setB(1 + j, 0);
		setC(1 - j + n, 0);

		if (j == outerEnd && odd == 1) {
			// when n is odd, only count to the middle column on the second row
			for (jt = 1; jt <= mid; jt++) {
				// push current field onto stack
				stack[last].col = (char) jt;
				stack[last++].row = (char) 2;
			}
		} else {
			// push fields from row 2 on stack, so we can process them in a
			// dfs way.
			for (jt = 1; jt <= n; jt++) {
				// push current field onto stack
				stack[last].col = (char) jt;
				stack[last++].row = (char) 2;
			}
		}
		// If stack is empty we have checked all edges in our search tree.
		while (last) {
			// Grab next field from stack and do dfs on it.
			ccol = stack[--last].col;
			crow = stack[last].row;
			if (x[crow]) {
				// There is already a queen placed in the current row. So we
				// know, that we have gone backwards in the tree - and we need
				// to clear the queen in the current row. And also in next row
				// beneath us. It might happen that there was no field from next
				// row processed during backtracking - and then the
				// queen will be still there in the next row!
				setA(x[crow], 1);
				setB(crow + x[crow], 1);
				setC(crow - x[crow] + n, 1);
				x[crow] = 0;
				if (x[crow + 1]) {
					setA(x[crow + 1], 1);
					setB(crow + 1 + x[crow + 1], 1);
					setC(crow + 1 - x[crow + 1] + n, 1);
					x[crow + 1] = 0;
				}
			}
			if (isValid(ccol, crow)) {
				// place queen in this field
				x[crow] = ccol;
				setA(ccol, 0);
				setB(crow + ccol, 0);
				setC(crow - ccol + n, 0);
				if (crow != n) {
					// We have to go 1 row deeper and push all fields on stack.
					for (jt = 1; jt <= n; jt++) {
						stack[last].col = (char) jt;
						stack[last++].row = (char) (crow + 1);
					}
				} else {
					// We hit last row, this is a valid solution.
					count++;
					// We also need to clean up board for the last row here!
					setA(ccol, 1);
					setB(crow + ccol, 1);
					setC(crow - ccol + n, 1);
					//printSolution(); // TODO: skip this line for perf tests
					x[crow] = 0;
				}
			}
		}
		// clear any leftover queens in all rows (except the last one)
		for (y = 1; y < n; y++) {
			if (x[y]) {
				setA(x[y], 1);
				setB(y + x[y], 1);
				setC(y - x[y] + n, 1);
				x[y] = 0;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc <= 1 || (n = atoi(argv[1])) <= 0) {
		n = 8;
	}
	mid = n >> 1; // mid = n/2
	try(); // start
// add mirrored solutions (simply double count)
	count = count << 1;
	printf("%ld\n", count); // print result (number of solutions found)
	return 0;
}

