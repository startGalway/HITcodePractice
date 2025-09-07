#ifndef FILEOP_H
#define FILEOP_H

#include <stdio.h>

struct myrecord {
    unsigned long id;  // 
    char name[32];  //32
    float score[3];  //12
    int weight;  //4
};

// 功能1：从文本文件读取数据，输出到屏幕，并写入二进制文件
int txt2bin(const char *txtfile, const char *binfile);

// 功能2：从二进制文件读取数据，输出到屏幕，并写入文本文件
int bin2txt(const char *binfile, const char *txtfile);

#endif // FILEOP_H