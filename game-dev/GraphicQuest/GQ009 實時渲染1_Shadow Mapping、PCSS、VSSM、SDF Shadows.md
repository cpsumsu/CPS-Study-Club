# 實時渲染1 Shadow Mapping、PCSS、VSSM、SDF Shadows、VSM、MSM

## 1. Shadow Mapping (陰影映射)

## 1.1 陰影映射算法流程
Shadow Mapping 為圖像空間算法，用於快速判斷Shadow point 是否於陰影之中
- 好處: 不需要場景的幾何信息(只需屏幕信息)
- 壞處: 存在自遮擋和走樣的問題
陰影映射算法分成兩步: 
1. 以光源為視點，生成場景的深度圖(Shadow map)
2. 將著色點(Shadow point)到光源的距離和深度圖中的對應值作比較，判斷該點是否處位陰影之中

![](pic/ShaderMap.png)

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
## 甚麼是自遮擋?

在第一步生成的深度圖中，深度變化差可能比較大，但深度圖分辨率不夠，所以在生成的深度圖採樣的深度有誤差

在第二步中，假設著色點在光源處上可以看見，但當計算著色點到光源距離時，會誤以為比從深度圖讀取的距離長( 著色點到光源距離 > 深度圖讀取的距離 )，算法會認為這個點位於陰影之中，以為著色點在光源處上看不見。

![](pic/自遮擋.png)

## 簡單的解決方法 偏倚 bias
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

![](pic/biasimport.png)

## 1.3 走樣問題 Aliasing
生成的陰影可能會呈現階梯狀，仍然是深度圖分辨率不足的問題
![](pic/bias.png)

## 2.1 PCF (Percentage Closer Filtering) 反走樣
改善剛剛提及的階梯狀陰影問題

## PCF流程

1. 對於某一個著色點p，先計算該點在場景中與光源的距離 $D_{scene}(p)$

1. 取濾波卷積核w，根據卷積核的呎吋，以p點為中心，取深度圖中附近區域內保存的深度信息 $D_{SM}(q), q \in N(p)$

3. 計算可見性判斷，並得出結果 $X^+[D_SM(q) - d_{scene}(p)]$

4. 根據卷積核的權重w(p,q)，對結果進行加權平均，得到p點最終可見性結果 

$$
V(p) = \sum_{q \in N(p)}w(p,q) * X^{+}[D_{SM}(q) - d_{scene}(p)]
$$

$$
X^{+}(n) = 
\begin{aligned}
    1 & & n > 0 \\
    0 & & n<=0
\end{aligned}
$$

假設已得到濾波卷積核w，那麼它的均值濾波(取平均值)為0.6667

$$
w = \begin{bmatrix}
    1 & 0 & 1 \\
    1 & 0 & 0 \\
    1 & 1 & 1
\end{bmatrix}, 6 / 9 = 0.6667
$$

## 2.2 PCF 在 GAMES202 homework 1 的 實現過程
1. 需要完善 phongFragment.glsl 中的 PCF(sampler2D shadowMap, vec4
shadowCoord, float filterSize) 函数。我们推荐在一个圆盘滤波核中进行随机采样，采用这种方案的原因是可以简化后续PCSS Shader 的编写同时可以使软阴影上模糊的部分更显圆润自然，计算出来的伴影直径可与单位圆盘上的采样点相乘生成 ShadowMap 上的采样坐标
2. （值得注意的是随机采样函数的质量将与最终渲染效果的好坏息息相关，我们在框架中提供了泊松圆盘采样和均匀圆盘采样两种采样函数，替换使用对比一下两种采样函数的细微区别，我们也鼓励使用其他的采样方法）。

```
// 採樣點數量
#define NUM_SAMPLES 20
vec2 poissonDisk[NUM_SAMPLES];
float PCF(sampler2D shadowMap, vec4 coords) 
{
  // 泊松分佈採樣 （Poisson-Disk Sample）
  // 圓範圍內隨機取一系列坐標作為採樣點，但是這些坐標還需要滿足一定約束，即坐標與坐標之間至少有一定距離間隔
  poissonDiskSamples(coords.xy);
  // 均勻圓盤分佈採樣（Uniform-Disk Sample）
  // 圓範圍內隨機取一系列坐標作為採樣點；看上去比較雜亂無章，採樣效果的 noise 比較嚴重。
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
    // 簡單理解
    // float closestDepth = unpack(texture2D(shadowMap,coords.xy+disk[i]*0.001).rgba);
    if(currentDepth < closestDepth + 0.01){
      noShadowCount += 1;
    }
  }
  // 根據卷積核的權重w(p,q)，對結果進行加權平均
  float shadow = float(noShadowCount) / float(NUM_SAMPLES);
  return shadow;
}
```

效果圖
![](pic/pcf.png)

## LightMVP 使用

<details>

