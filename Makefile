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
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueensR1 $(C_BASE)/nqueensR1.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueensI0 $(C_BASE)/nqueensI0.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueensI1 $(C_BASE)/nqueensI1.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueensI2 $(C_BASE)/nqueensI2.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueensI3 $(C_BASE)/nqueensI3.c
	$(GCC) $(GCC_FLAGS) -o $(C_TARGET)/nqueensI4 $(C_BASE)/nqueensI4.c

perf-c-all:
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueens $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueensR1 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueensI0 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueensI1 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueensI2 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueensI3 $(QUEENS_N)
	perf stat $(PERF_FLAGS) ./$(C_TARGET)/nqueensI4 $(QUEENS_N)
	
