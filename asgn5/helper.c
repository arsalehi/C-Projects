#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h> // Might not need bc in header

uint32_t *init_array(int size, int seed){

    //Ensures no errors with too small of a size
    if(size < 1){
        size = 1;
    }

    //Initializes array with 32bit integers (Masked later to be max 30 bits)
    uint32_t *arr = (uint32_t *)calloc(size, sizeof(uint32_t));

    //Ensures calloc worked properly and frees and terminates if not
    if (!arr){
        free(arr); //Not sure if needed or if correct
        return 0;
    }

    //Set seed
    srand(seed);

    //Initialize each value in array
    for(int i = 0; i < size; ++i){
        arr[i] = (rand() & 0x3FFFFFFF); // May need to do 0x3FFFFFF & rand
    }

    return arr;
}

void print_array(uint32_t *arr, int size, int num_print){
    if(size < num_print){
        num_print = size;
    }
    for(int i = 0; i < num_print; ++i){
        printf("\t%10d", arr[i]);
        if(i % 7 == 6){
            printf("\n");
        }
    }
    printf("\n");

    return;
}

int swap(uint32_t *arr, int index1, int index2, int moves){
    
    uint32_t temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;

    moves += 3;
    return moves;
}

