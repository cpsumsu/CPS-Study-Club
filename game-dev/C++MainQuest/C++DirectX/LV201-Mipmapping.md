# Mipmappping 

Mipmappping現在中文暫時沒有翻譯。

Mipmapping技術在1983年由Lance Williams 發明，在他的論文 Pyramidal parametrics 有描述

簡單來說，如果現在存在一個為256*256像素的圖片，則相關聯的 mipmap 鏈可能包含一系列 8 張圖像，每張圖像的總面積為前一張的四分之一：128×128 像素、64×64、32×32 , 16×16, 8×8, 4×4, 2×2, 1×1（單個像素）

例如，在一個場景中，彩現貼圖需要填滿的空間大小是40x40像素的話。

如果沒有三線性過濾，那32x32 會被放大顯示，或者有三線性過濾，會在64x64和32x32之間切換

![Mipmappping](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/MipMap_Example_STS101.jpg/330px-MipMap_Example_STS101.jpg)

# 應用場景:
仔細觀察這一系列圖片中是否存在奇怪的地方?
![](https://cdn.discordapp.com/attachments/1003320902731186196/1011490150557163601/unknown.png)
![](https://cdn.discordapp.com/attachments/1003320902731186196/1011490151303745617/unknown.png)
![](https://cdn.discordapp.com/attachments/1003320902731186196/1011490151643480134/unknown.png)
![](https://cdn.discordapp.com/attachments/1003320902731186196/1011490152088088607/unknown.png)

發現了嗎?這些黑白相間的距離變得越來越大了，這是因為我們採樣材質的過程中，由於我們離照片的距離越來越遠，採樣材質的間隔就會變得越來越大，同時紋理的大小是固定的，這以上的條件造成了很大的問題，此時，我們使用Mipmapping技術，生產一系列紋理圖像

# 簡單應用
```c++
Texture::Texture( Graphics& gfx,const std::string& path,UINT slot )
		:
		path( path ),
		slot( slot )
	{
		INFOMAN( gfx );

		// load surface
		const auto s = Surface::FromFile( path );
		hasAlpha = s.AlphaLoaded();

		// create texture resource
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = s.GetWidth();
		textureDesc.Height = s.GetHeight();
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = s.GetBufferPtr();
		sd.SysMemPitch = s.GetWidth() * sizeof( Surface::Color );
		wrl::ComPtr<ID3D11Texture2D> pTexture;
		GFX_THROW_INFO( GetDevice( gfx )->CreateTexture2D(
			&textureDesc,&sd,&pTexture
		) );

		// create the resource view on the texture
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = textureDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		GFX_THROW_INFO( GetDevice( gfx )->CreateShaderResourceView(
			pTexture.Get(),&srvDesc,&pTextureView
		) );
	}
```

更改 textureDesc 參數:
> textureDesc.MipLevels = 0;

> textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;

> textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

> srvDesc.Texture2D.MipLevels = -1;

最後使用 gpu 渲染管道生成 mip 鏈:
```c++
GetContext( gfx )->GenerateMips( pTextureView.Get() );
```

此時彈出一則錯誤，是位於D3D11_SUBRESOURCE_DATA *pInitialData，出現了null指針

問題發現於
> GFX_THROW_INFO( GetDevice( gfx )->CreateTexture2D(
			&textureDesc,&sd,&pTexture
		) );

```c++
HRESULT CreateTexture2D(
  [in]            const D3D11_TEXTURE2D_DESC   *pDesc,
  [in, optional]  const D3D11_SUBRESOURCE_DATA *pInitialData,
  [out, optional] ID3D11Texture2D              **ppTexture2D
);
```

檢查 D3D11_SUBRESOURCE_DATA *pInitialData 在Docs的說明如下:
> A pointer to an array of D3D11_SUBRESOURCE_DATA structures that describe subresources for the 2D texture resource. 

> Applications can't specify NULL for pInitialData when creating IMMUTABLE resources (see D3D11_USAGE)

問題解答已經很明顯了，刪去D3D11_SUBRESOURCE_DATA sd以及其資料，先傳入nullptr，再使用UpdateSubresource函數替代掉此操作

```c++
GFX_THROW_INFO( GetDevice( gfx )->CreateTexture2D(
			&textureDesc,nullptr,&pTexture
		) );
GetContext( gfx )->UpdateSubresource(
			pTexture.Get(),0u,nullptr,s.GetBufferPtrConst(),s.GetWidth() * sizeof( Surface::Color ),0u
		);
```

![finish](https://cdn.discordapp.com/attachments/1003320902731186196/1011980253226340452/unknown.png)
效果不錯!

寫一個測試函數用作計算miplevel
```c++
UINT Texture::CalculateNumberOfMipLevels( UINT width,UINT height ) noexcept
	{
		const float xSteps = std::ceil( log2( (float)width ) );
		const float ySteps = std::ceil( log2( (float)height ) );
		return (UINT)std::max( xSteps,ySteps );
	}
```

# 備忘錄

論文 Pyramidal parametrics by Lance Williams

https://web.archive.org/web/20140414134825/http://staff.cs.psu.ac.th/iew/cs344-481/p1-williams.pdf

ID3D11Device::CreateTexture2D 參數詳解

https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-createtexture2d

ID3D11DeviceContext::UpdateSubresource 參數詳解

https://docs.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-updatesubresource