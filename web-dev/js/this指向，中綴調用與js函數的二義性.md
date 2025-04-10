> 本文整理自菜鳥、稀土掘金、知乎上的文章。

## `this`的指向

`this`指向是使用`javascript`時老生常談的問題。可以知道的是：

> 1. `this`存在於“執行上下文”。
> 2. `this`的指向只取決於函數的調用方式，它與函數的聲明無關。

```javascript
function foo(){
	console.log(this); // 在這個函數調用之前，我們並不知道this指向什麼。
}
```

不同調用方法下，`this`的指向不同。總的來說，`this`的值是在**非箭頭函數**中，由函數調用表達式的**左側對象**所決定。

### 直接調用

直接調用函數，`this`指向全局對象。
1. 瀏覽器環境下，`this`指向`window`對象；
2. Node環境下，`this`指向全局對象`global`；
3. 嚴格模式下，`this`指向`undefined`。

```javascript
function foo(){
	console.log(this);
}

foo(); // 此時函數左側什麼也沒有，故而指向全局對象。
```

實驗1：瀏覽器環境下，直接調用函數。

<img src="https://s2.loli.net/2025/04/10/SPG2scLyr6kRZAK.png" width="600px">

實驗2：`Node`環境下，直接調用函數。

<img src="https://s2.loli.net/2025/04/10/7xSPnI3WytdpwBA.png" width="400px">

實驗3：嚴格模式下，直接調用函數。

<img src="https://s2.loli.net/2025/04/10/zgeQKqkCT6lsPRc.png" width="400px">

### 通過對象調用

透過對象調用函數，則返回“上一個對象”。

假設`fn`是對象`obj`的一個鍵，其對應的值是`foo`函數，那麼透過`obj`調用`foo`函數的方法為`obj.fn()`，如下：

```javascript
function foo(){
	console.log(this);
}

obj.foo(); // 此時函數的左側為obj，故而this指向obj
```

實驗：

<img src="https://s2.loli.net/2025/04/10/Z4In2rBlVv9RPja.png" width="300px">

在此實驗中，`obj_out`為一個對象，其內部有一屬性也是一個對象，叫`obj_in`。 兩個對象內部都有一個`fn`方法，對應外層定義的`foo`函數。

- 調用`obj_out.fn()`，可以看到打印出的`this`為`obj_out`；
- 調用`obj_in.fn()`，可以看到打印出的`this`為`obj_in`。

對比實驗：在不同地方調用函數的區別。

<img src="https://s2.loli.net/2025/04/10/lV6hDRfI74vX8Mp.png" width="150px">

### 透過`call`、`apply`、`bind`調用

`call`、`apply`和`bine`這三個函數都是用來改變`this`指向的。函數透過這三個方法調用，`this`指向第一個參數。

#### `call` 方法

該方法的第一個參數就是你所需要設置的`this`指向，剩餘參數則是你函數定義的參數。

```javascript
function foo(msg){
	console.log(msg);
	console.log(this);
}

var obj = {
	hello: "world",
	how: "are you"
}

foo.call(obj, "This指向為") // 函數this指向為obj
```

實驗：

<img src="https://s2.loli.net/2025/04/10/CKbY7ceXdvMl6zP.png" width="300px">

如圖所示，`this`指向已成功被修改為目標對象。

#### `apply` 方法

`apply` 方法的以數組的形式入參，其餘與`call`一致。

```javascript
function foo(msg){
	console.log(msg);
	console.log(this);
}

var obj = {
	hello: "world",
	how: "are you"
}

foo.apply(obj, ["This 指向為"]) // 函數this指向為obj
```

實驗：

<img src="https://s2.loli.net/2025/04/10/hktnUYFXrvM3WyV.png" width="300px">

#### `bind` 方法

`bind`方法會創建一個新的函數，叫做綁定函數。調用綁定函數時，`this`指向為原函數`bind`方法時的第一個參數。

```javascript
function foo(msg){
	console.log(msg);
	console.log(this);
}

var obj = {
	hello: "world",
	how: "are you"
}

const bar = foo.bind(obj, msg) 
bar(); // 函數this指向為obj
```

實驗：

<img src="https://s2.loli.net/2025/04/10/GqWX9pwjg1rd7Of.png" width="250px">

## this指向與中綴調用

