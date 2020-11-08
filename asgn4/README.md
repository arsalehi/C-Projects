Ali Salehi	ASGN4			README

To properly use this program, ensure that the Makefile is in the same directory as all .c and .h files. Secondly, run the "make" command to compile the code. Next, run "./sequence" followed by your choice of arguments that dictate the output. Use the 's' argument print out all primes, including the special primes. Use the 'p' argument to print palindromic primes of base 2, 9, 10, and 29 (10 + 's'). Lastly, the '-n' argument allows you to change the length of the BitVector, so include an integer following -n to set the length. Note that calling just '-s' or '-p' will default the length of the BitVector to 1000. 

Separate note:
Attempting to use a length value less than 2 will require you to rerun the program, given that sieve begins at 2and prime numbers are typically calculated beginning at 2.

This program has no memory leaks and no errors after running make infer.
