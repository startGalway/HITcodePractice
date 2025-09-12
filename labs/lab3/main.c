#include "sort.h"
#include <sys/time.h>

#define MAX_SIZE 1000000

void generate_int_data(int *arr, int n);
void generate_float_data(float *arr, int n);
void generate_student_data(Student *arr, int n);
void copy_array(void *dest, void *src, size_t nmemb, size_t size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_elements>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0 || n > MAX_SIZE) {
        printf("Invalid size: %d\n", n);
        return 1;
    }

    int *int_orig = malloc(n * sizeof(int));
    float *float_orig = malloc(n * sizeof(float));
    Student *student_orig = malloc(n * sizeof(Student));

    generate_int_data(int_orig, n);
    generate_float_data(float_orig, n);
    generate_student_data(student_orig, n);

    void *data;
    size_t size;
    CompareFunc cmp;

    // 测试整型排序
    data = malloc(n * sizeof(int));
    copy_array(data, int_orig, n, sizeof(int));
    cmp = compare_int;

    clock_t start = clock();
    selection_sort(data, n, sizeof(int), cmp);
    clock_t end = clock();
    printf("Selection Sort (int): %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // 其他排序类似，此处省略...

    free(data);
    free(int_orig);
    free(float_orig);
    free(student_orig);

    return 0;
}

void generate_int_data(int *arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void generate_float_data(float *arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = (float)rand() / RAND_MAX * 100.0f;
    }
}

void generate_student_data(Student *arr, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i].id = rand() % 10000;
        arr[i].score = (float)rand() / RAND_MAX * 100.0f;
        sprintf(arr[i].name, "Student%d", i);
    }
}

void copy_array(void *dest, void *src, size_t nmemb, size_t size) {
    memcpy(dest, src, nmemb * size);
}