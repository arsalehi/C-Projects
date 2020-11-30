CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CC = clang $(CFLAGS)

hatterspeak	:	hatterspeak.o bf.o bv.o speck.o parser.o ll.o hatter.o hash.o
	$(CC) -o hatterspeak hatterspeak.o bf.o bv.o speck.o parser.o ll.o hatter.o hash.o
tests:	tests.o bf.o bv.o speck.o ll.o hatter.o hash.o 
	$(CC) -o tests tests.o bf.o bv.o speck.o ll.o hatter.o hash.o 
bf.o:	bf.c bf.h
	$(CC) -c bf.c
ll.o:	ll.c ll.h
	$(CC) -c ll.c
hash.o:	hash.h hash.c ll.h speck.h 
	$(CC) -c hash.c
hatter.o:	hatter.c hatter.h
	$(CC) -c hatter.c
parser.o	:	parser.c parser.h
	$(CC) -c parser.c
speck.o:	speck.c speck.h
	$(CC) -c speck.c
bv.o:	bv.c bv.h
	$(CC) -c bv.c
hatterspeak.o	:	hatterspeak.c
	$(CC) -c hatterspeak.c
tests.o:	tests.c	
	$(CC) -c tests.c
clean	:
	rm -f hatterspeak.o bf.o bv.o speck.o parser.o ll.o hatter.o hash.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind:
	valgrind ./hatterspeak