# D3D11_SAMPLER_DESC Filter 紋理濾波設定

```c++
Sampler::Sampler( Graphics& gfx )
	{
		INFOMAN( gfx );

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
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

預設:
> samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

濾波設定為取紋理上最近似的紋理單元顔色做為像素顔色

改良:
> samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;

各向異性的濾波方式主要是對于三維空間的立體貼圖有效果，防止貼圖畸變，效果很不錯