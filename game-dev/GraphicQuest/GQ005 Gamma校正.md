# Gamma校正

![](pic/螢幕擷取畫面%202022-09-11%20095751.png)

Gamma校正所解決的問題和場景:
* (Gamma校正)[https://www.bilibili.com/video/BV15t411Y7cf/?spm_id_from=autoNext&vd_source=c8f797eb0ed2b9ae031c806a2b48a232]

# 甚麼是Gamma校正
灰階分成兩種: 

- 非線性灰階（視覺上看著均勻變化的）

- 一種是物理/線性灰階（物理上均勻變化的）。

Gamma校正就是把兩者聯繫起來的函數，用來做兩者的轉換。

![](pic/Gamma.png)

# 為什麼要Gamma校正
1. 人眼對於灰色的變化更敏感
2. 早期顯示器(CRT)發展需要節能

# 嘗試在unity 色彩空間使用Gamma校正
![](pic/螢幕擷取畫面%202022-09-11%20103521.png)

![](pic/螢幕擷取畫面%202022-09-11%20103457.png)

