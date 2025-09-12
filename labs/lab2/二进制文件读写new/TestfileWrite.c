#include <stdio.h>

#ifndef SORT_H
#define SORT_H

#include <stddef.h>

// 比较函数指针类型
typedef int (*cmp_func)(const void *, const void *);

// 支持的结构体类型
typedef struct {
    int key;
    float value;
} Record;

// 排序算法接口声明
void bubble_sort(void *base, size_t n, size_t size, cmp_func cmp);
void selection_sort(void *base, size_t n, size_t size, cmp_func cmp);
void insertion_sort(void *base, size_t n, size_t size, cmp_func cmp);
void merge_sort(void *base, size_t n, size_t size, cmp_func cmp);
void quick_sort(void *base, size_t n, size_t size, cmp_func cmp);
void heap_sort(void *base, size_t n, size_t size, cmp_func cmp); // 选做

#endif // SORT_H

int main() {
    FILE *fp = fopen("testfile.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "1007 wangsa\t97.5\t90.0  88.9  70\n");
    fprintf(fp, "1008 zhaosan\t98.5 \t80.0  89.9  91\n");
    fprintf(fp, "1009 lisan\t99.5\t79.0  99.9  72 \n");
    fprintf(fp, "1010 liusan\t95.5\t100.0 59.9 83\n");

    fclose(fp);
    return 0;
}