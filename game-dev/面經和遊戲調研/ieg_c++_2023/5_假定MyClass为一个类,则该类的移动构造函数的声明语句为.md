# 假定MyClass为一个类,则该类的 __移动构造函数__ 的声明语句为
## __移动构造函数__

```c++
MyClass (MyClass x) // 1. 
MyClass (MyClass& x) // 2. 
MyClass& (MyClass& x) // 3. 
MyClass (MyClass&& x) // 4.
```

# 答案

<details>

```c++
MyClass (MyClass&& x) // 4.
```

移动构造函数是一种特殊的构造函数,它用来初始化一个对象,并从另一个对象"偷取"资源。
移动构造函数的标准声明格式如下:

```c++
MyClass(MyClass&& x)
```

其中 x 是右值引用类型 MyClass&&。

其他选项中的参数类型都是错误的:
1. 普通值传递会调用拷贝构造函数
2. 引用传递会调用拷贝构造函数
3. 返回引用类型不符合构造函数声明

所以移动构造函数的正确声明是选项4。

</details>
