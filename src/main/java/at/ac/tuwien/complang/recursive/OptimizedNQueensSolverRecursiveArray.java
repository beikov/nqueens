package at.ac.tuwien.complang.recursive;

/**
 * Based on OriginalNQueensSolver.
 * 
 * Removed field x since there is no real use for it
 * Removed maxN and used n instead
 * Common subexpressions eliminated
 * Skipped mirror solutions
 */
public class OptimizedNQueensSolverRecursiveArray {

    private final int n;
    private final int mid;

    // 1..n
    // a[x] ist true, wenn man in Spalte x eine Dame setzen kann
    private final boolean[] a;

    // 2..2*n
    // b[x+y] ist true, wenn man in der Diagonale, 
    // die die Felder (x+k, y-k) (fuer alle k) enthaelt, eine Dame setzen kann
    private final boolean[] b;

    // 1..2*n-1
    // c[x-y+n] ist true, wenn man in der Diagonale,
    // die die Felder (x+k, y+k) (fuer alle k) enthaelt, eine Dame setzen kann
    private final boolean[] c;

    private long count = 0;

    public OptimizedNQueensSolverRecursiveArray(int n) {
        this.n = n;
        this.mid = n >> 1;
        this.a = new boolean[n + 1];
        this.b = new boolean[2 * n + 1];
        this.c = new boolean[2 * n];
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
    
    private void tryMid(final int i, final int j) {
        int bIndex = i + j;
        int cIndex = i + n - j;
        
        if (a[j] && b[bIndex] && c[cIndex]) {
            a[j] = false;
            b[bIndex] = false;
            c[cIndex] = false;
            try1(i + 1, true);
            a[j] = true;
            b[bIndex] = true;
            c[cIndex] = true;
        }
    }

    private void try1(final int i, boolean mirrorExit) {
        int j = 0;
        int bIndex = i;
        int cIndex = i + n;
        do {
            j++;
            bIndex++;
            cIndex--;
            if (mirrorExit && j > mid) {
                // Don't count mirrored solutions
                return;
            }
            if (a[j] && b[bIndex] && c[cIndex]) {
                if (i < n) {
                    a[j] = false;
                    b[bIndex] = false;
                    c[cIndex] = false;
                    try1(i + 1, false);
                    a[j] = true;
                    b[bIndex] = true;
                    c[cIndex] = true;
                } else {
                    count++;
                }
            }
        } while (j != n);
    }

    public long solve() {
        try1(1, true);
        
        if ((1 & n) == 1) {
            tryMid(1, mid + 1);
        }
        
        // Add mirrored solutions
        count = count << 1;
        
        return count;
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        OptimizedNQueensSolverRecursiveArray o = new OptimizedNQueensSolverRecursiveArray(n);
        System.out.println(o.solve());
    }
}
