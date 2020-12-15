ALI SALEHI      ASGN 7      README

This program utilizes the LZ78 compression algorithm in conjuction with a trie and a word table to encode and decode files respectively. Encoded files can be passed to the decode function to restore them to their original state. FIrst, ensure all .c and .h files are in the same directory as the Makefile. Then, run "make all" to compile both encode and decode. Next, to encode a file, run ./encode using the following arguments.

    -i: Specifies input to compress (filename) -- will be stdin by default
    -o: Specifies output of compressed input (filename) -- will be stdout by default
    -v: Will display compression statistics

These same arguments will be used when running ./decode. To view the outputs or check the success of the compression, the bash command "xxd" paired with a filename will display the bytes and text of the file provided.

The encode function utilizes a trie to store symbols and codes, which are encoded with variable bit lengths into the compressed file.

The decode function reads in the compressed file, and assigns the pairs of symbols and codes into words and stores these words in a word table. Finally, this word table is used to print the corresponiding output of the compressed file (aka the original file).

This program has no errors on valgrind, as well as none after running make infer.
