# LV001-創建WinMain

# 環境設定

在VS 中創建新的專案，創建點選Window傳統應用程式

刪除所有在方案中的.cpp 和.h 示例代碼，創建一個新的WinMain.cpp文件

在組態(Configurations)中點選所有組態(All Configurations)

## C/C++
1. General 中 Milti-processor Compilation 多處理器編譯 點選 是
2. Preprocessor 中 Preprocessor Definition 增加 NDEBUG
3. Code Generation 中 Runtime Library 點選 /MT
4. Code Generation 中 Floating Point Model 點選 Fast
5. Language 中 C++ Language Standard 點選 /std:c++latest

## Linker 連結器
1. System 中 SubSystem 點選 Window

# WinMain?

用戶提供的基於 Windows 的圖形應用程序的入口點。

WinMain 是用於應用程序入口點的常規名稱。

The user-provided entry point for a graphical Windows-based application.

WinMain is the conventional name used for the application entry point. For more information, see Remarks.

window程序中包含了:
1. window: class, instance
2. message: ?

以下是示例代碼
```c++
#include <Windows.h>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	while (true)
	{
	}
	return 0;
}
```

# 備忘
https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
https://blog.csdn.net/yaked/article/details/52354921