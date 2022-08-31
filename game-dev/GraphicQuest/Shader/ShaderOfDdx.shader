Shader "Custom/ShaderOfDdx"
{
    Properties
    {
        [KeywordEnum(IncreaseEdgeAdj, BrightEdgeAdj)] _EADJ("Edge Adj type", Float) = 0
        _Tex("Tex", 2D) = "white" {}
        _Intensity("Intensity", Range(0, 20)) = 2
    }
    SubShader
    {
        Pass
        {
            Tags { "RenderType"="Opaque" }
            Cull off
            Blend SrcAlpha OneMinusSrcAlpha

            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #pragma multi_compile _EADJ_INCREASEEDGEADJ _EADJ_BRIGHTEDGEADJ
            #include "UnityCG.cginc"
            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };
            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };
            sampler2D _Tex;
            float4 _Tex_ST;
            float _Intensity;
            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _Tex);
                return o;
            }
            fixed4 frag (v2f i, float f : VFACE) : SV_Target
            {
                fixed a = 1;
                if (f < 0) a = 0.5;
                fixed3 c = tex2D(_Tex, i.uv).rgb;
                #if _EADJ_INCREASEEDGEADJ // 邊緣調整：增加邊緣差異調整
                c += (ddx(c) + ddy(c)) * _Intensity;
                #else //_EADJ_BRIGHTEDGEADJ // 邊緣調整：增加邊緣亮度調整
                //c += abs(ddx(c)) + abs(ddy(c)) *_Intensity;
                c += fwidth(c) * _Intensity; // fwidth(c) ==> abs(ddx(c)) + abs(ddy(c))
                #endif // end _EADJ_INCREASEEDGEADJ
                return fixed4(c, a);
            }
            ENDCG
        }
    }
    FallBack "Diffuse"
}