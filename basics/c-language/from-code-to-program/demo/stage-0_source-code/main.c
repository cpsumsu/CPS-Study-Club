// 宏替换
#define ONE 1
#define TWO 2
#define MAX(a, b) ((a > b) ? a : b)

// 文件展开
#include <stdio.h>
#include "addition.h"

// 条件编译
#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif

int main() {
    int a = ONE;
    int b = TWO;
    printf("1 + 2 = %d\n", add(a, b));
    printf("MAX(1, 2) = %d\n", MAX(a, b));

#ifdef __linux__
    printf("Compiling under linux/unix!\n");
    sleep(5);
#elif _WIN32
    printf("Compiling under windows!\n");
    Sleep(5);
#endif

    return 0;
}
