CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
LFLAGS = -lm

math	:	math.o
	$(CC) $(CFLAGS) -o math math.o $(LFLAGS)
math.o	:	math.c
	$(CC) $(CFLAGS) -c math.c
clean	:
	rm -f math math.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
