// Enhanced demo main for modular sorting project
#include "sort.h"
#include <unistd.h>   // isatty
#include <sys/time.h>

#define MAX_SIZE 1000000

typedef enum { T_INT, T_FLOAT, T_STUDENT } ElemType;

typedef void (*sort_func)(void*, size_t, size_t, CompareFunc);

static void generate_int_data(int *arr, size_t n);
static void generate_float_data(float *arr, size_t n);
static void generate_student_data(Student *arr, size_t n);
static void copy_array(void *dest, const void *src, size_t nmemb, size_t size);
static size_t read_ints_from_stdin(int *arr, size_t n);
static void print_usage(const char *prog);

typedef struct {
    const char *name;
    sort_func fn;
} Algo;

static Algo ALGOS[] = {
    {"bub", bubble_sort},
    {"sel", selection_sort},
    {"ins", insertion_sort},
    {"mer", merge_sort},
    {"qui", quick_sort},
    {"heap", heap_sort}
};

static void run_one(const char *algo_name, ElemType type, size_t n,
                    const void *orig, size_t elem_size, CompareFunc cmp) {
    // Prepare copy for fair comparison
    void *data = malloc(n * elem_size);
    if (!data) {
        printf("error %d : %s\n", errno, strerror(errno));
        return;
    }
    copy_array(data, orig, n, elem_size);

    // Find algo
    sort_func fn = NULL;
    for (size_t i = 0; i < sizeof(ALGOS)/sizeof(ALGOS[0]); ++i) {
        if (strcmp(ALGOS[i].name, algo_name) == 0) { fn = ALGOS[i].fn; break; }
    }
    if (!fn) { printf("Unknown algo: %s\n", algo_name); free(data); return; }

    clock_t c1 = clock();
    fn(data, n, elem_size, cmp);
    clock_t c2 = clock();
    double elapsed = (double)(c2 - c1) / CLOCKS_PER_SEC;

    // Output results for small n
    if (n <= 32) {
        if (type == T_INT) {
            print_array_int((int*)data, (int)n);
        } else if (type == T_FLOAT) {
            print_array_float((float*)data, (int)n);
        } else {
            print_students((Student*)data, (int)n);
        }
    }
    printf("%s elapsed: %.6f s (n=%zu)\n", algo_name, elapsed, n);

    free(data);
}

int main(int argc, char *argv[]) {
    // Usage: ./main <type:int|float|student> <algo|all> <n> [--stdin]
    if (argc < 4) { print_usage(argv[0]); return 1; }

    ElemType type;
    if (strcmp(argv[1], "int") == 0) type = T_INT;
    else if (strcmp(argv[1], "float") == 0) type = T_FLOAT;
    else if (strcmp(argv[1], "student") == 0) type = T_STUDENT;
    else { print_usage(argv[0]); return 1; }

    const char *algo = argv[2];
    size_t n = (size_t)strtoull(argv[3], NULL, 10);
    if (n > MAX_SIZE) { printf("Invalid size: %zu\n", n); return 1; }
    int use_stdin = 0;
    if (argc >= 5 && strcmp(argv[4], "--stdin") == 0) use_stdin = 1;
    if (!isatty(STDIN_FILENO)) use_stdin = 1; // support redirection

    // Prepare origin data
    void *orig = NULL; size_t elem_size = 0; CompareFunc cmp = NULL;
    if (type == T_INT) {
        elem_size = sizeof(int); cmp = compare_int;
        int *arr = calloc(n, sizeof(int)); if (!arr) { printf("error %d : %s\n", errno, strerror(errno)); return 2; }
        if (use_stdin) {
            size_t got = read_ints_from_stdin(arr, n);
            if (got < n) {
                // Fill remaining with random to avoid UB
                for (size_t i = got; i < n; ++i) arr[i] = rand();
            }
        } else {
            generate_int_data(arr, n);
        }
        orig = arr;
        if (n <= 32) { printf("Input int data (n=%zu):\n", n); print_array_int(arr, (int)n); }
    } else if (type == T_FLOAT) {
        elem_size = sizeof(float); cmp = compare_float;
        float *arr = calloc(n, sizeof(float)); if (!arr) { printf("error %d : %s\n", errno, strerror(errno)); return 2; }
        generate_float_data(arr, n);
        orig = arr;
    } else {
        elem_size = sizeof(Student); cmp = compare_student;
        Student *arr = calloc(n, sizeof(Student)); if (!arr) { printf("error %d : %s\n", errno, strerror(errno)); return 2; }
        generate_student_data(arr, n);
        orig = arr;
    }

    if (strcmp(algo, "all") == 0) {
        const char *names[] = {"bub","sel","ins","mer","qui","heap"};
        for (size_t i = 0; i < sizeof(names)/sizeof(names[0]); ++i) {
            run_one(names[i], type, n, orig, elem_size, cmp);
        }
    } else {
        run_one(algo, type, n, orig, elem_size, cmp);
    }

    free(orig);
    return 0;
}

static void generate_int_data(int *arr, size_t n) {
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < n; i++) arr[i] = rand();
}

static void generate_float_data(float *arr, size_t n) {
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < n; i++) arr[i] = (float)rand() / RAND_MAX * 1000.0f;
}

static void generate_student_data(Student *arr, size_t n) {
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < n; i++) {
        arr[i].id = (int)(rand() % 100000);
        arr[i].score = (float)rand() / RAND_MAX * 100.0f;
        snprintf(arr[i].name, sizeof(arr[i].name), "Student%zu", i);
    }
}

static void copy_array(void *dest, const void *src, size_t nmemb, size_t size) {
    memcpy(dest, src, nmemb * size);
}

static size_t read_ints_from_stdin(int *arr, size_t n) {
    size_t cnt = 0; int x;
    while (cnt < n && scanf("%d", &x) == 1) arr[cnt++] = x;
    return cnt;
}

static void print_usage(const char *prog) {
    printf("Usage: %s <type:int|float|student> <algo:bub|sel|ins|mer|qui|heap|all> <n> [--stdin]\n", prog);
    printf("Examples:\n");
    printf("  %s int all 5\n", prog);
    printf("  echo '3 1 2 5 4' | %s int bub 5 --stdin\n", prog);
}