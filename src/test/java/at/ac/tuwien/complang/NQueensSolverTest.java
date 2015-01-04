
package at.ac.tuwien.complang;

import at.ac.tuwien.complang.recursive.OptimizedNQueensSolverRecursiveArray;
import at.ac.tuwien.complang.recursive.OptimizedNQueensSolverRecursive;
import at.ac.tuwien.complang.iterative.NQueensSolverIterative1;
import at.ac.tuwien.complang.iterative.NQueensSolverIterative2;
import at.ac.tuwien.complang.iterative.NQueensSolverIterative3;
import at.ac.tuwien.complang.iterative.NQueensSolverIterative4;
import at.ac.tuwien.complang.iterative.NQueensSolverIterative5;
import at.ac.tuwien.complang.iterative.OptimizedNQueensSolverIterative;
import at.ac.tuwien.complang.iterative.OptimizedNQueensSolverIterativeArray;
import at.ac.tuwien.complang.recursive.NQueensSolverRecursive1;
import at.ac.tuwien.complang.recursive.NQueensSolverRecursive2;
import at.ac.tuwien.complang.recursive.NQueensSolverRecursive3;
import com.carrotsearch.junitbenchmarks.BenchmarkOptions;
import com.carrotsearch.junitbenchmarks.BenchmarkRule;
import java.util.Arrays;
import java.util.Collection;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Rule;
import org.junit.rules.TestRule;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

/**
 *
 * @author Christian
 */
@RunWith(Parameterized.class)
@BenchmarkOptions(benchmarkRounds = 5, warmupRounds = 5)
public class NQueensSolverTest {
    
    private final Integer n;
    private final Long count;
    
    @Rule
    public TestRule benchmarkRun = new BenchmarkRule();
    
    public NQueensSolverTest(int n, long count) {
        this.n = n;
        this.count = count;
    }
    
    @Parameterized.Parameters
    public static Collection<Object[]> getTestData() {
        return Arrays.asList(new Object[][] {
//            { 4, 2L },
//            { 5, 10L },
//            { 6, 4L },
//            { 7, 40L },
//            { 8, 92L },
//            { 9, 352L },
//            { 10, 724L },
//            { 11, 2680L },
//            { 12, 14200L },
//            { 13, 73712L },
//            { 14, 365596L },
            { 15, 2279184L },
        });
    }

    @Test
    public void testOriginal() {
        assertEquals(count.longValue(), new OriginalNQueensSolver(n).solve());
    }

    @Test
    public void testRecursive1() {
        assertEquals(count.longValue(), new NQueensSolverRecursive1(n).solve());
    }

    @Test
    public void testRecursive2() {
        assertEquals(count.longValue(), new NQueensSolverRecursive2(n).solve());
    }
    
    @Test
    public void testRecursive3() {
        assertEquals(count.longValue(), new NQueensSolverRecursive3(n).solve());
    }

    @Test
    public void testOptimizedRecursive() {
        assertEquals(count.longValue(), new OptimizedNQueensSolverRecursive(n).solve());
    }
    
    @Test
    public void testOptimizedRecursiveArray() {
        assertEquals(count.longValue(), new OptimizedNQueensSolverRecursiveArray(n).solve());
    }

    @Test
    public void testIterative1() {
        assertEquals(count.longValue(), new NQueensSolverIterative1(n).solve());
    }

    @Test
    public void testIterative2() {
        assertEquals(count.longValue(), new NQueensSolverIterative2(n).solve());
    }
    
    @Test
    public void testIterative3() {
        assertEquals(count.longValue(), new NQueensSolverIterative3(n).solve());
    }
    
    @Test
    public void testIterative4() {
        assertEquals(count.longValue(), new NQueensSolverIterative4(n).solve());
    }
    
    @Test
    public void testIterative5() {
        assertEquals(count.longValue(), new NQueensSolverIterative5(n).solve());
    }
    
    @Test
    public void testOptimizedIterative() {
        assertEquals(count.longValue(), new OptimizedNQueensSolverIterative(n).solve());
    }
    
    @Test
    public void testOptimizedIterativeArray() {
        assertEquals(count.longValue(), new OptimizedNQueensSolverIterativeArray(n).solve());
    }
    
}
