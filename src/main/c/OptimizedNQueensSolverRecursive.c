/******************************************************************************
 * Based on OriginalNQueensSolver.
 *
 * Removed field x since there is no real use for it
 * Removed maxN and used n instead (use malloc to reserve int arrays on heap)
 * Common subexpressions eliminated
 * Symmetrie checking along the vertical middle line
 * Use long number and bitmask as boolean array (n limited to 31 now)
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
/* a[x] is true, if a queen can be placed in column x  (x: 1..n)
 We use here a int number and bitmask instead of  int a[n + 1] */
int aInt = -2; // all bits 1 except at index 0
/* b[y+x] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y-k) for all k. "/" antidiagonal line
 We use here a long number and bitmask instead of  int b[2 * n + 1] */
long bLong = -4L; // all bits 1 except at index 0 and 1
/* c[y-x+n] is true, if a queen can be placed in the diagonal which is covered
 by the fields (x+k, y+k) for all k. "\" diagonal line
 We use here a long number and bitmask instead of  int c[2 * n] */
long cLong = -2L; // all bits 1 except at index 0

/* Function prototypes */
void try1(int i, int mirrorExit);
void tryMid(int i, int j);

/*
 * If we have odd number of n, then we have to do an extra run for the n/2 + 1
 * column.
 */
void tryMid(int i, int j) {
	// Common subexpressions
	int aBitMask = 1 << j;
	long bBitMask = 1L << (i + j);
	long cBitMask = 1L << (i - j + n);
	if ((aInt & aBitMask) && (bLong & bBitMask) && (cLong & cBitMask)) {
		aInt = aInt & ~aBitMask;
		bLong = bLong & ~bBitMask;
		cLong = cLong & ~cBitMask;
		try1(i + 1, 1);
		aInt = aInt | aBitMask;
		bLong = bLong | bBitMask;
		cLong = cLong | cBitMask;
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
		// Common subexpressions
		bIndex++;
		cIndex--;
		int aBitMask = 1 << j;
		long bBitMask = 1L << (bIndex);
		long cBitMask = 1L << (cIndex);
		if ((aInt & aBitMask) && (bLong & bBitMask) && (cLong & cBitMask)) {
			aInt = aInt & ~aBitMask;
			bLong = bLong & ~bBitMask;
			cLong = cLong & ~cBitMask;
			if (i < n) {
				try1(i + 1, 0);
			} else {
				count++;
			}
			aInt = aInt | aBitMask;
			bLong = bLong | bBitMask;
			cLong = cLong | cBitMask;
		}
	} while (j != n);
}

int main(int argc, char *argv[]) {
	if (argc <= 1 || (n = atoi(argv[1])) <= 0) {
		n = 8;
	}
	mid = n >> 1; // mid = n/2
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

