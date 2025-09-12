#include "sort.h"

void bubble_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    char *arr = base;
    for (size_t i = 0; i < nmemb - 1; i++) {
        for (size_t j = 0; j < nmemb - i - 1; j++) {
            if (cmp(arr + j * size, arr + (j + 1) * size) > 0) {
                swap(arr + j * size, arr + (j + 1) * size, size);
            }
        }
    }
}