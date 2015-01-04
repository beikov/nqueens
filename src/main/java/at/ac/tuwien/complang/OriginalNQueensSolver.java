package at.ac.tuwien.complang;

/**
 * Original solution in idiomatic Java.
 *
 */
public class OriginalNQueensSolver {

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
    
    public OriginalNQueensSolver(int n) {
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

    private void try1(int i) {
        int j = 0;
        do {
            j = j + 1;
            if (a[j] && b[i + j] && c[i - j + n]) {
                x[i] = j;
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
        OriginalNQueensSolver o = new OriginalNQueensSolver(n);
        System.out.println(o.solve());
    }
}