1. PhongMaterial.js的buildPhongMaterial()函數通過調用PhongMaterial
2. ShadowMaterial.js的buildShadowMaterial()函數通過調用ShadowMaterial
3. 在ShadowMaterial中進行CalcLightMVP()
4. 計算過後在loadOBJ中結合定義的transform和scale賦值傳入material
   
</details>

# 3.1 Soft Shadow
當面光源照射物體時，會在物體後面產生軟陰影（soft shadow）。軟陰影邊緣的柔和程度不固定，會隨著遮擋程度的變化而變化。

雖然上一節介紹的 PCF 技術可以使陰影的邊緣變得柔和，但是單純地使用 PCF 並不能得到軟陰影，因為 PCF 濾波卷積核的尺寸固定，於是得到的陰影邊緣柔和程度也是固定的。

要想得到軟陰影，可以在 PCF 的基礎上進一步發展，根據遮擋程度的變化而動態調整濾波卷積核的尺寸，使陰影邊緣的柔和程度隨著遮擋程度的變化而變化。
# 4.1 PCSS
PCSS（Percentage Closer Soft Shadows）是一種在 PCF 的基礎上得到的軟陰影生成技術，它根據著色點和光源之間遮擋物的相對平均深度來判斷著色點的被遮擋程度，依此選擇合適的 PCF 濾波卷積核尺寸，使得陰影邊緣的柔和程度隨著遮擋程度的變化而變化。

![PCSS 示意](pic/pcss.png)
PCSS 算法可分為三步：

1. 遮擋物搜索（blocker search）： 在深度圖上計算著色點附近給定區域的平均遮擋物深度 $d_{blocker}$ ； 這個搜索遮擋物區域的範圍可以是恆定的，例如固定為 $5*5$ ， 也可以使用啟發法（heuristics），根據光源的尺寸 $w_{light}$ 和著色點與光源之間的距離 $d_{receiver}$  確定搜索遮擋物區域的範圍；
2. 半影估計（penumbra estimation）： 假設光源、遮擋物和著色點所在表面相互平行，根據光源的尺寸 $w_{light}$ ，著色點與光源之間的距離 $d_{receiver}$ 和平均遮擋物深度$d_{blocker}$ 估計陰影在著色點處的柔和程度 $w_{penumbra} = \frac{d_{receiver} - d_{blocker}}{d_{blocker}}$ ；
3. PCF：執行 PCF 算法，而 PCF 卷積核的尺寸和半影估計 $w_{penumbra}$ 成正比；
   
# 4.2 PCSS 在 GAMES202 homework 1 的 實現過程
1. 需要完善 phongFragment.glsl 中的 findBlocker(sampler2D shadowMap,vec2 uv, float zReceiver)。findBlocker 函数中需要完成对遮挡物平均深度的计算。
2. 需要完善 phongFragment.glsl 中的 PCSS(sampler2D shadowMap, vec4 shadowCoord) 函数

詳細在 GAMES202 homework 1 的 實現過程
<details>

findBlocker(sampler2D shadowMap,vec2 uv, float zReceiver)函數實現
```
float findBlocker( sampler2D shadowMap,  vec2 uv, float zReceiver ) {
  int blockerNum = 0;
  float block_depth = 0.;
  float shadowmapSize = 2048.;
  float Stride = 50.;

  poissonDiskSamples(uv);
  
  for (int i = 0; i < NUM_SAMPLES;++i)
  {
    vec4 shadow_color = 
      texture2D(shadowMap,uv + poissonDisk[i] * Stride / shadowmapSize);
    float shadow_depth = unpack(shadow_color);
    if (zReceiver > shadow_depth + 0.01)
    {
      blockerNum++;
      block_depth += shadow_depth;
    }
  }
  if (blockerNum == 0)
    return 1.;
  return float(block_depth) / float(blockerNum);
}
```

</details>


# 5.1 VSSM
PCSS 算法的第一步為了估計著色點平均遮擋物深度 $z_{occ}$ ，需要讀取深度圖中該點附近所有紋元（texel）保存的深度，並與著色點的深度進行比較，求取那些比著色點深度更小的紋元深度的平均值，而在第三步為了得到平均可見性結果，也要再次重複這個統計過程。

VSSM（Variance Soft Shadow Mapping） 近似了這個統計過程，大大加速了 PCSS 第一步和第三步的估計。加速的統計過程可簡單地分為如下兩步：

計算著色點附近深度分佈的均值和方差；
借助不等式估計該點附近未遮擋物的平均深度 $z_{occ}$ 或該點的可見性判斷結果 $V(p)$ ；

# 5.1.1 計算深度分佈的均值和方差
隨機變量 $X$ 的數學期望 $E(X)$ 和方差 $Var(X)$ 存在如下關係：

$$
(1): Var(X) = E(X^2) - E^2(X) 
$$

