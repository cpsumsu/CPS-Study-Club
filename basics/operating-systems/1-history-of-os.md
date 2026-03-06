
# 1.1 批處理系統 Batch Systems (1955-1965)

這個時代，計算機還使用點卡編程。所謂“操作系統”做以下事情：

1. Read: 讀取卡帶的第一個任務。
2. Run: 運行該任務。
3. Write: 將輸出寫入另一個卡帶。
4. 返回第1步，直到沒有更多任務。

批處理系統有以下問題：

- Bad Responsiveness 響應能力差：假設程序末尾出現異常，需要等待程序跑完才能發現。
- Bad Concurrency 不可同步使用：用戶必須一個一個等待使用。
- Bad Efficiency 效率低下：在做I/O（即Input, Output）時，計算單元是空閒的。

Multiprogramming: 我們渴望一個能在同時間內完成多個任務的系統。

# 1.2 MULTICS

MULTICS 即 Multiplexed Information and Computing Service，多路信息和計算服務。由麻省理工貝爾實驗室（Bell Labs, MIT）和通用電氣（General Electric）合力打造。

- 支持上百個用戶同時使用。
- UNIX的前身。

<img src="https://upload.wikimedia.org/wikipedia/commons/d/d6/Multics-Login.png" width="400px">

# 1.3 UNIX (1971)

UNIX 即 Uniplexed Information and Computing Service，單工信息和計算服務。由Ken Thompson 與 Dennis Ritchie 與貝爾實驗室編寫。Ken因MULTICS項目被砍他想繼續玩他在MULTICS上編寫的太空遊戲，他一怒之下就寫了一個操作系統，即UNIX。

Unix最初運行在貝爾實驗室的PDP-11計算機上。1973年，Ritchie發明了C語言以輔助Unix的開發。

<img src="https://upload.wikimedia.org/wikipedia/commons/8/8a/Simh-pdp11-unix-sysiii.png" width="400px">

## 伯克利軟件套件 BSD

伯克利軟件套件 Berkeley Software Distribution，是一個衍生自Unix的操作系統，即“類Unix”操作系統，由伯克利加州大學的學生Bill Joy 開創。

 許多操作系統的內核都由BSD的影子，如Sun公司的 SunOS 和 DEC 的 Ultrix。此外，蘋果 (Apple Computer.Inc) 於2000年推出的開源操作系統DarwinOS（現今macOS和iOS的內核）採用的XNU混合內核也包含BSD元素。因此，這些都是類”Unix“操作系統。

# 1.4 Linux (1991)

赫爾辛基大學的大學生 Linus Torvalds 想要學習操作系統，但是當時UNIX已被商業化且閉源（即源代碼不對外公開）。因此，Linus決定親自寫一個操作系統並將其開源。

> Linux源碼：https://github.com/torvalds/linux
> 
> Linux社區開發文檔：https://www.kernel.org/doc/html/latest/

<img src="https://images.steamusercontent.com/ugc/2040739975502125035/E69DDD0360D7AEECA55156D5B5FAD509198D3F0C/?imw=637&imh=358&ima=fit&impolicy=Letterbox&imcolor=%23000000&letterbox=true" width="300px">

> 對Nvidia豎起中指的Linus Torvalds ;)

~~*Linux是一個梗很多的操作系統（誤*~~

而今，Linux操作系統核心被廣泛使用。最為主要的就是Linux發行版：

- Ubuntu：面向桌面和服務器，對用戶友好，社區活躍；
- CentOS：面向服務器，穩定性好，廣泛用於生產環境；
- Debian：注重穩定性和安全性，適合服務器和嵌入式設備；
- Arch Linux：面向愛折騰的用戶，高度可定製，滾動更新；
- ......

Linux發行版之外，我們常見的安卓操作系統 (Android) 也是基於Linux開發的，也是一個開源其核心操作系統。Android系統的核心是AOSP，即Android Open Source Project。


<div>
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/35/Tux.svg/1012px-Tux.svg.png" height="150px">
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/ae/Ubuntu_24.10_Oracular_Oriole_Desktop_English.png/1600px-Ubuntu_24.10_Oracular_Oriole_Desktop_English.png" height="150px">
<img src="https://i.ytimg.com/vi/-hlRB2izres/maxresdefault.jpg" height="150px">
</div>

> 圖1：Linux的吉祥物，是一只叫Tux的企鵝。*“企鹅就该有点呆萌、有点诙谐，这才是Linux该有的样子。”*
> 
> 圖2：Ubuntu的用戶界面。
> 
> 圖3：YouTuber [@LinusTechTips](https://www.youtube.com/@LinusTechTips) 體驗純AOSP原生安卓的[視頻](https://www.youtube.com/watch?v=-hlRB2izres)。

# 1.5 PC-era (1980-今)

IBM 於1981年推出 PC，即 Personal Computer。其使用新的 Intel 的處理器，需要一個操作系統。

- PC/M 操作系統
- MS-DOS，Microsoft Disk Operating System

## 圖形用戶界面GUI

操作系統最初的用戶界面是簡單的命令行界面 Command-line Interface.

施樂公司 Xerox-PARC (台灣稱全錄) 打造了第一個圖形界面的操作系統。

- Steve Jobs 參觀了施樂公司後把圖形界面用在了新的 1983 年的 Apple Lisa 電腦和 1984 年的Macintosh電腦 (即如今的Mac)。
- Microsoft與 1985 年推出 Microsoft Windows。