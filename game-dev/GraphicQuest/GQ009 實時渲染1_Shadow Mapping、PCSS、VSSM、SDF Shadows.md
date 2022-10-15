# 實時渲染1 Shadow Mapping、PCSS、VSSM、SDF Shadows

## 1. Shadow Mapping (陰影映射)

## 1.1 陰影映射算法流程
Shadow Mapping 為圖像空間算法，用於快速判斷Shadow point 是否於陰影之中
- 好處: 不需要場景的幾何信息(只需屏幕信息)
- 壞處: 存在自遮擋和走樣的問題
陰影映射算法分成兩步: 
1. 以光源為視點，生成場景的深度圖(Shadow map)
2. 將著色點(Shadow point)到光源的距離和深度圖中的對應值作比較，判斷該點是否處位陰影之中

``` 
// Shadow Mapping 
// 計算有多少點不在陰影內 
int noShadowCount = 0;
// 深度圖中的對應值
float closestDepth = unpack(closestDepthVec);
// 著色點到光源距離
float currentDepth = coords.z;
if(currentDepth < closestDepth){
    noShadowCount += 1;
}
```
## 1.2 自遮擋問題
### 甚麼是自遮擋?

在第一步生成的深度圖中，深度變化差可能比較大，但深度圖分辨率不夠，所以在生成的深度圖採樣的深度有誤差

在第二步中，判斷這個著色點是否在陰影。

假設著色點在光源處上可以看見，但當計算著色點到光源距離時，會誤以為比從深度圖讀取的距離長( 著色點到光源距離 > 深度圖讀取的距離 )，算法會認為這個點位於陰影之中，以為著色點在光源處上看不見。

### 簡單的解決方法 偏倚 bias
加入額外的變量bias作比較

如果(著色點到光源距離 < 深度圖讀取的距離 + bias)，有多少點不在陰影內 

``` 
// Shadow Mapping 
// 計算有多少點不在陰影內 
int noShadowCount = 0;
// 深度圖中的對應值: closestDepthVec為深度圖
float closestDepth = unpack(closestDepthVec);
// 著色點到光源距離
float currentDepth = coords.z;
// 加入額外的變量作比較
if(currentDepth < closestDepth + 0.01){
    noShadowCount += 1;
}
```

## 1.3 走樣問題 Aliasing
生成的陰影可能會呈現階梯狀，仍然是深度圖分辨率不足的問題

## 2.1 PCF (Percentage Closer Filtering) 反走樣
改善剛剛提及的階梯狀陰影問題

## PCF流程

1. 對於某一個著色點p，先計算該點在場景中與光源的距離 

$$
D_{scene}(p)
$$

2. 取濾波卷積核w，根據卷積核的呎吋，以p點為中心，取深度圖中附近區域內保存的深度信息

$$
D_{SM}(q), q \in N(p)
$$

3. 計算可見性判斷，並得出結果

$$
X^+[D_SM(q) - d_{scene}(p)]
$$

4. 根據卷積核的權重w(p,q)，對結果進行加權平均，得到p點最終可見性結果

$$
V(p) = \sum_{q \in N(p)}{}w(p,q) * X^+[D_{SM}(q) - d_{scene}(p)] 
$$

$$
當中 X^ +(n) = 
\begin{aligned}
    1 & & ,{n > 0} \\
    0 & & ,{otherwise}
\end{aligned}

$$

$$
假設濾波卷積核w = \begin{bmatrix}
    1 & 0 & 1 \\
    1 & 0 & 0 \\
    1 & 1 & 1
\end{bmatrix}, 那麼它的均值濾波(取平均值)為0.6667
$$

```
// 採樣點數量
#define NUM_SAMPLES 20
vec2 poissonDisk[NUM_SAMPLES];
float PCF(sampler2D shadowMap, vec4 coords) 
{
  // 泊松分佈採樣
  poissonDiskSamples(coords.xy);
  //uniformDiskSamples(coords.xy);

  // shadow map 的大小, 越大滤波的范围越小
  float textureSize = 400.0;
  // 濾波的波長
  float filterStride = 5.0;
  // 濾波窗口的範圍
  float filterRange = 1.0 / textureSize * filterStride;
  // 計算有多少點不在陰影內
  int noShadowCount = 0;
  for( int i = 0; i < NUM_SAMPLES; i ++ ) {
    vec2 sampleCoord = poissonDisk[i] * filterRange + coords.xy;
    vec4 closestDepthVec = texture2D(shadowMap, sampleCoord); 
    float closestDepth = unpack(closestDepthVec);
    float currentDepth = coords.z;
    if(currentDepth < closestDepth + 0.01){
      noShadowCount += 1;
    }
  }
  // 根據卷積核的權重w(p,q)，對結果進行加權平均
  float shadow = float(noShadowCount) / float(NUM_SAMPLES);
  return shadow;
}
```

## 2.3 PCF 在 GAMES202 homework 1 的 實現過程
1. PhongMaterial.js的buildPhongMaterial()函數通過調用PhongMaterial
2. ShadowMaterial.js的buildShadowMaterial()函數通過調用ShadowMaterial
3. 在ShadowMaterial中進行CalcLightMVP()
4. 計算過後在loadOBJ中結合定義的transform和scale賦值傳入material
