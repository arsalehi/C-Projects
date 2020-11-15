#include "helper.h"
#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#define OPTIONS "Absqip:r:n:"

int main(int argc, char **argv){

    int op = 0;

    bool do_bubble = false;
    bool do_shell = false;
    bool do_quick = false;
    bool do_binary = false;

    int num_print = 100;
    int seed = 8222022;
    int size = 100;

    while((op = getopt(argc, argv, OPTIONS)) != -1){
        switch(op){
        case 'A':
            do_bubble = true;
            do_shell = true;
            do_quick = true;
            do_binary = true;
            break;
        case 'b':
            do_bubble = true;
            break;
        case 's':
            do_shell = true;
            break;
        case 'q':
            do_quick = true;
            break;
        case 'i':
            do_binary = true;
            break;
        case 'p':
            num_print = atoi(optarg);
            break;
        case 'r':
            seed = atoi(optarg);
            break;
        case 'n':
            size = atoi(optarg);
            break;
        default:
            printf("Invalid argument: rerun program\n");
            break;
        }
    }

    if(do_binary){
        printf("Binary Insertion Sort\n");
        uint32_t *bi = init_array(size, seed);
        int moves = bi_sort(bi, size);
        int comps = bi_get_comparisons();
        printf("%d elements, %d moves, %d compares\n", size, moves, comps);
        print_array(bi, size, num_print);
        free(bi);
    }

    if(do_quick){
        printf("Quick Sort\n");
        uint32_t *q = init_array(size, seed);
        q_sort(q, 0, size-1);
        printf("%d elements, %d moves, %d compares\n", size, q_get_moves(), q_get_comparisons());
        print_array(q, size, num_print);
        free(q);
    }

    if(do_shell){
        printf("Shell Sort\n");
        uint32_t *sh = init_array(size, seed);
        int moves = s_sort(sh, size);
        int comps = s_get_comparisons();
        printf("%d elements, %d moves, %d compares\n", size, moves, comps);
        print_array(sh, size, num_print);
        free(sh);
    }

    if(do_bubble){
        printf("Bubble Sort\n");
        uint32_t *bub = init_array(size, seed);
        int moves = b_sort(bub, size);
        int comps = b_get_comparisons();
        printf("%d elements, %d moves, %d compares\n", size, moves, comps);
        print_array(bub, size, num_print);
        free(bub);
    }
    return 0;
}


