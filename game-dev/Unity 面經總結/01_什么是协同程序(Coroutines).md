# 什么是协同程序(Coroutines)

协同程序(Coroutines)是unity中的一种特殊方法，用于实现异步方法和延迟执行方法。

协同程序的主要特征是:

1. 可以暂停和恢复执行
2. 可以等待下一帧继续执行
3. 可以在yield return null;语句处暂停执行，并在下一次Resume()调用时继续执行

协同程序的基本结构是:

```csharp
IEnumerator DoSomething()
{
    // 执行一段代码
    yield return null;  // 暂停执行，返回执行协同程序的对象
    
    // ...
    yield return null;
    
    // ...
}
```
使用协同程序的步骤:
1. 定义一个IEnumerator接口的方法，此方法为协同程序方法
2. 在方法体中使用yield return语句暂停执行
3. 调用StartCoroutine()启动协同程序
4. 协同程序会在遇到yield return语句时暂停，并返回一个IEnumerator对象
5. 下次调用枚举器的MoveNext()方法时，会从上次暂停的地方继续执行
例如:
```csharp
IEnumerator FadeIn()
{
    float alpha = 0;
    float increment = 0.1f;
    
    while (alpha < 1) {
        alpha += increment;
        Color c = sprite.color;
        c.a = alpha;
        sprite.color = c;
        
        yield return null;  // 暂停并等待下一帧
    }
}

// 调用
StartCoroutine(FadeIn());
```
这个协同程序会逐渐增加一个精灵的alpha值，实现淡入效果，并在每一帧暂停等待继续执行。