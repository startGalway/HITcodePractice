#include <stdio.h>
#include <stdlib.h> // 用于 exit 函数

int main() {
    FILE *file;
    float floatArray[100]; // 存储读取的100个浮点数
    size_t elementsRead;

    // 1. 打开二进制文件
    file = fopen("floats_binary.bin", "rb"); // "rb" 表示以二进制只读模式打开
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // 2. 读取数据
    elementsRead = fread(floatArray, sizeof(float), 100, file);
    // 此处返回值elementsRead表示实际读取到的元素个数。
    // 3. 检查读取是否成功
    if (elementsRead != 100) {
        if (feof(file)) {
            printf("Error: End of file reached prematurely. Only read %zu elements.\n", elementsRead);
        } else if (ferror(file)) {
            perror("Error reading from file");
        }
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // 4. 关闭文件
    if (fclose(file) != 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    // 5. 处理或使用数据 (此处示例为打印前5个和后5个)
    printf("Successfully read 100 float values:\n");
    for (int i = 0; i < 100; i++) {
        printf("floatArray[%d] = %.2f\n", i, floatArray[i]);
    }
    // printf("...\n");
    // for (int i = 95; i < 100; i++) {
    //     printf("floatArray[%d] = %.2f\n", i, floatArray[i]);
    // }

    return 0;
}