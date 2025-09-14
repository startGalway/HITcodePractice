#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sort.h"

typedef void (*sort_fn)(void*, size_t, size_t, CompareFunc);

static double now_sec() {
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

static void timed_call(const char *name, void *base, size_t n, size_t sz, CompareFunc cmp) {
    char sym[64];
    snprintf(sym, sizeof(sym), "%s", name);
    sort_fn real = (sort_fn)dlsym(RTLD_NEXT, sym);
    if (!real) {
        fprintf(stderr, "timewrap: failed to resolve %s\n", name);
        return;
    }
    double t1 = now_sec();
    real(base, n, sz, cmp);
    double t2 = now_sec();
    fprintf(stderr, "[LD_PRELOAD] %s elapsed: %.6f s (n=%zu)\n", name, t2 - t1, n);
}

void bubble_sort(void *base, size_t n, size_t sz, CompareFunc cmp) { timed_call("bubble_sort", base, n, sz, cmp); }
void selection_sort(void *base, size_t n, size_t sz, CompareFunc cmp) { timed_call("selection_sort", base, n, sz, cmp); }
void insertion_sort(void *base, size_t n, size_t sz, CompareFunc cmp) { timed_call("insertion_sort", base, n, sz, cmp); }
void merge_sort(void *base, size_t n, size_t sz, CompareFunc cmp) { timed_call("merge_sort", base, n, sz, cmp); }
void quick_sort(void *base, size_t n, size_t sz, CompareFunc cmp) { timed_call("quick_sort", base, n, sz, cmp); }
void heap_sort(void *base, size_t n, size_t sz, CompareFunc cmp) { timed_call("heap_sort", base, n, sz, cmp); }
