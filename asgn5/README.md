ALI SALEHI	ASGN5	README.md

This program sorts random arrays using bubble, shell, quick, and binary insertion sort. To use the program first insure all .c and .h files are contained in the same directory as the Makefile. Secondly, run the make command to compile the program. Next, run ./sorting followed by "-A' for all sorting algorithms, "-q" for quick, "-s" for shell, "-b" for bubble, or "-i" for binary insertion. Then, to change the size of the array use "-n" followed by an integer determining the size. To change the number of elements to pring use "-p" followed by an integer. Lastly, to change the random seed include "-r" followed by an integer for the seed.

This program passed with no errors or memory leaks through valgrind.

Infer did produce one error message, that is likely misguided. It states "The value read from gap[_] was never initialized." though after the initialization of the gap array to the size of the array to be sorted, a while loop is used to change the proper amount of elements in the gap array. Any value read from gap[] will have been initialized by the time it is used in the main for loop for shell sort. 
