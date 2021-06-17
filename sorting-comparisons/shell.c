#include "shell.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>

int s_comparisons = 0;

int s_sort(uint32_t *arr, int size) {
  int gap[size];
  int gap_count = 0;
  int temp = size;
  int moves = 0;

  while (temp > 1) {
    if (temp <= 2) {
      gap[gap_count++] = 1;
      temp = 1;
    } else {
      gap[gap_count++] = (5 * temp / 11);
      temp = (5 * temp / 11);
    }
  }

  for (int i = 0; i < gap_count; ++i) {
    int step = gap[i];
    for (int j = step; j < size; ++j) {
      for (int k = j; k > step - 1; k -= step) {
        s_comparisons++;
        if (arr[k] < arr[k - step]) {
          moves = swap(arr, k, k - step, moves);
        }
      }
    }
  }
  return moves;
}

int s_get_comparisons() { return s_comparisons; }
