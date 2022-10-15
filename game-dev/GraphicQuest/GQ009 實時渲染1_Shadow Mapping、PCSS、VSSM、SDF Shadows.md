# 實時渲染1 Shadow Mapping、PCSS、VSSM、SDF Shadows

## 1. Shadow Mapping (陰影映射)

## 1.1 陰影映射算法流程
Shadow Mapping 為圖像空間算法，用於快速判斷Shadow point 是否於陰影之中
- 好處: 不需要場景的幾何信息(只需屏幕信息)
- 壞處: 存在自遮擋和走樣的問題
陰影映射算法分成兩步: 
1. 以光源為視點，生成場景的深度圖(Shadow map)
2. 將Shadow point到光源的距離和深度圖中的對應值作比較，判斷該點是否處位陰影之中
## 1.2 自遮擋問題
### 甚麼是自遮擋?

在第一步生成的深度圖中，深度變化差可能比較大，但深度圖分辨率不夠，所以在生成的深度圖採樣的深度有誤差

在第二步中，判斷這個Shawdor point 是否在陰影時，雖然Shader point在光源處

### 