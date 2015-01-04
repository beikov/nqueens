
package at.ac.tuwien.complang.iterative;

/**
 *
 */
public class OptimizedNQueensSolverIterative {
    
    private final int n;
    private final int mid;
    
    // 1..n
    // a[x] ist true, wenn man in Spalte x eine Dame setzen kann
    private long aLong;
    
    // 2..2*n
    // b[x+y] ist true, wenn man in der Diagonale, 
    // die die Felder (x+k, y-k) (fuer alle k) enthaelt, eine Dame setzen kann
    private long bLong;
    
    // 1..2*n-1
    // c[x-y+n] ist true, wenn man in der Diagonale,
    // die die Felder (x+k, y+k) (fuer alle k) enthaelt, eine Dame setzen kann
    private long cLong;
    
    // 1..n
    // x[y] enthaelt die Spalten der aktuellen (Teil)loesung
    private final long[] x;

    private long count = 0;
    
    public OptimizedNQueensSolverIterative(int n) {
        this.n = n;
        this.mid = n >> 1;
        this.x = new long[n + 1];
        // All bits 1 except at index 0
        this.aLong = -2L;
        // All bits 1 except at index 0 and 1
        this.bLong = -4L;
        // All bits 1 except at index 0
        this.cLong = -2L;
    }
    
    private boolean a(int index) {
        return get(aLong, index);
    }
    
    private void a(int index, boolean value) {
        aLong = set(aLong, index, value);
    }
    
    private boolean b(int index) {
        return get(bLong, index);
    }
    
    private void b(int index, boolean value) {
        bLong = set(bLong, index, value);
    }
    
    private boolean c(int index) {
        return get(cLong, index);
    }
    
    private void c(int index, boolean value) {
        cLong = set(cLong, index, value);
    }
    
    private boolean get(long field, int index) {
        return (field & (1 << index)) != 0;
    }
    
    private long set(long field, int index, boolean value) {
        if (value) {
            return field | (1 << index);
        } else {
            return field & ~(1 << index);
        }
    }
    
    private long stackElement(int col, int row) {
        return ((long) col << 32) | (long) row;
    }
    
    private int col(long stackElement) {
        return (int) (stackElement >> 32);
    }
    
    private int row(long stackElement) {
        return (int) stackElement & -1;
    }

    /**
     * Do iterative DFS for every field in the first row.
     */
    private void try0() {
        /* Stack */
        final long[] stack = new long[n * n];
        
        int j;
        int jt;
        /* The currently processed field. */
        long f;
        int fRow;
        int fCol;
        /* Pointer to next free entry on top of Stack. If 0, the stack is empty. */
        int last = 0;
        
        // Don't count mirrored solutions, so only count to the middle
        int odd = n & 1;
        int outerEnd = mid + odd;
        int lastRow = -1;
    
        for (j = 1; j <= outerEnd; j++) {
            final int bIndex = 1 + j;
            final int cIndex = 1 - j + n;
            // do DFS for a queen placed in first (topmost) row on column j (1..n)
            // mark queen placed in field of first row (j,1)
            x[1] = (byte) j;
            a(j, false);
            b(bIndex, false);
            c(cIndex, false);
            
            if (j == outerEnd && odd == 1) {
                // when n is odd, only count to the middle column on the second row
                for (jt = 1; jt <= mid; jt++) {
                    // push current field onto stack
                    stack[last++] = stackElement(jt, 2);
                }
                
            } else {
                // push all fields from row 2 on stack, so we can process them in a
                // dfs way.
                for (jt = 1; jt <= n; jt++) {
                    // push current field onto stack
                    stack[last++] = stackElement(jt, 2);
                }
            }
            // If stack is empty we have checked all edges in our search tree.
            while (last != 0) {
                // Grab next field from stack and do dfs on it.
                // For simple structs (as ours) the compiler will make memcopy, so
                // we can use simple assign here.
                f = stack[--last];
                fRow = row(f);
                fCol = col(f);
                if (fRow < lastRow) {
                    // There is already a queen placed in the current row. So we
                    // know, that we have gone backwards in the tree - and we need
                    // to clear the queen in the current row. And also in all rows
                    // beneath us. It might happen that there was no field from next
                    // row processed during backtracking - and then the
                    // queen will be still there in the next row!
                    clearQueens(fRow, lastRow);
                }
                if (isValid(fCol, fRow)) {
                    // place queen in this field
                    x[fRow] = (byte) fCol;
                    a(fCol, false);
                    b(fRow + fCol, false);
                    c(fRow - fCol + n, false);
                    if (fRow != n) {
                        // We have to go 1 row deeper and push all fields on stack.
                        for (jt = 1; jt <= n; jt++) {
                            stack[last++] = stackElement(jt, fRow + 1);
                        }
                    } else {
                        // We hit last row, this is a valid solution.
                        count++;
                        // We also need to clean up board for the last row here!
                        a(fCol, true);
                        b(fRow + fCol, true);
                        c(fRow - fCol + n, true);
                        lastRow = fRow;
                    }
                } else {
                    lastRow = fRow;
                }
            }
            // Clear queen in first row. All other queens have been removed already.
            a(j, true);
            b(bIndex, true);
            c(cIndex, true);
        }
    }
    
    /**
     * Return true only if a queen can savely be placed in column x and row y.
     * This is Niklaus Wirth's validation algorithm.
     */
    private boolean isValid(int x, int y) {
        return a(x) && b(y + x) && c(y - x + n);
    }

    /**
     * This clears all eventually leftover queens from the board beginning at
     * startRow downwards. We can skip last row, because that one will always be
     * cleared.
     */
    private void clearQueens(int startRow, int lastRow) {
        for (int y = startRow; y <= lastRow; y++) {
            int col = (int) x[y];
            if (col != 0) {
                // clear Niklaus Wirth's arrays
                a(col, true);
                b(y + col, true);
                c(y - col + n, true);
                x[y] = 0;
            }
        }
    }

    public long solve() {
        try0();
        
        // Add mirrored solutions
        count = count << 1;
        
        return count;
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        OptimizedNQueensSolverIterative o = new OptimizedNQueensSolverIterative(n);
        System.out.println(o.solve());
    }
}
