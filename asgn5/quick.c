#include "quick.h"
#include "helper.h"

int q_moves = 0;
int q_comparisons = 0;

int partition(uint32_t *arr, int left, int right){
    uint32_t pivot = arr[left];
    int lo = left + 1;
    int hi = right;

    while(1){
        q_comparisons++;
        while(lo <= hi && arr[hi] >= pivot){
            q_comparisons++;
            hi -=1;
        }
        q_comparisons++;
        while(lo <= hi && arr[lo] <= pivot){
            q_comparisons++;
            lo += 1;
        }
        if(lo <= hi){
            q_moves = swap(arr, lo, hi, q_moves);
        } else {
            break;
        }
    }
    q_moves = swap(arr, hi, left, q_moves);
    return hi;
}

void q_sort(uint32_t *arr, int left, int right){
    if(left < right){
        int index = partition(arr, left, right);
        q_sort(arr, left, index-1);
        q_sort(arr, index + 1, right);
    }
}

int q_get_moves(){
    return q_moves;
}

int q_get_comparisons(){
    return q_comparisons;
}

