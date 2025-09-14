#include "sort.h"

void selection_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    if (nmemb < 2) return;
    char *arr = base;
    for (size_t i = 0; i < nmemb - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < nmemb; j++) {
            if (cmp(arr + j * size, arr + min_idx * size) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr + i * size, arr + min_idx * size, size);
        }
    }
}