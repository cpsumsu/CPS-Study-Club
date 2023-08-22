# C++11/14 feature 

## Author: awepo-pro

2011 年，c++ 發表的新特性比 1989 多出 80%，新的特性不單提高語言的性能和自由度，也漸逐地將c++轉化為"安全"的語言。

這個 repository 主要講解 c++11/14 feature and concept!

MaxOS 用戶可用 g++/gcc 編譯：

```md
// 這裏用了g++
g++ -std=c++11 <file_name.cpp>
./a.out
```

## [lvalue和rvalue](./lvalue%20and%20rvalue.cpp)
- lvalue指的是在內存中具有持久地址的對象。
- rvalue指的是在內存中沒有持久地址的臨時對象。
- 代碼示例使用lvalue和rvalue的示例。
- 理解C++表達式和引用時，lvalue和rvalue的區別非常重要。

## [模板中數組的最佳匹配](./best%20matches%20for%20array%20in%20template.cpp)
- C++模板中數組的最佳匹配類型。
- print函數被重載以處理不同類型的數組。
- 最佳匹配類型的優先級由const的存在和數組的類型決定。
- 提供了不同數組類型及其對應的最佳匹配類型的示例。

## [C++中的函數式編程](./functional.cpp)
- C++中函數式編程特性的使用。
- 具有相同調用簽名的函數可以使用std::function統一。
- lambda表達式、函數對象和標準函數對象的使用。
- hash映射將不同的函數存儲為值，並可用於執行各種操作。

# C++ 完美轉發: Universal Reference
## [forward_and_move.h](./universal%20reference/forward_and_move.h)
- 定義了 po_move 和 po_forward 函數，用於實現 C++ 中的移動語義和完美轉發。
- po_move 函數使用 remove_reference 來確保返回的是右值引用。
- po_forward 函數使用 remove_reference 和 static_cast 來實現完美轉發。

## [reference_collapse.cpp](./universal%20reference/reference%20collapse.cpp)
- 引用折疊(reference collapsing)的概念。
- 在 wrapper 函數中，使用 std::forward 來實現完美轉發。
- fun 函數被重載以處理不同類型的引用。

## [rvalue_reference_parameter.cpp](./universal%20reference/rvalue%20reference%20parameter.cpp)
- 右值引用參數的使用。
- 在 f 函數中，使用 std::forward 來實現完美轉發。
- g 函數不同引用類型的特性。

# C++ 模板（部分特化）和特化: specialization
## [specialization.cpp](./template%20(partial%20specialization)/specialization.cpp)
- C++中模板的特化和部分特化的用法。
- 通過重載和特化，可以根據不同的類型進行不同的處理。
- 定義了幾個模板函數和特化函數，用於打印不同類型的數組。
- 通過特化，可以對const char*類型的數組進行特殊處理。

## [patial specialization priority.cpp](./template%20(partial%20specialization)/patial%20specialization%20priority.cpp)
- 特化的優先級。
- 特化的優先級高於部分特化，因為特化更加明確。
- 通過特化，可以對不同引用類型進行不同的處理。

## [remove_reference.h](./template%20(partial%20specialization)/specialization.cp/remove_reference.h)
- 部分特化和一般特化的實現方式。
- 通過部分特化和一般特化，可以根據不同的引用類型進行不同的處理。
- 定義了一個模板結構po_remove_reference和幾個特化版本，用於去除引用類型。
- 特化和部分特化之間的優先級。




