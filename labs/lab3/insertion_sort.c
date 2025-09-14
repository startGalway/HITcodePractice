#include "sort.h"

void insertion_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    if (nmemb < 2) return;
    char *arr = base;
    for (size_t i = 1; i < nmemb; i++) {
        char temp[size];
        memcpy(temp, arr + i * size, size);
        size_t j = i;
        while (j > 0 && cmp(temp, arr + (j - 1) * size) < 0) {
            memcpy(arr + j * size, arr + (j - 1) * size, size);
            j--;
        }
        memcpy(arr + j * size, temp, size);
    }
}