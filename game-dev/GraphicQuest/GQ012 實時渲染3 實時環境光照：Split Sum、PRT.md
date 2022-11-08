# 實時環境光照：環境光照與預計算 環境光與Split Sum
環境映射 Environment Mapping

在《Real-Time Rendering 3rd》第八章 : Area and Environmental Lighting 中，介紹了 Environment Mapping (環境映射)

Environment mapping（環境映射），又稱Reflection Mapping（反射映射）,是計算機圖形學領域中使用基於圖像的光照（Image-Based Lighting，IBL）技術，用預先計算的紋理圖像模擬複雜鏡面的一種高效方法。

環境映射將周圍環境與光照通過直接投影而簡化表示為紋理，保存的環境光照在繪製時假設來自無窮遠處，得到的環境光照圖常是球體圖（spherical map）或立方體圖（cube map）。

![](https://pic4.zhimg.com/v2-b5aee79979012a34e485bafb8b6f7ac7_r.jpg)

由於是事先準備好的數據，這種實現方法比傳統的光線跟踪算法效率更高，但是需要注意的是這種方法是實際反射的一種近似，有時甚至是非常粗糙的近似。這種技術的一個典型的缺點是沒有考慮自反射，即無法看到物體反射的物體自身的某一部分。

# Signed Distance Function (SDF)
- Distance Function: 就是空間中任何一點，到某個物體的最小距離
- Signed: 就是加入規定負數代表在物體內部，正數則表示在物體外部。這樣不止定義了距離，還定義了方向

## SDF 的應用
1. Ray Marching
   - 以迭代方式遍歷射線，從而將每條射線有效地劃分為較小的射線段，並在每個步驟中對某些函數進行採樣  
2. 生成軟陰影

# Split Sum
- 放棄原渲染方程的visibility項
- 著色點的lighting項就變成了環境光的lighting
