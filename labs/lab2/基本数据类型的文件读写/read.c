#include <stdio.h>
int main()
{
    FILE *fp = fopen("./text.txt","r");
    if(fp == NULL)
    {
        printf("File open error\n");
        return -1;
    }
    char str[30] = {0};
    while(fgets(str, 30, fp) != NULL)
    {
        printf("%s", str);
    }
    fclose(fp);
    return 0;
}