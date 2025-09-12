#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

typedef int (*CompareFunc)(const void*, const void*);

// 排序函数接口
void selection_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp);
void insertion_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp);
void bubble_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp);
void merge_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp);
void quick_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp);
void heap_sort(void *base, size_t nmemb, size_t size, CompareFunc cmp);

// 比较函数
int compare_int(const void *a, const void *b);
int compare_float(const void *a, const void *b);

// 结构体类型
typedef struct {
    int id;
    float score;
    char name[20];
} Student;

int compare_student(const void *a, const void *b);

// 辅助函数
void swap(void *a, void *b, size_t size);
void print_array_int(int *arr, int n);
void print_array_float(float *arr, int n);
void print_students(Student *arr, int n);

#endif