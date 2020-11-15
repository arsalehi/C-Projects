#include "binary.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>

int bi_comparisons = 0;

int bi_sort(uint32_t *arr, int size) {
  int moves = 0;

  for (int i = 1; i < size; ++i) {
    uint32_t value = arr[i];
    int left = 0;
    int right = i;

    while (left < right) {
      int mid = left + ((right - left) / 2);

      bi_comparisons++;
      if (value >= arr[mid]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    for (int j = i; j > left; j--) {
      moves = swap(arr, j - 1, j, moves);
    }
  }

  return moves;
}

int bi_get_comparisons() { return bi_comparisons; }
