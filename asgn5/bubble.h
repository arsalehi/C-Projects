#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include <inttypes.h>

// Sorts Using Bubble Sort
//
// *arr = pointer to array to be sorted
// size = size of the array to be sorted
//
// Returns number of moves necessary to complete sorting
int b_sort(uint32_t *arr, int size);

// Returns number of comparisons
//
int b_get_comparisons();

#endif
