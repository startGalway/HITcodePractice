#include <stdio.h>
#include <limits.h> // 用于INT_MAX定义

// 循环方式实现累加
int sum_iterative(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++) {
        s += i; // 此处可设置条件断点(i==50)
    }
    return s;
}

// 递归方式实现累加（AI辅助实现）
int sum_recursive(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n + sum_recursive(n - 1);
    }
}

// 计算溢出临界点
int find_overflow_point() {
    int sum = 0;
    int i = 1;
    while (sum <= INT_MAX - i) { // INT_MAX是int类型的最大值
        sum += i;
        i++;
    }
    return i - 1; // 返回最后一个不会导致溢出的i值
}

int main() {
    int n;
    printf("请输入一个正整数n: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("输入错误，请输入一个正整数。\n");
        return 1;
    }
    
    // 使用循环方式计算
    int result_iterative = sum_iterative(n);
    printf("循环方式计算结果: sum=%d\n", result_iterative);
    
    // 使用递归方式计算
    int result_recursive = sum_recursive(n);
    printf("递归方式计算结果: sum=%d\n", result_recursive);
    
    // 计算溢出点
    int overflow_point = find_overflow_point();
    printf("sum将超出int范围(INT_MAX=%d)时的i值: %d\n", INT_MAX, overflow_point);
    printf("此时sum值为: %d\n", sum_iterative(overflow_point));
    printf("下一个i值(%d)将导致溢出: %d\n", overflow_point + 1, sum_iterative(overflow_point + 1));
    
    return 0;
}