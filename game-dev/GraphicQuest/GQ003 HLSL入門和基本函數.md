# HLSL 入門和基本函數
什麼是HLSL？

高階著色器語言（High Level Shader Language，簡稱HLSL），就是用來編寫shader的一種語言

類似的語言還有：

## CG
它是由NVIDIA公司所開發的，基於C語言同時被OpenGL和Direct3D所支持的開發語言，其語法和HLSL類似。在《GPU編程與CG語言之陽春白雪》中雖然曾認為CG會越來越受歡迎，但遺憾的是，NVIDIA還是拋棄了CG，目前CG的最終版本是3.1。雖然在一些簡單的shader編寫上還是可以使用，但是在新的硬件環境下還是可能不支持，且對一些新功能的支持較差。

## GLSL
GLSL是基於OpenGL的接口，其語法體係自成一家。但是它不支持DirectX，就不得不放棄僅支持DirectX的Xbox等平台。

## HLSL
HLSL是由微軟開發的，在Windows平台上一家獨大，多用於遊戲領域。語法類似CG語言，在Unity中CG和HLSL等價。

# 常用函數分類
1. 基本數學運算
2. 冪指對函數
3. 數據範圍類
4. 類型判斷類
5. 三角函數與雙曲線函數
6. 向量與矩陣類
7. 光線運算類
8. 1D紋理查找
9. 2D紋理查找
10. 3D紋理查找
11. 立體紋理查找

# 基本數學運算
<details>
- max（a，b）	返回較大的
- min（a，b）	返回較小的
- mul（a，b）	兩向量相乘，常用於矩陣運算
- abs（a）	    返回a的絕對值
- round（x）	返回與x最近的整數
- sqrt（x）	    返回x的平方根
- rsqrt（x）	返回x的平方根的倒數
- degrees（x）	將弧度轉化為角度
- redians（x）	將角度轉化為弧度
- noise（x）	噪聲函數,在每個像素點上輸出0/1可形成噪波圖
</details>

# 冪指對函數
<details>

</details>

# 類型判斷類
<details>

</details>

# 三角函數與雙曲線函數
<details>

</details>

# 向量與矩陣類
<details>

</details>

# 光線運算類
<details>

</details>

# 1D紋理查找
<details>

</details>

# 2D紋理查找
<details>

</details>

# 3D紋理查找
<details>

</details>

# 立體紋理查找
<details>

</details>