# Author: Julia Zeng
# Makefile for building benchmarks and tests

override CFLAGS := -Wall -Werror -std=gnu99 -pedantic -O0 -g -pthread
override LDLIBS := -pthread $(LDLIBS)
#override CXXFLAGS := -fsanitize=address $(CXXFLAGS)
#override LDFLAGS := -fsanitize=address $(LDFLAGS)

# Use 'make test' to run benchmarking for all BFS implementations
test: *.c *.h
	$(CC) $(CFLAGS) matrix.c graph.c benchmark.c bfs_serial.c test.c -o test

# Use 'make tb_serial' to run testbench (verification) for serial BFS
tb_serial: *.c *.h
	$(CC) $(CFLAGS) matrix.c graph.c benchmark.c bfs_serial.c tb_serial.c -o tb_serial

.PHONY: clean

clean:
	rm -f *.o;
	rm test;
	rm tb_serial;
