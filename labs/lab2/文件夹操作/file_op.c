#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_PATH_LEN 1024
#define MAX_FILES 1024

// 文件信息结构体
typedef struct {
    char filename[MAX_PATH_LEN];
    long size;
    long offset;
} FileInfo;

// 包文件头结构
typedef struct {
    int file_count;
    char signature[8];
} PackageHeader;

// 递归获取文件夹下所有文件
int list_files(const char *path, FileInfo files[], int *count) {
    DIR *dir;
    struct dirent *entry;
    struct stat stat_buf;
    char full_path[MAX_PATH_LEN];
    
    if ((dir = opendir(path)) == NULL) {
        perror("opendir failed");
        return -1;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        // 跳过 "." 和 ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // 构建完整路径
        snprintf(full_path, MAX_PATH_LEN, "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &stat_buf) == -1) {
            perror("stat failed");
            continue;
        }
        
        if (S_ISREG(stat_buf.st_mode)) {  // 常规文件
            if (*count >= MAX_FILES) {
                printf("文件数量超过限制\n");
                closedir(dir);
                return -1;
            }
            
            strcpy(files[*count].filename, full_path);
            files[*count].size = stat_buf.st_size;
            (*count)++;
        } else if (S_ISDIR(stat_buf.st_mode)) {  // 目录，递归处理
            if (list_files(full_path, files, count) == -1) {
                closedir(dir);
                return -1;
            }
        }
    }
    
    closedir(dir);
    return 0;
}

// 打印文件列表
void print_file_list(FileInfo files[], int count) {
    printf("找到 %d 个文件:\n", count);
    printf("%-40s %s\n", "文件名", "大小");
    printf("---------------------------------------- ----------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-40s %10ld bytes\n", files[i].filename, files[i].size);
    }
}

// 打包文件夹
int package_files(const char *dir_path, const char *package_name) {
    FileInfo files[MAX_FILES];
    int file_count = 0;
    FILE *package_fp;
    PackageHeader header;
    long header_size;
    long current_offset;
    
    // 获取文件列表
    if (list_files(dir_path, files, &file_count) == -1) {
        return -1;
    }
    
    printf("正在打包 %d 个文件...\n", file_count);
    
    // 创建包文件
    if ((package_fp = fopen(package_name, "wb")) == NULL) {
        perror("创建包文件失败");
        return -1;
    }
    
    // 写入包文件头（预留位置，后面再填充）
    strcpy(header.signature, "MYPACK");
    header.file_count = file_count;
    header_size = sizeof(PackageHeader) + sizeof(FileInfo) * file_count;
    current_offset = header_size;
    
    fwrite(&header, sizeof(PackageHeader), 1, package_fp);
    for (int i = 0; i < file_count; i++) {
        files[i].offset = current_offset;
        fwrite(&files[i], sizeof(FileInfo), 1, package_fp);
        current_offset += files[i].size;
    }
    
    // 写入文件内容
    for (int i = 0; i < file_count; i++) {
        FILE *src_fp;
        char buffer[4096];
        size_t bytes_read;
        
        if ((src_fp = fopen(files[i].filename, "rb")) == NULL) {
            perror("打开源文件失败");
            fclose(package_fp);
            return -1;
        }
        
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_fp)) > 0) {
            fwrite(buffer, 1, bytes_read, package_fp);
        }
        
        fclose(src_fp);
        printf("已打包: %s\n", files[i].filename);
    }
    
    // 更新文件头
    rewind(package_fp);
    fwrite(&header, sizeof(PackageHeader), 1, package_fp);
    for (int i = 0; i < file_count; i++) {
        fwrite(&files[i], sizeof(FileInfo), 1, package_fp);
    }
    
    fclose(package_fp);
    printf("打包完成! 包文件: %s\n", package_name);
    return 0;
}

// 解包文件
int unpack_files(const char *package_name, const char *output_dir) {
    FILE *package_fp;
    PackageHeader header;
    FileInfo files[MAX_FILES];
    char output_path[MAX_PATH_LEN];
    
    if ((package_fp = fopen(package_name, "rb")) == NULL) {
        perror("打开包文件失败");
        return -1;
    }
    
    // 读取文件头
    fread(&header, sizeof(PackageHeader), 1, package_fp);
    if (strcmp(header.signature, "MYPACK") != 0) {
        printf("无效的包文件格式\n");
        fclose(package_fp);
        return -1;
    }
    
    if (header.file_count > MAX_FILES) {
        printf("包文件中文件数量超过限制\n");
        fclose(package_fp);
        return -1;
    }
    
    // 读取文件信息
    for (int i = 0; i < header.file_count; i++) {
        fread(&files[i], sizeof(FileInfo), 1, package_fp);
    }
    
    printf("开始解包 %d 个文件...\n", header.file_count);
    
    // 提取文件
    for (int i = 0; i < header.file_count; i++) {
        FILE *dest_fp;
        char buffer[4096];
        long remaining;
        size_t to_read;
        
        // 创建输出路径
        snprintf(output_path, MAX_PATH_LEN, "%s/%s", output_dir, files[i].filename);
        
        // 创建目录（如果需要）
        char *dir_sep = strrchr(output_path, '/');
        if (dir_sep != NULL) {
            *dir_sep = '\0';
            mkdir(output_path, 0777);
            *dir_sep = '/';
        }
        
        if ((dest_fp = fopen(output_path, "wb")) == NULL) {
            perror("创建目标文件失败");
            fclose(package_fp);
            return -1;
        }
        
        // 定位到文件数据开始位置
        fseek(package_fp, files[i].offset, SEEK_SET);
        
        // 复制文件内容
        remaining = files[i].size;
        while (remaining > 0) {
            to_read = sizeof(buffer) < remaining ? sizeof(buffer) : remaining;
            fread(buffer, 1, to_read, package_fp);
            fwrite(buffer, 1, to_read, dest_fp);
            remaining -= to_read;
        }
        
        fclose(dest_fp);
        printf("已解包: %s\n", output_path);
    }
    
    fclose(package_fp);
    printf("解包完成! 文件输出到: %s\n", output_dir);
    return 0;
}

// 显示使用说明
void print_usage(const char *program_name) {
    printf("使用说明:\n");
    printf("  %s list <目录路径>        - 列出目录下的所有文件\n", program_name);
    printf("  %s pack <目录路径> <包文件> - 打包目录到包文件\n", program_name);
    printf("  %s unpack <包文件> <输出目录> - 从包文件解包\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "list") == 0) {
        if (argc != 3) {
            printf("错误: 需要指定目录路径\n");
            print_usage(argv[0]);
            return 1;
        }
        
        FileInfo files[MAX_FILES];
        int file_count = 0;
        
        if (list_files(argv[2], files, &file_count) == 0) {
            print_file_list(files, file_count);
        }
    } else if (strcmp(argv[1], "pack") == 0) {
        if (argc != 4) {
            printf("错误: 需要指定目录路径和包文件名\n");
            print_usage(argv[0]);
            return 1;
        }
        
        package_files(argv[2], argv[3]);
    } else if (strcmp(argv[1], "unpack") == 0) {
        if (argc != 4) {
            printf("错误: 需要指定包文件名和输出目录\n");
            print_usage(argv[0]);
            return 1;
        }
        
        unpack_files(argv[2], argv[3]);
    } else {
        printf("错误: 未知命令 '%s'\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }
    
    return 0;
}