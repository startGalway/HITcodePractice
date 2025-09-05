#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    float score;
} Student;

//先读取文件并打印，之后在第二个结构体后面插入一个新结构体，再次打印
int main()
{
    FILE *file;
    

    file = fopen("students.bin", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    Student students[10];
    fread(students, sizeof(Student), 10, file);
    for(int i=0;i<10;i++)
    {
        printf("ID: %d, Name: %s, Score: %.2f\n", students[i].id, students[i].name, students[i].score);
    }
    printf("--------------------------------------------------\n");
    fclose(file);
    //插入新结构体(把老数据全部读入，插入之后再写回)
    Student students_con_new[11];
    Student newStudent = {11, "NewStudent", 91.0};
    for(int i=0;i<2;i++)
    {
        students_con_new[i] = students[i];
    }
    students_con_new[2] = newStudent;
    for(int i=2;i<11;i++)
    {
        students_con_new[i] = students[i-1];
    }
    file = fopen("students.bin", "wb");
    if (file == NULL) {
        perror("Error opening file");
        return -1; 
    fwrite(students_con_new, sizeof(Student), 11, file);
    fclose(file);
    //再次读取并打印
    file = fopen("students.bin", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    Student students_after[11];
    fread(students_after, sizeof(Student), 11, file);
    for(int i=0;i<11;i++)
    {
        printf("ID: %d, Name: %s, Score: %.2f\n", students_after[i].id, students_after[i].name, students_after[i].score);
    }
    fclose(file);


}
}
}