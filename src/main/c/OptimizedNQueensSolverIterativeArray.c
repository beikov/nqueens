/******************************************************************************
 * converted from recursive to interative program.
 * only clear queens from board if required
 * replace 'struct field f' (stack element) with simple integers
 * use char instead of integer in 'struct field' for stack elements
 * Symmetrie checking along the vertical middle line
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXN 31
/* this is the actual board size to be used */
int n;
/* half of n */
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
/* x[y] has an entry for each row which tells, in which column the queen is
 put for current partly solution. */
int *x;

struct field {
	char col;
	char row;
};

/* Stack */
struct field stack[MAXN * MAXN];

/* Pointer to next free entry on top of Stack. If 0, the stack is empty. */
int last = 0;

/*
 * Return true only if a queen can savely be placed in column x and row y.
 * This is Niklaus Wirth's validation algorithm.
 */
int isValid(int x, int y) {
	if (a[x] && b[y + x] && c[y - x + n]) {
		return 1;
	} else {
		return 0;
	}
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
		a[j] = 0;
		b[1 + j] = 0;
		c[1 - j + n] = 0;

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
				a[x[crow]] = 1;
				b[crow + x[crow]] = 1;
				c[crow - x[crow] + n] = 1;
				x[crow] = 0;
				if (x[crow + 1]) {
					a[x[crow + 1]] = 1;
					b[crow + 1 + x[crow + 1]] = 1;
					c[crow + 1 - x[crow + 1] + n] = 1;
					x[crow + 1] = 0;
				}
			}
			if (isValid(ccol, crow)) {
				// place queen in this field
				x[crow] = ccol;
				a[ccol] = 0;
				b[crow + ccol] = 0;
				c[crow - ccol + n] = 0;
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
					a[ccol] = 1;
					b[crow + ccol] = 1;
					c[crow - ccol + n] = 1;
					x[crow] = 0;
				}
			}
		}
		// clear any leftover queens in all rows (except the last one)
		for (y = 1; y < n; y++) {
			if (x[y]) {
				a[x[y]] = 1;
				b[y + x[y]] = 1;
				c[y - x[y] + n] = 1;
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
	// initialize all arrays
	// make arrays the required size
	a = (int *) malloc((n + 1) * sizeof(int));
	b = (int *) malloc((2 * n + 1) * sizeof(int));
	c = (int *) malloc((2 * n) * sizeof(int));
	x = (int *) malloc((n + 1) * sizeof(int));
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
	for (i = 0; i <= (n + 1); i++) {
		x[i] = 0;
	}
	try(); // start
	// add mirrored solutions (simply double count)
	count = count << 1;
	printf("%ld\n", count); // print result (number of solutions found)
	return 0;
}

