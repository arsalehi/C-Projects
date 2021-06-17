#ifndef __QUICK_H__
#define __QUICK_H__

#include <inttypes.h>

// partition is used in q_sort to place elements less than pivot on left
// and elements greater than the pivot on the right
//
// *arr = array to sort
// left = left index
// right = right index
//
// returns index of partitioning index used in q_sort
int partition(uint32_t *arr, int left, int right);

// Recursive function that sorts the given array
//
// *arr = array used to sort
// left = leftmost index
// right = rightmost index
//
void q_sort(uint32_t *arr, int left, int right);

// Gets number of moves
//
int q_get_moves();

// Gets number of comparisons
//
int q_get_comparisons();

#endif
