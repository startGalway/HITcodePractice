#include <stdio.h>

int main() {
    // 初始化数据
    float floatArray[100];
    char charArray[100] = "This is a sample character array. It contains 100 characters to demonstrate the difference between binary and text file storage."; // 确保足够长

    // 为浮点数组赋值一些示例数据
    for (int i = 0; i < 100; i++) {
        floatArray[i] = i * 0.5f; // 示例值
    }

    // 1. 将浮点数组写入文本文件
    FILE *textFloatFile = fopen("floats_text.txt", "w");
    if (textFloatFile == NULL) {
        perror("Error opening text file for floats");
        return 1;
    }
    for (int i = 0; i < 100; i++) {
        fprintf(textFloatFile, "%f\n", floatArray[i]);
    }
    fclose(textFloatFile);

    // 2. 将浮点数组写入二进制文件
    FILE *binFloatFile = fopen("floats_binary.bin", "wb");
    if (binFloatFile == NULL) {
        perror("Error opening binary file for floats");
        return 1;
    }
    fwrite(floatArray, sizeof(float), 100, binFloatFile);
    fclose(binFloatFile);

    // 3. 将字符数组写入文本文件
    FILE *textCharFile = fopen("chars_text.txt", "w");
    if (textCharFile == NULL) {
        perror("Error opening text file for chars");
        return 1;
    }
    fprintf(textCharFile, "%s", charArray);
    fclose(textCharFile);

    // 4. 将字符数组写入二进制文件
    FILE *binCharFile = fopen("chars_binary.bin", "wb");
    if (binCharFile == NULL) {
        perror("Error opening binary file for chars");
        return 1;
    }
    fwrite(charArray, sizeof(char), 100, binCharFile);
    fclose(binCharFile);

    printf("文件写入完成！\n");
    return 0;
}