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

struct stat infstats;

int main(void){

    int outfile = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    int infile = open("in.txt", O_RDONLY);

    fstat(infile, &infstats);
    
    FileHeader *infhead = (FileHeader *)calloc(1, sizeof(FileHeader));
    infhead->magic = MAGIC;
    infhead->protection = infstats.st_mode;

    write_header(outfile, infhead);

    free(infhead);


    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;

    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = START_CODE;


    while(read_sym(infile, &curr_sym)){
        //printf("sym: %c\n", curr_sym);
        TrieNode *next_node = trie_step(curr_node, curr_sym);

        if(next_node){

            prev_node = curr_node;
            curr_node = next_node;

        } else {

            buffer_pair(outfile, curr_node->code, curr_sym, bitlen(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code = next_code + 1;
        }

        if(next_code == MAX_CODE){
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }

        prev_sym = curr_sym;
    }

    if(curr_node != root){
        buffer_pair(outfile, prev_node->code, prev_sym, bitlen(next_code));
        next_code = (next_code + 1) % MAX_CODE;
    }

    buffer_pair(outfile, STOP_CODE, 0, bitlen(next_code));
    flush_pairs(outfile);

    trie_delete(root);
    close(infile);
    close(outfile);

    return 0;
}


uint8_t bitlen(uint16_t x){
    return log2(x) + 1;
}
