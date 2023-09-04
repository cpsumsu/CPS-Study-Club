# 假定arr是一个数组，以下C++代码的目的是什么

```c++
[arr](){return 0;}()[arr];
```

1. 返回数组arr的拷贝
2. 返回数组arr的第1个元素
3. 语法错误，会编译失败
4. 创建并返回一个空数组arr

# 答案

<details>

2. 返回数组arr的第1个元素

```c++
#include <iostream>
#include <vector>
using namespace std;

void arr(int arr[])
{
    // 1
    auto b = [arr]() {return 0; }()[arr]; // 返回 arr首地址0的元素

    auto c = [arr]()->int {return 0; }; // std::function 返回0
    auto d = [arr]() -> int* {
        int* arr = new int[10]; // 分配10个元素的int数组
        return arr; // 返回数组指针
    }(); // 立即执行lambda表达式
    auto e = [arr]() -> std::vector<int> { // 返回std::vector来避免手动内存管理:
        return std::vector<int>(10);
    }();
    auto copy = [arr]() -> int* { // 拷贝数组
        int* copy = new int[10];
        for (int i = 0; i < 10; i++) {
            copy[i] = arr[i];
        }
        return copy;
    }();
    cout << b << endl;
    cout << c() << endl;
}

int main()
{
    int a[100] = { 99,98,97 };
    arr(a);
    return 0;
}
```

</details>