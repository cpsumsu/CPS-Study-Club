# 延遲渲染 Deferred Rendering
## 1.1 甚麼是延遲渲染？
>　A single rendering pass could generate a color image in one target, object identifiers in another, and world-space distances in a third. This ability has also given rise to a different type of rendering pipeline, called Deferred shading, where visibility and shading are done in separate passes

甚麼是延遲渲染？為什麼要延遲渲染？

假設一個場景中，有10000個Mesh需要渲染，有100個Light，
```c++
// 示例
int main()
{
    for (int i = 0; i < 10000;++i)
    {
        for (int j = 0; j < 100;++j)
        {
            RenderMesh(Mesh,Light)
        }
    }
}

void RenderMesh(int Mesh,int Light)
{
    for (int i = 0; i < Mesh * 3;++i)
    {
        RenderTriange(Light);
    }
}
```
在一個正常的場景，涉及的Mesh可能有上百萬個，如果此時我們還想要去渲染100個Light互相影響的結構，不就相當於把這幾百萬個Mesh再重新渲染100次？就算是RTX4090也hold不住

所以延遲渲染的做法就是先做深度測試(Depth Test)，再做渲染

## 1.2 延遲渲染的過程
1. Geometry Pass(幾何處理階段): 
   - 正常的渲染過程，只是我們不做光照處理。我們把場景中各種幾何信息暫存起來，我們叫這個暫存的地方叫 G-buffer
   - G-buffer放甚麼幾何信息?你可以放:
     - Position (像素位置)
     - Normals (光線)
     - Diffuse Albedo RGB (漫反射)
     - Spec-Power (高光反射)
     - Spec-Intersity
     - ...

![](pic/367b8335a4aa1ffa2d1718506cd6f0e7.jpg)

2. Lighting Pass(光照處理階段):
   1. 

