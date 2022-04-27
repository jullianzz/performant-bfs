# Author: Julia Zeng
# Makefile for building benchmarks and tests

override CFLAGS := -Wall -Werror -std=gnu99 -pedantic -O0 -g -pthread $(CFLAGS)
override LDLIBS := -pthread $(LDLIBS)

all: test.o

matrix.o: matrix.c matrix.h 

param.o: param.h

benchmark.o: benchmark.c benchmark.h param.o

serial.o: serial.c param.o benchmark.o matrix.o

test.o: test.c serial.o param.o matrix.o benchmark.o 


.PHONY: clean

clean:
	rm -f test.o serial.o param.o matrix.o benchmark.o 

# test1: tls.o test1.c
# 	$(CC) $(CFLAGS) -pthread tls.o test1.c -o test1
