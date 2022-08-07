## 支線任務1 i++和++i哪個快?

i++ : 後加
++i : 前加

你知道對於電腦來說，哪個更快嗎?

# 解答
在這兩個簡單函數中，寫出前加和後加的分別:
```
void fun_1()
{
    int i = 1;
    int a = ++i;
}

void fun_2()
{
    int i = 1;
    int a = i++;
}
```

而如果在編譯器的角度來看，它們的匯編指令為:
```
fun_1():
        push    rbp

        #(int i = 1;)
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 1 

        #(int a = ++i;)
        add     DWORD PTR [rbp-4],
        mov     eax, DWORD PTR [rbp-4]
        mov     DWORD PTR [rbp-8], eax

        nop
        pop     rbp
        ret
fun_2():
        push    rbp

        #(int i = 1;)
        mov     rbp, rsp 
        mov     DWORD PTR [rbp-4], 1

        #(int a = i++;)
        mov     eax, DWORD PTR [rbp-4]
        lea     edx, [rax+1]
        mov     DWORD PTR [rbp-4], edx
        mov     DWORD PTR [rbp-8], eax

        nop
        pop     rbp
        ret
```

如果不懂匯編代碼也沒有關係，只知道越少指令行效率越快就可以了(沒有循環的話)
注意到: fun_1 和 fun_2 之間的分別多了一行匯編碼
因此在對比++i和i++的效率的時候，我們可以說++i比i++更好

# 那多出來的匯編碼是甚麼?

1. 前加: 

``` add     DWORD PTR [rbp-4] ``` 很容易理解

2. 後加:

``` lea     edx, [rax+1] ``` 先實現自加1的運算，然後放在臨時變量edx中(1+1 = 2，現在edx中存放著2)

``` mov     DWORD PTR [rbp-4], edx``` 把臨時變量edx 拷貝複製給了變量i

# 即便多了一行匯編碼，這差距也很小不是嗎?
正確的，現代CPU一秒可以運行幾百萬行指令，這兩個幾乎沒有差別，你喜歡用哪個就用哪個