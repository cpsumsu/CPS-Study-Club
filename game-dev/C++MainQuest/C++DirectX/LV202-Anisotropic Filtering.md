# Anisotropic Filtering 各向異性過濾

如果順利完成上面的Mipmapping，你還需要對Sampler中的LOD(Level of Detail)參數進行設定才能使用

```c++
Sampler::Sampler( Graphics& gfx )
	{
		INFOMAN( gfx );

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		//added
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		GFX_THROW_INFO( GetDevice( gfx )->CreateSamplerState( &samplerDesc,&pSampler ) );
	}
```

預設:
> samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

濾波設定為取紋理上最近似的紋理單元顔色做為像素顔色

改良:
> samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;

![Anisotropic filtering](https://wikimedia.org/api/rest_v1/media/math/render/svg/cefc19220ffab8525959461b437c6d4050449b94)

各向異性過濾，主要是對于三維空間的立體貼圖有效果，防止貼圖畸變，效果很不錯，與雙線性過濾和三線性過濾相比，它在大角度顯示方面具有更高的精度，令畫面更逼真，但計算量也更大，對顯示卡的要求也更高。

不要忘記加上:
> samplerDesc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;

```c++
Sampler::Sampler( Graphics& gfx )
	{
		INFOMAN( gfx );

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		GFX_THROW_INFO( GetDevice( gfx )->CreateSamplerState( &samplerDesc,&pSampler ) );
	}
```

# 備忘錄

各向異性過濾wiki
https://zh.wikipedia.org/zh-tw/%E5%90%84%E5%90%91%E5%BC%82%E6%80%A7%E8%BF%87%E6%BB%A4