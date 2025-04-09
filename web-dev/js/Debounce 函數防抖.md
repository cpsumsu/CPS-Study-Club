
## What is Debounce? 什麼是函數防抖？

在JavaScript網頁開發中，我們會接觸到防抖的概念。它的產生源於這個需求：

> 用戶在點擊某個按鈕的時候，由於某些操作系統帶來的習慣，會連點三下。假設按鈕點擊的回調函數被設定為向服務器發出請求，則服務器一共會收到三次同樣的請求。但是實際上，只有最後一個請求是有用的。

通常來講，防抖適用於以下情況：

> 1. 函數在短時間內多次調用；
> 2. 只有最後一次調用被視為有效調用。
> 例如，用戶連續點擊三次上傳按鈕，只有最後一次被視為有效上傳，前兩次應當忽略。

防抖函數做的事情：

> 1. 首先，維護一個計時器ID。
> 2. 防抖函數調用的當下，函數會清空該計時器ID下的計時。
> 3. 防抖函數使用`setTimeout`方法，向瀏覽器計時器線程提交一個任務，並掛載到計時器ID上。
> 	- 假設該函數在規定時間內再次被調用，則**對應的**計時器任務會被清空，函數重新註冊給定的任務並設定觸發延遲。
> 	- 假設該函數在規定時間內未再被調用，則**對應的**計時器任務不會被清空，給定的任務在規定延遲後準時觸發，之後任務被移出隊列，調用完成。

若要防抖有效，找到對應的計時器至關重要。

代碼如下：

```javascript
let timer;
function debounce(){
	clearTimeout(timer);
	timer = setTimeout(
		()=>{
			console.log("do something");
		},    // 第一個參數：函數實際上要做的事情。
		1000  // 第二個參數：點擊過後等待多少毫秒
	);
}
```

實驗：

<img src="https://s2.loli.net/2025/04/10/XI6kCMq1nzHf3rB.png" width="300px">

## Encapsulation of Debounce 防抖函數的封裝

我們通常會把防抖函數封裝成一個高階函數。所謂高階函數，就是把“函數”作為入參的函數。

### 方法1：`debounce`作為函數立即執行

這種方法需要你將你要防抖的函數`foo`和其所需要的參數一併傳入`debounce`函數並執行。

```javascript
let timer;
function debounce(callback, delay, ...args){
	clearTimeout(timer);
	timer = setTimeout(
		() => {
			callback(...args); // ...args即為你定義的函數的入參。
		},
		delay
	);
}
```

調用方法如下：

```javascript
function foo(hungry, foolish){
	console.log(`stay ${hungry}, stay ${foolish}.`);
}

const hungry = "hungry";
const foolish = "foolish";
debounce(foo, delay, hungry, foolish); // 直接執行debounce函數
```

實驗：

<img src="https://s2.loli.net/2025/04/10/jU7idfZqv1pmgS9.png" width="300px">

### 方法2：執行`debounce`返回的防抖過的函數

這種方法只需要你將你要防抖的函數`foo`傳入`debounce`即可，不需要將`foo`的參數傳入`debounce`，因為`debounce`會返回一個新的函數供你執行。

```javascript
function debounce(callback, delay){
  let timer;  // timer放入函數內部作用域
  return function(...args) {
    clearTimeout(timer);
    timer = setTimeout(
        () => {
          callback(...args);
        },
        delay);
  }
}
```

調用方法如下：

```javascript
function foo(hungry, foolish){
	console.log(`stay ${hungry}, stay ${foolish}.`);
}

const hungry = "hungry";
const foolish = "foolish";

d_foo = debounce(foo, 1000); // 通過debounce獲取防抖過的函數
d_foo(hungry, foolish);      // 調用新返回的函數，而不是debounce本身
```

實驗：

<img src="https://s2.loli.net/2025/04/10/vU6m5QKIxc4hoyO.png" width="300px">

### 比較兩種方法

方法2優於方法1，因為方法2能夠把timer放到`debounce`內部的作用域中，從而每個防抖函數都能夠有自己的`timer`。反觀方法1，由於`timer`是全局變量，所有的`debounce`都要共用一個`timer`。

實際上，方法1中，如果將`timer`放入`debounce`函數中，防抖會失效。

實驗：

<img src="https://s2.loli.net/2025/04/10/YKn5QiTExL4wsPC.png" width="300px">

**為何會這樣呢？**

方法1中，頻繁調用目標防抖的函數**會**直接導致`debounce`函數被頻繁調用。換句話說，調用了多少次目標防抖的函數，就調用了多少次`debounce`。如果`let timer`語句直接放在`debounce`函數中的話，每次調用`debounce`該語句都會被執行一次，覆蓋掉上一次的值。因此，`debounce` 無法正確追蹤`timer`變量，防抖失效。於是，`timer`變量需要是一個全局變量。


方法2中，頻繁調用目標防抖的函數**不會**導致`debounce`函數被頻繁調用。我們只調用了一次`debounce`用來獲取防抖過後的函數，後續頻繁調用目標防抖的函數只會導致`debounce`函數返回出來的函數被頻繁調用，而`debounce`只在獲取該函數的時候被調用了一次。因此，`debounce`內部維護的`timer`變量不會被覆蓋，防抖有效。於是，`timer`變量不需要是一個全局變量。

### React中使用TypeScript封裝

在`React`中，防抖函數需要被封裝成一個`hook`。`hook`必須以`use`開頭。

```typescript
import {useCallback} from "react";
export function useDebounce<T extends (...args: any[]) => any>(
	fn: T, delay = 500  // T是一個泛型，指代“任何函數”。
) {

    let timer: ReturnType<typeof setTimeout>;  // 瀏覽器和Node環境可能有類型差異

    return useCallback(
	    function (
		    this: ThisParameterType<T>,  // 函數的this
		    ...args: Parameters<T>       // 入參
		    ) {
	        clearTimeout(timer);
	        timer = setTimeout(() => {
	            fn.apply(this, args);  // 這裡需要綁定fn的this指向。
        }, delay);
    }, []);

}
```

調用方法：

```typescript
function foo(hungry, foolish){
	console.log(`stay ${hungry}, stay ${foolish}.`);
}

const hungry = "hungry";
const foolish = "foolish";
const d_foo = useDebounce(foo, 500);

d_foo(hungry, foolish);
```

## 總結

函數防抖是一個防止頻繁無效操作的技巧。它能夠篩掉某段頻繁操作之中，最後一次操作前的所有操作，只保留最後一次操作。它能夠應用於服務器節流、前端佈局性能節省等場景。這些場景的共同點是：

> 1. 存在多次頻繁函數調用；
> 2. 只有最後一次調用被認為是有效的。

