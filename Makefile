# Author: Julia Zeng
# Makefile for building benchmarks and tests

override CFLAGS := -Wall -Werror -std=gnu99 -pedantic -O0 -g -pthread $(CFLAGS)
override LDLIBS := -pthread $(LDLIBS)

all: test.o

matrix.o: matrix.c matrix.h 

benchmark.o: benchmark.c benchmark.h param.h

queue.o: queue.h queue.c

serial.o: serial.c param.h benchmark.o matrix.o queue.o

test.o: test.c serial.o


######## Testbenches to verify BFS Output ########
serial_testbench: serial_testbench.c serial.o	// make serial_testbench


.PHONY: clean

clean:
	rm -f *.o
