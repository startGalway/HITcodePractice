#include "sort.h"

void merge(void *a, void *b, size_t l, size_t m, size_t r, size_t size, CompareFunc cmp) {
    size_t i = l, j = m + 1, k = l;
    char *arr = a, *temp = b;
    while (i <= m && j <= r) {
        if (cmp(arr + i * size, arr + j * size) <= 0) {
            memcpy(temp + k * size, arr + i * size, size);
            i++;
        } else {
            memcpy(temp + k * size, arr + j * size, size);
            j++;
        }
        k++;
    }
    while (i <= m) {
        memcpy(temp + k * size, arr + i * size, size);
        i++; k++;
    }
    while (j <= r) {
        memcpy(temp + k * size, arr + j * size, size);
        j++; k++;
    }
    for (k = l; k <= r; k++) {
        memcpy(arr + k * size, temp + k * size, size);
    }
}

void merge_sort_helper(void *a, void *b, size_t l, size_t r, size_t size, CompareFunc cmp) {
    if (l < r) {
        size_t m = l + (r - l) / 2;
        merge_sort_helper(a, b, l, m, size, cmp);
        merge_sort_helper(a, b, m + 1, r, size, cmp);
        merge(a, b, l, m, r, size, cmp);
    }
}

void merge_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    if (nmemb < 2) return;
    void *temp = malloc(nmemb * size);
    if (!temp) return;
    merge_sort_helper(base, temp, 0, nmemb - 1, size, cmp);
    free(temp);
}