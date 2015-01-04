
package at.ac.tuwien.complang.iterative;

/**
 *
 */
public class NQueensSolverIterative3 {
    
    private static final int maxN = 100;
    private final int n;
    
    // 1..n
    // a[x] ist true, wenn man in Spalte x eine Dame setzen kann
    private final boolean[] a = new boolean[maxN + 1];
    
    // 2..2*n
    // b[x+y] ist true, wenn man in der Diagonale, 
    // die die Felder (x+k, y-k) (fuer alle k) enthaelt, eine Dame setzen kann
    private final boolean[] b = new boolean[2 * maxN + 1];
    
    // 1..2*n-1
    // c[x-y+n] ist true, wenn man in der Diagonale,
    // die die Felder (x+k, y+k) (fuer alle k) enthaelt, eine Dame setzen kann
    private final boolean[] c = new boolean[2 * maxN];
    
    // 1..n
    // x[y] enthaelt die Spalten der aktuellen (Teil)loesung
    private final int[] x = new int[maxN + 1];

    private long count = 0;
    
    public NQueensSolverIterative3(int n) {
        this.n = n;
        int i;

        for (i = 1; i <= n; i++) {
            a[i] = true;
        }
        for (i = 2; i <= 2 * n; i++) {
            b[i] = true;
        }
        for (i = 1; i <= 2 * n - 1; i++) {
            c[i] = true;
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
        int ccol = 1; // col number of current processed field
        int crow = 1; // row number of current processed field

        /* Pointer to next free entry on top of Stack. If 0, the stack is empty. */
        int last = 0;
    
        for (j = 1; j <= n; j++) {
            
            // do DFS for a queen placed in first (topmost) row on column j (1..n)
            // mark queen placed in field of first row (j,1)
            x[1] = j;
            a[j] = false;
            b[1 + j] = false;
            c[1 - j + n] = false;
            // push all fields from row 2 on stack, so we can process them in a
            // dfs way.
            for (jt = 1; jt <= n; jt++) {
                // push current field onto stack
                stack[last++] = stackElement(jt, 2);
            }
            // If stack is empty we have checked all edges in our search tree.
            while (last != 0) {
                // Grab next field from stack and do dfs on it.
                final long f = stack[--last];
                ccol = col(f);
                crow = row(f);
                if (x[crow] != 0) {
                    // There is already a queen placed in the current row. So we
                    // know, that we have gone backwards in the tree - and we need
                    // to clear the queen in the current row. And also in next row
                    // beneath us. It might happen that there was no field from next
                    // row processed during backtracking - and then the
                    // queen will be still there in the next row!
                    a[x[crow]] = true;
                    b[crow + x[crow]] = true;
                    c[crow - x[crow] + n] = true;
                    x[crow] = 0;
                    if (x[crow + 1] != 0) {
                        a[x[crow + 1]] = true;
                        b[crow + 1 + x[crow + 1]] = true;
                        c[crow + 1 - x[crow + 1] + n] = true;
                        x[crow + 1] = 0;
                    }
                }
                if (isValid(ccol, crow)) {
                    // place queen in this field
                    x[crow] = ccol;
                    a[ccol] = false;
                    b[crow + ccol] = false;
                    c[crow - ccol + n] = false;

                    if (crow != n) {
                        // We have to go 1 row deeper and push all fields on stack.
                        for (jt = 1; jt <= n; jt++) {
                            stack[last++] = stackElement(jt, crow + 1);
                        }
                    } else {
                        // We hit last row, this is a valid solution.
                        count++;
                        // We also need to clean up board for the last row here!
                        a[ccol] = true;
                        b[crow + ccol] = true;
                        c[crow - ccol + n] = true;

                        //printSolution(); // TODO: skip this line for perf tests
                        x[crow] = 0;
                    }
                }
            }
            // Clear queen in first row. All other queens have been removed already.
            a[j] = true;
            b[1 + j] = true;
            c[1 - j + n] = true;
        }
    }
    
    /**
     * Return true only if a queen can savely be placed in column x and row y.
     * This is Niklaus Wirth's validation algorithm.
     */
    private boolean isValid(int x, int y) {
        return a[x] && b[y + x] && c[y - x + n];
    }

    public long solve() {
        try0();
        return count;
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        NQueensSolverIterative3 o = new NQueensSolverIterative3(n);
        System.out.println(o.solve());
    }
}
