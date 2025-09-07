#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float score;
} Student;
int main()
{
    FILE *fp = fopen("students.bin","rb");
    if (fp == NULL)
    {
        perror("error:fopen error");
        return -1;
    }
    Student students[20];
    size_t read_count = fread(students, sizeof(Student), 20, fp);
    if(read_count == 0)
    {
        if (feof(fp))
        {
            printf("End of file reached.\n");
        }
        else if (ferror(fp))
        {
            perror("Error reading file");
        }
    }
    for(int i=0;i<read_count;i++)
    {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }
    fclose(fp);
    return 0;
}