# Push前請看
一般情況為你本地的倉庫與遠端倉庫同步了(全部文件都是一致的)，然後你提交(commit)再去上傳(push)。
但是如果本地的倉庫與遠端的倉庫不同步了？這個時候你上傳到遠端倉庫git就會報錯，並表示遠端的倉庫與你本地的倉庫並不同步，所以不能上傳到遠端倉庫。

---

## 良好的習慣 / 解決方法
### `pull` - 下載與合併
> pull = fetch and merge

每次在提交或上傳前，把遠端倉庫下載和合併到本地倉庫以避免發生不同步衝突。

```console
git pull origin main
```
<img width="626" alt="git pull" src="https://user-images.githubusercontent.com/82365010/182049854-914d723e-8709-4a59-9939-e239a549ef76.png">

有更新的時候就會顯示出下載的大小與什麼檔案有改變。沒有更新的話則會顯示 `Already up to date`.

---

## 其他方法
### `fetch` - 獲取
把遠端倉庫獲取到本地倉庫。獲取並不沒有把遠端倉庫下載(同步)到本地的倉庫，只是讓你可以了解本地倉庫與遠端倉庫有什麼變動。
> 把遠端倉庫全部的分支都獲取到本地倉庫
```console
git fetch
# or
git fetch orign
```
> 把遠端倉庫的分支 `branch_name` 獲取到本地倉庫
```console
git fetch origin <branch_name>
```

<img width="620" alt="Screenshot 2022-08-01 at 12 17 40 AM" src="https://user-images.githubusercontent.com/82365010/182049282-6ca6356c-b98a-48f3-8d0b-3695c700424c.png">

我們可以用 `git status` 來查看遠端跟本地的分別。

當遠端倉庫有相較本地更新版本的時候，我們就可以把它合併到本地。

```console
git merge master/main
```

這也是`git pull origin main`在背後做的事情。

---



