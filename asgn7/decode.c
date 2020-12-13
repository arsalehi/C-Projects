#include <stdio.h>
#include <stdlib.h>
#include "word.h"
#include "code.h"
#include "trie.h"
#include "io.h"
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

uint8_t bitlen(uint16_t x);

int main(void){

    int infile = open("out.txt", O_RDONLY);
    int outfile = open("dec.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    
    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = START_CODE;

    while(read_pair(infile, &curr_code, &curr_sym, bitlen(next_code))){
        printf("Cur code: %d\n", curr_sym);
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        printf("table[next_code]: %lu\n", table[next_code]->len);
        printf("added to word table\n");
        buffer_word(outfile, table[next_code]);
        printf("Buffered words\n");
        next_code++;
        if(next_code == MAX_CODE){
            wt_reset(table);
            next_code = START_CODE;
        }
    }
    flush_words(outfile);

    close(infile);
    close(outfile);
    wt_delete(table);

    printf("RAN SUCCESSFULLY\n");
    return 0;
}

uint8_t bitlen(uint16_t x){
    return log2(x) + 1;
}
