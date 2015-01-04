package at.ac.tuwien.complang.recursive;

/**
 * Based on OriginalNQueensSolver.
 * 
 * Removed field x since there is no real use for it
 * Removed maxN and used n instead
 * 
 */
public class NQueensSolverRecursive2 {

    private final int n;
    
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
    
    public NQueensSolverRecursive2(int n) {
        this.n = n;
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

    private void try1(int i) {
        int j = 0;
        do {
            j = j + 1;
            if (a[j] && b[i + j] && c[i - j + n]) {
                a[j] = false;
                b[i + j] = false;
                c[i - j + n] = false;
                if (i < n) {
                    try1(i + 1);
                } else {
                    count++;
                }
                a[j] = true;
                b[i + j] = true;
                c[i - j + n] = true;
            }
        } while (j != n);
    }

    public long solve() {
        try1(1);
        return count;
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        NQueensSolverRecursive2 o = new NQueensSolverRecursive2(n);
        System.out.println(o.solve());
    }
}