只需記錄下隨機變量 $X$ 的數學期望 $E(X)$ 和 2階原點矩 $E(X^2)$ ，便能得到隨機變量所服從概率分佈的均值和方差。於是，在生成深度圖時，不僅記錄場景的深度 $z$ ，也額外記錄場景深度的平方 $z^2$ ，然後計算各自的 SAT（summed area table）。(類似前綴和)

指定著色點附近區域的查詢範圍後，根據深度 SAT 和深度平方 SAT，可以快速地獲取著色點附近深度的平均值 $(z^2)_{arg}$ 和深度平方的平均值 $(z_{arg})^2$ ，分別作為深度分佈的均值和  階原點矩，並根據公式(1) 得到了深度分佈的方差 $(z^2)_{arg}-(z_{arg})^2$

# 5.1.2 通過不等式估計未遮擋物的平均深度或著色點的可見性判斷結果
切比雪夫不等式（Chebychev’s inequality）刻畫了概率分佈的概率密度函數，均值和方差之間的關係，其內容如下：

$$
P(x > t) \leq \frac{\sigma^2}{\sigma^2 + (t - \mu)^2}
$$

將著色點 $p$ 的深度記作 $z_t$ ，則 $P(x > t)$ 即是該著色點附近區域內，未被遮擋的紋元在所有紋元中所佔的比例。

VSSM 直接<u>假設切比雪夫不等式中等號成立</u>：

$$
P(z > z_t) = \frac{(z^2)_{arg}-(z_{arg})^2}{(z^2)_{arg}-(z_{arg})^2 + (z_{t}-z_{arg})^2}
$$

如果此時對應於 PCSS 的第三步，則便直接得到了著色點 $p$ 的最終可見性判斷結果 $V(p) = P(z > z_t)$ 。

如果此時對應於 PCSS 的第一步，則繼續假設未遮擋物的平均深度等於著色點的深度 $z_{unocc} = z_t$ ，並將著色點附近的遮擋物平均深度記作 $z_{}$ ，未遮擋物平均深度記作 ，於是存在如下關係：

$$
[1-P(z>z_t)] * z_{occ} + P(z > z_t) * z_{unocc} = z_{avg}
$$

代入相應的數值，便可以估計出遮擋物的平均深度 $z_{occ}$ 以用於 PCSS 第二步估計半影。

# 6 Moment Shadow Mapping (MSM)
VSSM 使用<a>切比雪夫不等式</a>估計著色點附近深度分佈的累積概率函數，進而計算該點附近未被遮擋的紋元占所有紋元的比例。此時，累計概率函數的重建僅用到了均值和  階原點矩。 Moment Shadow Mapping 在其基礎上對重建步驟作了改進，在重建累計概率函數時用到了更高階的原點矩，得到了更準確的擬合。

因為考慮了深度的更高階項，所以消耗了更多的存放空間，重建時也消耗了更多的資源，但是的確緩解了 VSSM 生成陰影時的漏光等現象。

# 7 Distance Field Soft Shadows
和 PCSS 系列技術不同，distance field soft shadows 依靠有向距離場而不是陰影圖來生成軟陰影。

有向距離場（signed distance field，SDF）  保存了三維場景中任一點與距離它最近的景物表面之間的距離。如果該點在景物內部，則距離是負數，否則是正數。

從著色點  發射一根指向光源的光線，在光線傳播的過程中記錄當前點 $p$ 的有向距離場數值 $sdf(p)$ 和當前點到著色點之間的距離，計算相應的角度，並記錄下光線傳播過程中最小的那個角度 $\theta$ ，則這個角度代表了從著色點從該方向向光源望去時未被其它物體遮擋的“安全”視角。

這個“安全”角越小，則著色點被其它物體遮擋的程度越大，於是可以根據“安全“角的大小調整陰影的柔和程度，由此得到軟陰影。

通常， ”安全“角  的計算並非直接求取反三角函數，而是使用如下公式以減少計算耗費：

$$
\theta = min\big({\frac{k * sdf(p)}{||p - o||},1}\big)
$$

參數 $k$ 控制了陰影邊緣的柔和程度， $k$ 越大，則陰影的邊緣則越柔和。

Distance Field Soft Shadows 可以生成相對高質量的軟陰影，並且速度較快，但是還是存在走樣問題，而且有向距離場需要預計算並存儲場景中每個三維點的深度信息，和 PCSS 系列技術相比消耗了更多的存儲空間，因為後者在生成深度圖時只需要計算並存儲光源處的深度信息即可。

為了避免生成有向距離場時需要計算場景中每個三維點的信息，一些研究提出可以使用八叉樹之類的層次化數據結構細分場景。對於場景中那些遠離任何景物表面的區域，細分的層級可以粗糙一些，如此便減少了資源耗費。

# 參考資料
* 有向距離場（Signed Distance Field）（SDF）:
* [虚幻引擎网格体距离场 | 虚幻引擎5.0文档 (unrealengine.com)](https://docs.unrealengine.com/5.0/zh-CN/mesh-distance-fields-in-unreal-engine/)

