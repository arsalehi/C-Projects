#ifndef __BINARY_H__
#define __BINARY_H__

#include <inttypes.h>

// Sorts Using Binary Insertion Sort
//
// *arr = pointer to array to be sorted
// size = size of the array to be sorted
//
// Returns number of moves necessary to complete sorting
int bi_sort(uint32_t *arr, int size);

// Returns number of comparisons
//
int bi_get_comparisons();

#endif
