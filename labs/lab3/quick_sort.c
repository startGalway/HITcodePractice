#include "sort.h"

size_t partition(void *base, size_t low, size_t high, size_t size, CompareFunc cmp) {
    char *arr = base;
    void *pivot = malloc(size);
    memcpy(pivot, arr + high * size, size);
    size_t i = low;
    for (size_t j = low; j < high; j++) {
        if (cmp(arr + j * size, pivot) <= 0) {
            swap(arr + i * size, arr + j * size, size);
            i++;
        }
    }
    swap(arr + i * size, arr + high * size, size);
    free(pivot);
    return i;
}

void quick_sort_helper(void *base, size_t low, size_t high, size_t size, CompareFunc cmp) {
    if (low < high) {
        size_t pi = partition(base, low, high, size, cmp);
        if (pi > 0) quick_sort_helper(base, low, pi - 1, size, cmp);
        quick_sort_helper(base, pi + 1, high, size, cmp);
    }
}

void quick_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    quick_sort_helper(base, 0, nmemb - 1, size, cmp);
}