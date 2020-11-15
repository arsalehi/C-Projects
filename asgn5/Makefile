CFLAGS= -Wall -Wextra -Werror -pedantic -std=c99
CC = clang $(CFLAGS)

sorting	:	sorting.o helper.o bubble.o binary.o shell.o quick.o
	$(CC) -o sorting sorting.o helper.o bubble.o binary.o shell.o quick.o
helper.o	:	helper.c helper.h
	$(CC) -c helper.c
bubble.o	:	bubble.c bubble.h helper.c
	$(CC) -c bubble.c
binary.o	:	binary.c binary.h helper.c
	$(CC) -c binary.c
shell.o	:	shell.c shell.h helper.c
	$(CC) -c shell.c
quick.o	:	quick.c quick.h helper.c
	$(CC) -c quick.c
sorting.o	:	sorting.c
	$(CC) -c sorting.c
clean	:
	rm -f sorting sorting.o helper.o bubble.o binary.o shell.o quick.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
valgrind:
	valgrind ./sorting -A

