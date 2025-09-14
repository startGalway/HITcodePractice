#include "sort.h"

void heapify(void *base, size_t n, size_t i, size_t size, CompareFunc cmp) {
    char *arr = base;
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && cmp(arr + left * size, arr + largest * size) > 0)
        largest = left;

    if (right < n && cmp(arr + right * size, arr + largest * size) > 0)
        largest = right;

    if (largest != i) {
        swap(arr + i * size, arr + largest * size, size);
        heapify(base, n, largest, size, cmp);
    }
}

void heap_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    if (nmemb < 2) return;
    char *arr = base;
    for (int i = nmemb / 2 - 1; i >= 0; i--)
        heapify(arr, nmemb, i, size, cmp);

    for (int i = nmemb - 1; i > 0; i--) {
        swap(arr, arr + i * size, size);
        heapify(arr, i, 0, size, cmp);
    }
}