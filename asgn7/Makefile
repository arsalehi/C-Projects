CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
CC = clang $(CFLAGS)

all		:	encode decode
decode	:	decode.o word.o trie.o io.o
	$(CC) -o decode decode.o word.o trie.o io.o -lm
encode	:	encode.o word.o trie.o io.o
	$(CC) -o encode encode.o word.o trie.o io.o -lm
encode.o	:	encode.c
	$(CC) -c encode.c
decode.o	:	decode.c
	$(CC) -c decode.c
trie.o	:	trie.c trie.h
	$(CC) -c trie.c
word.o	:	word.c word.h
	$(CC) -c word.c
io.o	:	io.c io.h
	$(CC) -c io.c
clean	:
	rm -f encode encode.o decode decode.o io.o trie.o word.o
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
