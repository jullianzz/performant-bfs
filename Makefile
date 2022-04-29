# Author: Julia Zeng
# Makefile for building benchmarks and tests

# Use 'make test' to run benchmarking for all BFS implementations
test: *.c *.h
	cc -Wall -Werror -std=gnu99 -pedantic -O0 -g -pthread matrix.c graph.c benchmark.c serial.c test.c -o test

# Use 'make tb_serial' to run testbench (verification) for serial BFS
tb_serial: *.c *.h
	cc -Wall -Werror -std=gnu99 -pedantic -O0 -g -pthread matrix.c graph.c benchmark.c serial.c serial_tb.c -o tb_serial

.PHONY: clean

clean:
	rm -f *.o
