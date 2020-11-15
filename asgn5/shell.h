#ifndef __SHELL_H__
#define __SHELL_H__

#include <inttypes.h>

// Sorts Using Shell Sort
//
// *arr = pointer to array to be sorted
// size = size of the array to be sorted
//
// Returns number of moves necessary to complete sorting
int s_sort(uint32_t *arr, int size);

// Returns number of comparisons
//
int s_get_comparisons();

#endif
