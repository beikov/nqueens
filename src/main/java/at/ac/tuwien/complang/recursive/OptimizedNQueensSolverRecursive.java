package at.ac.tuwien.complang.recursive;

/**
 * Based on OriginalNQueensSolver but uses bit fields instead of arrays.
 */
public class OptimizedNQueensSolverRecursive {

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

    private long count = 0;

    public OptimizedNQueensSolverRecursive(int n) {
        this.n = n;
        this.mid = n >> 1;
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
    
    private void tryMid(final int i, final int j) {
        int bIndex = i + j;
        int cIndex = i + n - j;
        
        if (a(j) && b(bIndex) && c(cIndex)) {
            a(j, false);
            b(bIndex, false);
            c(cIndex, false);
            try1(i + 1, true);
            a(j, true);
            b(bIndex, true);
            c(cIndex, true);
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
            if (a(j) && b(bIndex) && c(cIndex)) {
                if (i < n) {
                    a(j, false);
                    b(bIndex, false);
                    c(cIndex, false);
                    try1(i + 1, false);
                    a(j, true);
                    b(bIndex, true);
                    c(cIndex, true);
                } else {
                    count++;
                }
            }
        } while (j != n);
    }

    public long solve() {
        try1(1, true);
        
        if ((1 & n) != 0) {
            tryMid(1, mid + 1);
        }
        
        // Add mirrored solutions
        count = count << 1;
        
        return count;
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        OptimizedNQueensSolverRecursive o = new OptimizedNQueensSolverRecursive(n);
        System.out.println(o.solve());
    }
}
