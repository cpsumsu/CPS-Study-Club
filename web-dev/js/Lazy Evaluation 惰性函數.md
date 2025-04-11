在前端開發中，我們經常會遇到瀏覽器兼容的問題。在一些老舊的瀏覽器（如IE6）中，特定的`javascript` API 並不兼容。在這種情況下，為了完成某種操作，我們需要不斷判斷該API是否存在，從而決定做不同的操作。

以下面的為例：`copy`函數用於複製一段文本到用戶的剪貼板。函數先判斷`navigator.clipboard` API是否存在（即是否兼容），如果存在則使用該API，如果不存在則用另外的方法。

```javascript
function copy(text) {
	if(navigator.clipboard){ // 判斷API是否存在
		navigator.clipboard.writeText(text);
	} else {
		const input = document.createElement("input");
		input.setAttribute("value", text);
		document.body.appendChild(input);
		input.select();
		document.execCommand("copy");
		document.body.removeChild(input);
	}
}
```

這種寫法雖然沒問題，但是會與實際需求有一定的出入。在API兼容性這個例子中，我們並非每次調用`copy`函數都需要判斷兼容性——我們只需要判斷一次兼容性即可！

根據這個理念，我們可以把代碼改成下面的樣子：

```javascript
function copy(text){
	if(navigator.clipboard){ // 判斷API是否存在
		copy = (text) => { // 根據條件覆蓋自身
			navigator.clipboard.writeText(text);
		}
	} else {
		copy = (text) => { // 根據條件覆蓋自身
			const input = document.createElement("input");
			input.setAttribute("value", text);
			document.body.appendChild(input);
			input.select();
			document.execCommand("copy");
			document.body.removeChild(input);
		}
	}
}
```

第一次調用的時候，`copy`會判斷API是否存在。判斷之後，`copy`會被覆蓋為不同情況下對應的函數。因此，第二次乃至後續調用`copy`函數時，都會是正確的函數。此外，在調用`copy`時，我們也省去了判斷的步驟，節省了性能。

實驗：

<img src="https://s2.loli.net/2025/04/11/KIrtCE75HXnAoFj.png" width="300px">

這就是惰性函數，即第一次調用的時候判斷條件並變更自身功能的函數。
