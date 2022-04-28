# Author: Julia Zeng
# Makefile for building benchmarks and tests

all: *.c *.h
	cc -Wall -Werror -std=gnu99 -pedantic -O0 -g -pthread matrix.c graph.c benchmark.c queue.c serial.c serial_tb.c -o tb_serial

.PHONY: clean

clean:
	rm -f *.o
