#include "fileop.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// 功能1：文本->结构体->二进制
int txt2bin(const char *txtfile, const char *binfile) {
    FILE *fin = fopen(txtfile, "r");
    if (!fin) {
        printf("error %d : %s (open %s)\n", errno, strerror(errno), txtfile);
        return -1;
    }
    FILE *fout = fopen(binfile, "wb");
    if (!fout) {
        printf("error %d : %s (open %s)\n", errno, strerror(errno), binfile);
        fclose(fin);
        return -2;
    }
    struct myrecord rec;
    int cnt = 0;
    while (fscanf(fin, "%lu %31s %f %f %f %d",
                  &rec.id, rec.name, &rec.score[0], &rec.score[1], &rec.score[2], &rec.weight) == 6) {
        printf("%lu %s %.2f %.2f %.2f %d\n",
               rec.id, rec.name, rec.score[0], rec.score[1], rec.score[2], rec.weight);
        if (fwrite(&rec, sizeof(rec), 1, fout) != 1) {
            printf("error %d : %s (write bin)\n", errno, strerror(errno));
            fclose(fin); fclose(fout);
            return -3;
        }
        cnt++;
    }
    fclose(fin);
    fclose(fout);
    printf("Total records written: %d\n", cnt);
    return cnt;
}

// 功能2：二进制->结构体->文本
int bin2txt(const char *binfile, const char *txtfile) {
    FILE *fin = fopen(binfile, "rb");
    if (!fin) {
        printf("error %d : %s (open %s)\n", errno, strerror(errno), binfile);
        return -1;
    }
    FILE *fout = fopen(txtfile, "w");
    if (!fout) {
        printf("error %d : %s (open %s)\n", errno, strerror(errno), txtfile);
        fclose(fin);
        return -2;
    }
    struct myrecord rec;
    int cnt = 0;
    while (fread(&rec, sizeof(rec), 1, fin) == 1) {
        printf("%lu %s %.2f %.2f %.2f %d\n",
               rec.id, rec.name, rec.score[0], rec.score[1], rec.score[2], rec.weight);
        fprintf(fout, "%lu %s %.2f %.2f %.2f %d\n",
                rec.id, rec.name, rec.score[0], rec.score[1], rec.score[2], rec.weight);
        cnt++;
    }
    fclose(fin);
    fclose(fout);
    printf("Total records read: %d\n", cnt);
    return cnt;
}