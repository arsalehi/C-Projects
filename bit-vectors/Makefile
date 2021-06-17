CFLAGS= -Wall -Wextra -Werror -pedantic
CC = clang $(CFLAGS)

sequence	:       sequence.o bv.o sieve.o
	$(CC) -o sequence sequence.o bv.o sieve.o -lm
sieve.o		:       sieve.c bv.h sieve.c
	$(CC) -c sieve.c
bv.o	:       bv.c bv.h
	$(CC) -c bv.c
sequence.o	:		sequence.c
	$(CC) -c sequence.c
clean	:
	rm -f sequence sequence.o bv.o sieve.o
infer	:
	make clean; infer-capture -- make; infer-capture -- make; infer-analyze -- make

