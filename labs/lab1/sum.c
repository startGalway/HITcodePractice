#include <stdio.h>

int main() {
    int n, i, s = 0; // 初始化总和s为0

    printf("请输入一个正整数n: ");
    scanf("%d", &n); // 从键盘读取用户输入的n[1,2,3,6](@ref)

    // 使用for循环计算1到n的和
    for (i = 0; i < n; ++i) 
    {
        s += i; // 将当前的i累加到总和s中
    }

    printf("sum=%d\n", s); // 输出计算结果[1,2,3](@ref)
    return 0;
}