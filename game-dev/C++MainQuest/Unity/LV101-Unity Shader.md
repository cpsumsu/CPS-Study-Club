# LV101-Unity Shader

以下為Unity Shader完整架構:

它們被分成了 Properties SubShader FallBack 三個部分

Unity開發者為了聲明這些以下的屬性，是為了在材質面板上能夠方便地調整各種材質的屬性

- Int (number) _Int("Int",Int)= 2
- Float (number) _Float("Float",Float) = 1.5
- _Color ("Color", Color) = (1,1,1,1)
- _MainTex ("Albedo (RGB)", 2D) = "white" {}
- _Glossiness ("Smoothness", Range(0,1)) = 0.5
- _Metallic ("Metallic", Range(0,1)) = 0.0
...

不用背，會用就行

在D3D10中新增了新的語義類型 (System-value semantics)

- 這些語義通常以SV為開頭
- 當我們使用 SV_POSITION 去修飾頂點著色器的時候，就表示了pos包含了...

<details>
```
Shader "Custom/NewSurfaceShader"
{
    Properties
    {}
    SubShader
    {}
    FallBack "Diffuse"
}
```

```shaderlab
Shader "Custom/NewSurfaceShader"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", Range(0,1)) = 0.0
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        sampler2D _MainTex;

        struct Input
        {
            float2 uv_MainTex;
        };

        half _Glossiness;
        half _Metallic;
        fixed4 _Color;

        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            // Albedo comes from a texture tinted by color
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
            o.Albedo = c.rgb;
            // Metallic and smoothness come from slider variables
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Alpha = c.a;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
```



# 頂點/片元著色器(Vertex/Fragment Shader)
頂點/片元著色器更加複雜，但也更加靈活

<details>
```
Shader "Custom/NewSurfaceShader"
{
    Properties
    {
        _Color("Color Tint", Color) = (1,1,1,1)
    }
    SubShader
    {
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
    
            uniform fixed4 _Color;

            struct a2v
            {
                float4 vvertex : POSITION;
                float3 normal : NORMAL;
                float4 texcood : TEXCOORD;
            };
            struct v2f
            {
                float4 pos : SV_POSITION;
                float3 ccolor : COLOR;
            };

            v2f vert(a2v v)
            {
                v2f o;
                o.pos = UnityObjectToClipPos(v.vvertex);
                o.ccolor = v.normal * 0.5 + fixed3(0.5,0.5,0.5);
                return o;
            }
            

            fixed4 frag(v2f i) : SV_Target
            {
                fixed3 c = i.ccolor;
                c *= _Color.rgb;
                return fixed4(c,1.0);
            }

            ENDCG
            
        }
    }
    FallBack "Diffuse"
}
```