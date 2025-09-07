#include <stdio.h>
#include <stdlib.h>
#include "fileop.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage:\n");
        printf("  %s 1 <input_txt> <output_bin>\n", argv[0]);
        printf("  %s 2 <input_bin> <output_txt>\n", argv[0]);
        return 1;
    }
    int mode = atoi(argv[1]);
    if (mode == 1) {
        // 文本->二进制
        return txt2bin(argv[2], argv[3]);
    } else if (mode == 2) {
        // 二进制->文本
        return bin2txt(argv[2], argv[3]);
    } else {
        printf("Invalid mode: %s\n", argv[1]);
        return 2;
    }
}