> 以下文字整理自[@谷雨同学](https://www.zhihu.com/people/guyutongxue)的[知乎文章](https://www.zhihu.com/question/654178975/answer/3480674806?utm_psn=1893529309966233856)。

在C語言中，要想進行類似的面向對象操作，需要這樣：

```c
typedef struct {
	char* name;
	int age;
} Student;

void grow_up(Student *student, int age){
	student->age = age;
}

int main(){
	Student* s = malloc(sizeof(Student));
	s->name = "Huang";
	s->age = 21;
	grow_up(s, 22);  // 非常不直觀
}
```

在這裡，更新“對象”內部屬性的閱讀順序是“操作-對象-值”，即`foo(obj, value)`，並不直觀。因此，面向對象語言的操作均采用中綴調用的形式，即`obj.foo(value)`。這種調用形式的閱讀順序是“對象-操作-值”，更加直觀。

中綴調用衍生的新問題是，我們如何去訪問`obj`呢？在C語言中，`obj`作為入參可以直接被訪問；但是在中綴調用中，`obj`不再是入參了，因此我們需要一個特定關鍵詞來訪問這個對象。這就是許多編程語言中的所謂`this`或者`self`的來歷，它們本質上是中綴調用的產物，**是一個特殊的形參**。

```cpp
class Foo
{
public:
    Foo() {}
    void print_this()
    {
        Foo this_obj = *this;
    }
};

int main()
{
    Foo *foo = new Foo();
    foo->print_this();
}
```

JS與其他面向對象的語言的區別是，其他語言對象內部的函數必須通過中綴調用來實現，而JS沒有這個限制。

```cpp
foo->print_this(); // 中綴調用，this為左側對象
print_this();      // 報錯，找不到該方法，自然也不會有this問題
```

```javascript
function print_this(){
	console.log(this);
}

var foo = {
	print_this: print_this
}

foo.print_this(); // 中綴調用，this為左側對象
print_this();     // 完全可以！那麼this到底是啥呢~
```

## js函數的二義性

### 什麼是二義性

`javascript`的函數具有二義性，即具有兩層含義。

> 1. 含義1：它可以作為一個執行流程；
> 2. 含義2：它也可以作為一個創建對象的構造函數。

以`Date`函數為例，既可以直接作為函數調用，又可以使用`new`語句作為構造函數來調用。

```javascript
let date = Date();  // 返回一個值
let new_date = new Date(); // 返回一個對象
```

實驗：

<img src="https://s2.loli.net/2025/04/10/yX7PVjzBsW5bQrH.png" width="400px">

### 二義性的解決

為了消除函數的二義性，ES6標準引入`class`，`new.target`和箭頭函數。

#### `class` 定義構造函數

由`class`來定義的函數只能作為構造函數使用，即其只能通過`new`來調用，強行調用會報錯。

```javascript
class Fn{  // 雖然它看上去不像是函數，但它仍然是函數，而不是類

}
Fn(); // 報錯
new Fn(); // 不報錯
```

實驗：

<img src="https://s2.loli.net/2025/04/10/8Z1epLWPQ2RaIDr.png" width="500px">

#### `new.target` 用於給普通函數去調節造函數的性質

若直接執行，`new.target`為`undefined`；若使用`new`調用，則`new.target`為函數對象。因此，我們可以透過`new.target`來改造普通函數，用於約束它“必須用作構造函數”或“不可用作構造函數”。

```javascript
function foo(){
	if(new.target){
		// fn()，無值，為undefined
		// new fn()，有值，為 foo {}
		throw new Error("不可透過new調用。");
	}
	console.log("執行");
}
fn(); // 執行
new fn(); // 報錯
```

實驗：

<img src="https://s2.loli.net/2025/04/10/JsAu2VeFDrKWjMg.png" width="300px">

#### 箭頭函數定義執行單元

箭頭函數，即立即執行函數，為最純粹的執行單元，不可以用來當做構造函數使用。

```javascript
const foo = () => {
	console.log(this);
}

foo(); // 執行
new foo(); // 報錯
```

實驗：

<img src="https://s2.loli.net/2025/04/10/dMqXDIxNnyhlc4J.png" >

### 立即執行函數的`this`指向問題

普通函數的`this`指向是動態綁定的，但是箭頭函數並沒有`this`，其`this`在定義時繼承自外部的執行上下文。

```javascript
const obj = {
	foo: function(){
		console.log(this);
	},
	bar: () => {
		console.log(this);
	}
}
```

實驗：

<img src="https://s2.loli.net/2025/04/10/OaJ6uhSe9iZL7NX.png" width="300px">

## 參考文獻

> 1. https://www.runoob.com/js/js-this.html
> 2. https://juejin.cn/post/7075603057924374541
> 3. https://www.zhihu.com/question/654178975/answer/3480674806?utm_psn=1893529309966233856