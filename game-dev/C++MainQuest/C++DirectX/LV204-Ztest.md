# ZTest

使用上個章節的代碼可能會出現穿模的情況

![穿模](https://cdn.discordapp.com/attachments/1003320902731186196/1007847319045144667/unknown.png)

使用ZTest確保幾何體的正確排序，通過改變深度測試的條件，您可以實現物體遮擋等視覺效果。

刪除上次原有的統一材質輸出
```c++
bindablePtrs.push_back( Blender::Resolve( gfx,hasAlphaDiffuse ) );
```

新增 alpha test
```hlsl  
    float4 dtex = tex.Sample(splr, tc);
    clip(dtex.a < 0.1f ? -1 : 1);
```

用於移除樹葉中透明的地方

# 解答

# 備忘

clip
https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-clip