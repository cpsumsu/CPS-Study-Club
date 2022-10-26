# C/C++ 的分別?
> 關於C同C++，我呢兩個地方都唔明，有冇啲通俗啲嘅版本？

C++ 比起 C 多左 classes、templates、exceptions

更多的特性可以參考[這裡](https://www.cnblogs.com/miloyip/archive/2010/09/17/behind_cplusplus.html)

在VS2019中，C/C++平台就是以C++為主的編程語言

# C++學習建議?
> Milo的游戏开发
C++缺點之一，是相對許多語言複雜，而且難學難精。許多人說學習C語言只需一本K&R《C程序設計語言》即可，但C++書籍卻是多不勝數。我是從C進入C++，皆是靠閱讀自學。在此分享一點學習心得。個人認為，學習C++可分為4個層次：

1. 第一層次，C++基礎：挑選一本入門書籍，如《C++ Primer》、《C++大學教程》、或Stroustrup撰寫的經典《C++程序設計語言》或他一年半前的新作《C++程序設計原理與實踐》，而一般C++課程也止於此，另外《C++ 標準程序庫》及《The C++ Standard Library Extensions》可供參考；
2. 第二層次，正確高效地使用C++：此層次開始必須自修，閱讀過《(More)Effective C++》、《(More)Exceptional C++》、《Effective STL》及《C++編程規範》等，才適宜踏入專業C++開發之路；
3. 第三層次，深入了解C++：關於全局問題可讀《深入探索C++對像模型》、《Imperfect C++》、《C++沉思錄》、《STL源碼剖析》，要挑戰智商，可看關於模版及模版元編程的書籍如《C++ Templates》、《C++設計新思維》、《C++模版元編程》；
4. 第四層次，研究C++：閱讀《C++語言的設計和演化》、《編程的本質》(含STL設計背後的數學根基)、C++標准文件《ISO/IEC 14882:2003》、C++標準委員會的提案書和報告書、關於C++的學術文獻。

# 甚麼是pointer?
pointer 相對應就係 address，用address代表該object的值 

```c++
#include <iostream>
 
using namespace std;
 
int main ()
{
   int  var1;
   char var2[10];
 
   cout << "var1 address： ";
   cout << &var1 << endl;
 
   cout << "var2 address： ";
   cout << &var2 << endl;
 
   return 0;
}
```

[推薦讀物](https://kopu.chat/c%E8%AA%9E%E8%A8%80-%E8%B6%85%E5%A5%BD%E6%87%82%E7%9A%84%E6%8C%87%E6%A8%99%EF%BC%8C%E5%88%9D%E5%AD%B8%E8%80%85%E8%AB%8B%E9%80%B2%EF%BD%9E/)

# 甚麼是structure?
> 只有變數？
C/C++ 結構是 C++ 中另一種用戶自定義的可用的數據類型，它允許您存儲不同類型的數據項。

```c++
struct A
{
    int a = 10;
    int b = 114514;
    string c = "114515aabbcc";
};
```
