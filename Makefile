JAVA_BASE = src/main/java
JAVA_TARGET = target/classes
CUSTOM_JAVA_BASE = $(JAVA_BASE)/at/ac/tuwien/complang

C_BASE = src/main/c
C_TARGET = target

GCC = gcc
GCC_FLAGS = -O3

PERF_FLAGS = -e cycles -e instructions -e cache-misses -e branch-misses
QUEENS_N = 16

all: compile-c compile-java

clean:
	rm -Rf target

compile-java:
	mkdir -p $(JAVA_TARGET)
	javac -d $(JAVA_TARGET) $(JAVA_BASE)/*.java $(CUSTOM_JAVA_BASE)/*.java $(CUSTOM_JAVA_BASE)/recursive/*.java $(CUSTOM_JAVA_BASE)/iterative/*.java
	
perf-java-all:
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) nqueens $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.OriginalNQueensSolver $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.NQueensSolverIterative1 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.NQueensSolverIterative2 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.NQueensSolverIterative3 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.NQueensSolverIterative4 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.NQueensSolverIterative5 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.OptimizedNQueensSolverIterative $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.iterative.OptimizedNQueensSolverIterativeArray $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.recursive.NQueensSolverRecursive1 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.recursive.NQueensSolverRecursive2 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.recursive.NQueensSolverRecursive3 $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.recursive.OptimizedNQueensSolverRecursive $(QUEENS_N)
	perf stat $(PERF_FLAGS) java -classpath $(JAVA_TARGET) at.ac.tuwien.complang.recursive.OptimizedNQueensSolverRecursiveArray $(QUEENS_N)
	
compile-c:
	mkdir -p $(C_TARGET)
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueens $(C_BASE)/nqueens.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/OriginalNQueensSolver $(C_BASE)/OriginalNQueensSolver.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverIterative1 $(C_BASE)/NQueensSolverIterative1.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverIterative2 $(C_BASE)/NQueensSolverIterative2.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverIterative3 $(C_BASE)/NQueensSolverIterative3.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverIterative4 $(C_BASE)/NQueensSolverIterative4.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverIterative5 $(C_BASE)/NQueensSolverIterative5.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/OptimizedNQueensSolverIterative $(C_BASE)/OptimizedNQueensSolverIterative.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/OptimizedNQueensSolverIterativeArray $(C_BASE)/OptimizedNQueensSolverIterativeArray.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverRecursive1 $(C_BASE)/NQueensSolverRecursive1.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverRecursive2 $(C_BASE)/NQueensSolverRecursive2.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/NQueensSolverRecursive3 $(C_BASE)/NQueensSolverRecursive3.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/OptimizedNQueensSolverRecursive $(C_BASE)/OptimizedNQueensSolverRecursive.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/OptimizedNQueensSolverRecursiveArray $(C_BASE)/OptimizedNQueensSolverRecursiveArray.c

perf-c-all:
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueens $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverIterative1 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverIterative2 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverIterative3 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverIterative4 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverIterative5 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/OptimizedNQueensSolverIterative $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/OptimizedNQueensSolverIterativeArray $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverRecursive1 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverRecursive2 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/NQueensSolverRecursive3 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/OptimizedNQueensSolverRecursive $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/OptimizedNQueensSolverRecursiveArray $(QUEENS_N)
	
