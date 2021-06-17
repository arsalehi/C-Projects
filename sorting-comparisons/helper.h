#ifndef __HELPER_H__
#define __HELPER_H__

#include <inttypes.h>
// Initializes array with random values dependent on given seed
uint32_t *init_array(int size, int seed);

// Prints array in desired format
void print_array(uint32_t *arr, int size, int num_print);

// Performs swap between two values in array
//
// *arr   = pointer to array
// index1 = first index to be swapped
// index2 = second index to be swapped
// moves  = number of moves to be incremented by 3
//
// Returns updated number of moves
int swap(uint32_t *arr, int index1, int index2, int moves);

#endif
