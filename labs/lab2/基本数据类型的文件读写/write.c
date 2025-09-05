#include <stdio.h>
int main()
{
    FILE *fp1 = fopen("./WriteInText.txt","w");
    FILE *fp2 = fopen("./text.txt","r");
    if(fp2 == NULL)
    {
        printf("File open error\n");
        return -1;
    }
    char str[30] = {0};
    while(fgets(str, 30, fp2) != NULL)
    {
        fputs(str, fp1);
    }
    printf("finished\n");
}