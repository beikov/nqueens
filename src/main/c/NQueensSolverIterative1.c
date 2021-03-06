/******************************************************************************
 * converted from recursive to interative program.
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* maximum board size we will process */
#define MAXN 100
/* this is the actual board size to be used */
int n;
/* only used to init arrays, may instead use e.g. int a[MAXN+1] = {1}; */
int idx;
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
/* x[y] has an entry for each row which tells, in which column the queen is
 put for current partly solution. Init with all 0.
 FYI: We NEED this here for backtracking, so we can clean up queens when
 going backwards in the search tree. (this is all done "automatically"
 when using recursion) */
int x[MAXN + 1] = { 0 };

struct field {
	int col;
	int row;
};

/* Stack */
struct field stack[MAXN * MAXN];

/* Pointer to next free entry on top of Stack. If 0, the stack is empty. */
int last;

/* The currently processed field. */
struct field f;

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
 * This clears all eventually leftover queens from the board beginning at
 * startRow downwards.
 */
void clearQueens(int startRow) {
	int y = 1;
	for (y = startRow; y < n; y++) {
		if (x[y]) {
			// clear Niklaus Wirth's arrays
			a[x[y]] = 1;
			b[y + x[y]] = 1;
			c[y - x[y] + n] = 1;
			x[y] = 0;
		}
	}
}

/*
 * Do iterative DFS for every field in the first row.
 */
void try(void) {
	int j = 1; // main column counter (1..n)
	int jt = 1; // temporary column counter

	for (j = 1; j <= n; j++) {
		// do DFS for a queen placed in first (topmost) row on column j (1..n)
		// mark queen placed in field of first row (j,1)
		x[1] = j;
		a[j] = 0;
		b[1 + j] = 0;
		c[1 - j + n] = 0;
		// push all fields from row 2 on stack, so we can process them in a
		// dfs way.
		for (jt = 1; jt <= n; jt++) {
			// push current field onto stack
			stack[last].col = jt;
			stack[last++].row = 2;
		}
		// If stack is empty we have checked all edges in our search tree.
		while (last) {
			// Grab next field from stack and do dfs on it.
			// For simple structs (as ours) the compiler will make memcopy, so
			// we can use simple assign here.
			f = stack[--last];
			if (x[f.row]) {
				// There is already a queen placed in the current row. So we
				// know, that we have gone backwards in the tree - and we need
				// to clear the queen in the current row. And also in all rows
				// beneath us. It might happen that there was no field from next
				// row processed during backtracking - and then the
				// queen will be still there in the next row!
				clearQueens(f.row);
			}
			if (isValid(f.col, f.row)) {
				// place queen in this field
				x[f.row] = f.col;
				a[f.col] = 0;
				b[f.row + f.col] = 0;
				c[f.row - f.col + n] = 0;
				if (f.row != n) {
					// We have to go 1 row deeper and push all fields on stack.
					for (jt = 1; jt <= n; jt++) {
						stack[last].col = jt;
						stack[last++].row = (f.row) + 1;
					}
				} else {
					// We hit last row, this is a valid solution.
					count++;
					// We also need to clean up board for the last row here!
					a[f.col] = 1;
					b[f.row + f.col] = 1;
					c[f.row - f.col + n] = 1;
					//printSolution(); // TODO: skip this line for perf tests
					x[f.row] = 0;
				}
			}
		}
		// Clear queen in first row. All other queens have been removed already.
		a[j] = 1;
		b[1 + j] = 1;
		c[1 - j + n] = 1;
	}
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
	try(); // start
	printf("%ld\n", count); // print result (number of solutions found)
	return 0;
}
