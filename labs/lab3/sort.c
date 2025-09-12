#include "sort.h"



// 比较整数
int compare_int(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

// 比较浮点数
int compare_float(const void *a, const void *b) {
    float arg1 = *(const float*)a;
    float arg2 = *(const float*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

// 比较学生结构体（按分数降序，姓名升序）
int compare_student(const void *a, const void *b) {
    const Student *s1 = (const Student*)a;
    const Student *s2 = (const Student*)b;
    if (s1->score != s2->score)
        return (s1->score < s2->score) ? 1 : -1; // 分数降序
    return strcmp(s1->name, s2->name); // 姓名升序
}

// 交换两个元素
void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

// 打印整数数组
void print_array_int(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 打印浮点数数组
void print_array_float(float *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
}

// 打印学生数组
void print_students(Student *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("ID: %d, Name: %s, Score: %.2f\n", arr[i].id, arr[i].name, arr[i].score);
}