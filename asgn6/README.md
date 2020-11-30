ALI SALEHI	ASGN6		README


This program takes a set of "oldspeak" words that are forbidden, and a list of oldspeak words in "hatterspeak.txt" that have a proper translation. Words in neither of these files are considered safe. To use this program, first ensure all .h and .c files are in the same directory as the makefile. Second, run "make" to compile the program and prepare it for running. After compilation run "./hatterspeak" followed by your choice of the following arguments.

	-h: specifies size of the hash table (default is 10,000)
	-f: specifies size of the bloom filter (default is 2^20)
	-m: will use the move to front rule (set to false as default)
	-b: wil not use the move to front rule
	-s: will hide the text output and only reveal statistics

Following the argument, input the words you would like to test to see whether they are forbidden, or have a valid translation. Input as many words as desired, and when finished use ctrl +dto terminate input and move on with the program.

Note: you cannot run with both -m and -b, only one is allowed. 

This program has no valgrind errors or errors from make infer.
