#include <stdio.h>

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