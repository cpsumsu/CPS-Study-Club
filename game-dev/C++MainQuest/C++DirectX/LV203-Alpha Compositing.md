# Alpha Compositing

Alpha compositing 是一種將圖像與背景結合的過程，結合後可以產生部分透明或全透明的視覺效果。Alpha合成也叫阿爾法合成或透明合成。

![Alpha Compositing](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2a/Alpha_compositing.svg/963px-Alpha_compositing.svg.png)

簡單來說就是去背

詳細的hlsl代碼
```hlsl
#include "ShaderOps.hlsli"
#include "LightVectorData.hlsli"

#include "PointLight.hlsli"

cbuffer ObjectCBuf
{
    bool normalMapEnabled;
    bool specularMapEnabled;
    bool hasGloss;
    float specularPowerConst;
    float3 specularColor;
    float specularMapWeight;
};

Texture2D tex;
Texture2D spec;
Texture2D nmap;

SamplerState splr;


float4 main(float3 viewFragPos : Position, float3 viewNormal : Normal, float3 viewTan : Tangent, float3 viewBitan : Bitangent, float2 tc : Texcoord) : SV_Target
{
    // normalize the mesh normal
    viewNormal = normalize(viewNormal);
    // replace normal with mapped if normal mapping enabled
    if (normalMapEnabled)
    {
        viewNormal = MapNormal(normalize(viewTan), normalize(viewBitan), viewNormal, tc, nmap, splr);
    }
	// fragment to light vector data
    const LightVectorData lv = CalculateLightVectorData(viewLightPos, viewFragPos);
    // specular parameter determination (mapped or uniform)
    float3 specularReflectionColor;
    float specularPower = specularPowerConst;
    if( specularMapEnabled )
    {
        const float4 specularSample = spec.Sample(splr, tc);
        specularReflectionColor = specularSample.rgb * specularMapWeight;
        if( hasGloss )
        {
            specularPower = pow(2.0f, specularSample.a * 13.0f);
        }
    }
    else
    {
        specularReflectionColor = specularColor;
    }
	// attenuation
    const float att = Attenuate(attConst, attLin, attQuad, lv.distToL);
	// diffuse light
    const float3 diffuse = Diffuse(diffuseColor, diffuseIntensity, att, lv.dirToL, viewNormal);
    // specular reflected
    const float3 specularReflected = Speculate(
        specularReflectionColor, 1.0f, viewNormal,
        lv.vToL, viewFragPos, att, specularPower
    );

    // edited

    // sample diffuse texture
    float4 dtex = tex.Sample(splr, tc);
	// final color = attenuate diffuse & ambient by diffuse texture color and add specular reflected

    return float4(saturate((diffuse + ambient) * dtex.rgb + specularReflected), dtex.a);
}
```

原有模型材質上的輸出流為:
```c++
bindablePtrs.push_back( Texture::Resolve( gfx,rootPath + texFileName.C_Str() ) );
```

新增為
```c++
auto tex = Texture::Resolve( gfx,rootPath + texFileName.C_Str() );
			hasAlphaDiffuse = tex->HasAlpha();
			bindablePtrs.push_back( std::move( tex ) );
```
> bool hasAlphaDiffuse = false;

記得所有材質皆需要統一blending mode
```c++
bindablePtrs.push_back( Blender::Resolve( gfx,hasAlphaDiffuse ) );
```

```c++
Blender::Blender( Graphics& gfx,bool blending )
		:
		blending( blending )
	{
		INFOMAN( gfx );

		D3D11_BLEND_DESC blendDesc = {};
		auto& brt = blendDesc.RenderTarget[0];
		if( blending )
		{
			brt.BlendEnable = TRUE;
			brt.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			brt.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			brt.BlendOp = D3D11_BLEND_OP_ADD;
			brt.SrcBlendAlpha = D3D11_BLEND_ZERO;
			brt.DestBlendAlpha = D3D11_BLEND_ZERO;
			brt.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			brt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		else
		{
			brt.BlendEnable = FALSE;
			brt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		GFX_THROW_INFO( GetDevice( gfx )->CreateBlendState( &blendDesc,&pBlender ) );
	}
```

```c++
std::shared_ptr<Blender> Blender::Resolve( Graphics& gfx,bool blending )
	{
		return Codex::Resolve<Blender>( gfx,blending );
	}
```

# 步驟

1. Texture image with alpha channel

2. Pixel shader that outputs alpha value

3. Output Merger set to build source with destination using the output alpha

# 備忘

Alpha合成

https://zh.wikipedia.org/zh-tw/Alpha%E5%90%88%E6%88%90