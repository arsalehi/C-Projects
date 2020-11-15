#include "bubble.h"
#include "helper.h"


int b_comparisons = 0;

int b_sort(uint32_t *arr, int size){
    int moves = 0;

    for(int i = 0; i < size -1; ++i){
        int j = size -1;
        while(j > i){
            b_comparisons++;
            if(arr[j] < arr[j-1]){
                moves = swap(arr, j, j-1, moves);
            }
            --j;
        }
    }

    return moves;
}

int b_get_comparisons(){
    return b_comparisons;
}

