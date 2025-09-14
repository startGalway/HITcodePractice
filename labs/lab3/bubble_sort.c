#include "sort.h"

void bubble_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp) {
    if (nmemb < 2) return;
    char *arr = base;
    for (size_t i = 0; i < nmemb - 1; i++) {
        for (size_t j = 0; j < nmemb - i - 1; j++) {
            if (cmp(arr + j * size, arr + (j + 1) * size) > 0) {
                swap(arr + j * size, arr + (j + 1) * size, size);
            }
        }
        #ifdef DEBUG_BUBBLE_TRACE
        if (i == 4) { // after 5 outer passes (0..4)
            // Attempt to print as int array when size matches
            size_t count = nmemb;
            if (size == sizeof(int)) {
                printf("[DEBUG] bubble after 5 passes:\n");
                print_array_int((int*)arr, (int)count);
            }
        }
        #endif
    }
}