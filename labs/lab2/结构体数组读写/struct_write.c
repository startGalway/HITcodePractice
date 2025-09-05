#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float score;
} Student;

int main()
{
    FILE *file;
    Student students[10] = {
        {1, "Alice", 85.5},
        {2, "Bob", 90.0},
        {3, "Charlie", 78.0},
        {4, "David", 92.5},
        {5, "Eve", 88.0},
        {6, "Frank", 75.5},
        {7, "Grace", 80.0},
        {8, "Hannah", 95.0},
        {9, "Ivy", 82.5},
        {10, "Jack", 89.0}
    };

    file = fopen("students.bin", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    fwrite(students, sizeof(Student), 10, file);
    fclose(file);

    printf("finished\n");
    return 0;
}