# [不定项]
# 已知int aa=10;以下表示引用的方法中,正确的是

```c++
int&& bb = 10; //1.
int& bb = aa * 10; //2.
int&& bb = aa; //3.
int& bb = aa; //4.
```

# 答案

<details>

```c++
#include <iostream>
using namespace std;

int main()
{
	int aa = 10;
	int&& bb = 10; //1.
	int& bb = aa * 10; //ERROR C++ 非常數參考的初始值必須是左值
	int&& bb = aa; //ERROR C++ 右值參考無法繫結至左值
	int& bb = aa; //4.
}

```

</details>