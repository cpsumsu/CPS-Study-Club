## 前言

> 我們所有的夢想都可以真的，只要我們有勇氣去追求它們（All our dreams can come true, if we have the courage to pursue them）。 
> ———— 華特·迪士尼

# 遊戲編程筆記
個人學習遊戲編程，收錄於CPSStudyClub，以後可能再整理一下倉庫內的目錄

## ——⚠️施工中的文章⚠️——
- 美術篇
  - 模型基礎和設計
- 計算機圖形學筆記
  - 深度與模板測試
- 計算機圖形學筆記 - 實時渲染篇 
  - 實時渲染4 3D空間GI的LPV算法和VXGI算法 SSAO算法
  - 實時渲染5 高級著色 BRDF及相關技術
- C++ 雜項 筆記
  - 速通LeetCode水題一百道
- 面經
  - 主要內容為網上收集的各大面經、考試、測試題信息雜項等
- UE5.2 筆記
  - 主要內容為 UE5.2虛幻引擎 開發
- 修正大部分Markdown文檔的數學格式
  - https://gist.github.com/jesshart/8dd0fd56feb6afda264a0f7c3683abbf

## 值得一看的b站影片
- [GAMES-Webinar b站主頁](https://space.bilibili.com/512313464)
  - 一個關於研究計算機圖形學組織，內有大量圖形學，每星期有研討會，包含大量關於學術界和工業界前沿知識講授。
  - GAMES101, GAMES202, GAMES104 都是很優質的系列!
- [CSAPP-深入理解计算机系统](https://www.bilibili.com/video/BV1cD4y1D7uR)
  - 源於書本 - 深入理解计算机系统，不論是中文和英文都難以理解，這裡有高質量動畫影片能通俗易懂計算機原理
- []
## 值得一看的YT影片
- [C++ 3D DirectX 11 Tutorial](https://www.youtube.com/watch?v=2NOgrpXks9A&t=1s&ab_channel=ChiliTomatoNoodle)
  - 由ChiliTomatoNoodle發佈的C++ 3D DirectX 11教學，一個很硬核的教學系列，內含主要為DirectX 11 API和軟件工程等知識，學習前需要了解基本的圖形學數學知識和使用github等技巧，Chili也在Discord活躍中，在c++領域中也有許多相關影片
- [Vol 036 如何设计一个逼真的三维模型 | 回形针](https://www.youtube.com/watch?v=LgZctC4uM3Q&t=354s&ab_channel=%E5%9B%9E%E5%BD%A2%E9%92%88PaperClip)
  - 內有計算機圖形學中著名的貝塞爾曲線和B樣條
## 值得一看的知乎專題和文章系列
- [《DirectX12 3D游戏开发实战》](https://zhuanlan.zhihu.com/p/422696799)
  - DirectX12 圖形api 教學筆記
- [实时渲染GI｜Directional Occlusion：SSDO](https://zhuanlan.zhihu.com/p/369750415)
  - 環境光吸收質量，一種為相互靠近的物體增加柔和的陰影，極大地提升高圖像質量
- [浅谈卡通渲染与真实感渲染结合思路](https://zhuanlan.zhihu.com/p/561494026)
  - "三渲二" 技術導讀，很好的科普文章
- [UE5渲染技术简介：Nanite篇](https://zhuanlan.zhihu.com/p/382687738)
  - 在GAMES104前沿技術課上有提及，目前還沒有看懂
- [GAMES104《现代游戏引擎：从入门到实践》视频公开课文字实录](https://mp.weixin.qq.com/mp/appmsgalbum?__biz=Mzg5OTc1NjI5Ng==&action=getalbum&album_id=2583276961356152834&scene=173&from_msgid=2247483918&from_itemidx=1&count=3&nolastread=1#wechat_redirect)
  - GAMES104 文字實錄，想要節省流量只看文字版可以看這個
## 值得一看的Github倉庫/論文
- [Game-Programmer-Study-Notes](https://github.com/QianMo/Game-Programmer-Study-Notes)
  - 遊戲程序員毛星雲一生生涯的讀書筆記合輯
- [图形学论文实现](https://github.com/AngelMonica126/GraphicAlgorithm)
  - 論文 + 代碼，助你更好理解圖形學
- [High-Resolution Image Synthesis with Latent Diffusion Models](https://arxiv.org/abs/2112.10752)
  - Diffusion Models 開山論文，近期很火的NovelAI(AI畫畫)中也有相關模型
## 值得一看的書
- 《Real–time Rendering 3rd》
- 《Real–time Rendering 4th》
- [《GPU Gems 1 》](https://developer.nvidia.com/gpugems/gpugems/foreword)
- [《GPU Gems 2 》](https://developer.nvidia.com/gpugems/gpugems2/inside-front-cover)
- [《GPU Gems 3 》](https://developer.nvidia.com/gpugems/gpugems3/foreword)
- 《Game Engine Architecture》
## 倉庫目錄
- 計算機圖形學 筆記:
  1. [材質的構成](./GraphicQuest/GQ001%20材質的構成.md)
  2. [模型格式和材質](./GraphicQuest/GQ002%20模型格式和材質.md)
  3. [HLSL入門和基本函數](./GraphicQuest/GQ004%20傳統光照模型詳解.md)
  4. [傳統光照模型詳解](./GraphicQuest/GQ004%20傳統光照模型詳解.md)
  5. [Gamma校正和色彩空間](./GraphicQuest/GQ005%20Gamma校正%20和%20色彩空間.md)
  6. [LDR和HDR](./GraphicQuest/GQ006%20LDR和HDR.md)
  7. [材質和外觀](./GraphicQuest/GQ007%20材質和外觀.md)
  8. [相機與透鏡](./GraphicQuest/GQ008%20相機與透鏡.md)
  9. [實現Flowmap](./GraphicQuest/GQ011%20實現Flowmap.md)
- 計算機圖形學筆記 - 實時渲染篇 (Real–time Rendering)
  1. [實時渲染1_Shadow Mapping、PCSS、VSSM、SDF Shadows](./GraphicQuest/GQ009%20實時渲染1_Shadow%20Mapping、PCSS、VSSM、SDF%20Shadows.md)
  2. [實時渲染2 延遲渲染 Deferred Rendering](./GraphicQuest/GQ010%20實時渲染2%20延遲渲染%20Deferred%20Rendering.md)
  3. [實時渲染3 實時環境光照：Split Sum、PRT](./GraphicQuest/GQ012%20實時渲染3%20實時環境光照：環境光照與預計算%20環境光與Split%20Sum、PRT.md)
  4. [實時渲染4 3D空間GI的LPV算法和VXGI算法 SSAO算法](./GraphicQuest/GQ013%20實時渲染4%203D空間GI的LPV算法和VXGI算法%20SSAO算法.md)
  5. [實時渲染5 高級著色 BRDF及相關技術](./GraphicQuest/GQ014%20實時渲染5%20高級著色%20BRDF及相關技術.md)
- C++ DirectX 11 筆記 (源於Chili架構):
  1. [Mipmapping](C++MainQuest/C++DirectX/LV201-Mipmapping.md)
  2. [Anisotropic Filtering](C++MainQuest/C++DirectX/LV202-Anisotropic%20Filtering.md)
  3. [Alpha Compositing](C++MainQuest/C++DirectX/LV203-Alpha%20Compositing.md)
  4. [Ztest](C++MainQuest/C++DirectX/LV204-Ztest.md)
  5. [CD3D11](C++MainQuest/C++DirectX/LV205-CD3D11.md)
- Unity 筆記 (青春版):
  1. [Unity簡介](Unity/LV001-Unity簡介.md)
  2. [Unity介面](Unity/LV002-Unity介面.md)
  3. [Unity_CCShader](Unity/LV003-Unity_CCShader.md)
  4. [Unity Shader](C++MainQuest/Unity/LV101-Unity%20Shader.md)
  5. [Lambert光照模型](C++MainQuest/Unity/LV103-Lambert光照模型.md)
- C++ WindowsAPI 筆記 (源於Chili架構):
  1. [創建WinMain](C++MainQuest/C++Windows/LV001-創建WinMain.md)
  2. [更多WinMain資料](C++MainQuest/C++Windows/LV002-更多WinMain資料.md)
  3. [創建一個窗口](C++MainQuest/C++Windows/LV003-創建一個窗口.md)
- C++ 雜項 筆記:
  1. [i++和++i哪個快](./C++SideQuest/SQ001%20i++和++i哪個快.md)
  2. [神寄的ASCII碼](C++SideQuest/SQ002%20神寄的ASCII碼.md)
  3. [基於複製的瞬間移動](./C++SideQuest/SQ003%20基於複製的瞬間移動.md)
  4. [COM架構](./C++SideQuest/SQ004%20COM架構.md)
  5. [速通LeetCode水題一百道](./C++SideQuest/SQ005%20速通LeetCode水題一百道.md)
- 算法分析與設計:
  1. [01_算法概略](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/01_%E7%AE%97%E6%B3%95%E6%A6%82%E7%95%A5.md)
  2. [02_递归分治](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/02_%E9%80%92%E5%BD%92%E5%88%86%E6%B2%BB.md)
  3. [03_動態規劃](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/03_%E5%8B%95%E6%85%8B%E8%A6%8F%E5%8A%83.md)
  4. [04_貪心算法](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/04_%E8%B2%AA%E5%BF%83%E7%AE%97%E6%B3%95.md)
  5. [05_回溯法](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/05_%E5%9B%9E%E6%BA%AF%E6%B3%95.md)
  6. [06_分支限界法](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/06_%E5%88%86%E6%94%AF%E9%99%90%E7%95%8C%E6%B3%95.md)
  7. [08_線性規劃](%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90%E8%88%87%E8%A8%AD%E8%A8%88/08_%E7%B7%9A%E6%80%A7%E8%A6%8F%E5%8A%83.md)
- 遊戲開發工具包: 
  1. [免費／付費美術資源地址整合](art_asset.md)

- 手寫軟光珊:
  1. [手寫軟光柵1](/game-dev/GraphicQuest/GQ021%20手寫軟光柵1.md)
  2. [手寫軟光柵2](/game-dev/GraphicQuest/GQ022%20手寫軟光柵2.md)
  3. [手寫軟光柵3](/game-dev/GraphicQuest/GQ023%20手寫軟光柵3.md)
  4. [手寫軟光柵4](/game-dev/GraphicQuest/GQ024%20手寫軟光柵4.md)
  5. [手寫軟光柵5](/game-dev/GraphicQuest/GQ025%20手寫軟光柵5.md)
  6. [手寫軟光柵6](/game-dev/GraphicQuest/GQ026%20手寫軟光柵6.md)

# 遊戲編程?

遊戲編程這個方向看似很明確，其實並不然。
製作一款遊戲可以不用學會編程語言，甚至是可以離開電腦。我們回歸到人類原始的遊戲類型桌遊，我們對這各個類型不一的紙牌也能玩的很開心，精美的卡片，多變的規則，複雜的人心，公正的主持，都是遊戲的主要構成元素，在此之上，當我們學習如何製作一款"桌遊"的規則時，我們也就成為了所謂的"Gameplay Programmer" 遊戲邏輯程序員，他們就是在遊戲世界制定所有秩序之神————忒彌斯

那麼創造這個遊戲世界大地之神是誰?當然是我們的 "Game Engine Programmer" 遊戲引擎程序員，比起掌握所有的規則，掌握了遊戲引擎更像是掌握這片遊戲世界的核心，比起天馬行空的遊戲策劃，他們更願意去腳踏實地做好遊戲裡的每一片細節，以致於他們在遊戲開發組裡是不常被提起的一幫人。絕大多數初創遊戲公司想進一步擴大業務的時候，都一定需要一名蓋亞來協助他們的工作，所以學習遊戲引擎具有極高的價值。

## 做哪種程序員?

一般來說，想成為遊戲邏輯程序員只需要學習入門划時代的遊戲引擎就可以了，比如可以學習使用虛幻4,虛幻5,Unity這種主流的遊戲引擎，但是對電腦設備要求比較高，而且對於新人程序員來說，學習上手任一款遊戲引擎的難度都是差不多的，在對比如使用c++語言的UE4,UE5和使用c#語言的unity來說，如果僅僅學習過c++語言和c#語言基本語法以及都沒有上手項目的經驗，可以說你對遊戲引擎裡編程語言起步點為0，學習哪一個遊戲引擎都是一樣的。

但是使用遊戲引擎畢竟是停留在表面看不到本質，當遊戲開發的時候出現了某些問題或者特殊需求，你往往很難處理。而且遊戲引擎技術日新月異，你所學的幾乎都是別人留下來的方法，而不是其本質思想。如果將來別的遊戲引擎興起，你又要重新學習另外的遊戲引擎怎麼使用。在很多大公司裡面，甚至都有自己公司內部專用的引擎（如網易公司的風魂引擎、金山公司的劍網3引擎、蝸牛公司的Flexi引擎等等）。所以單純地走這條路線，可能不會讓你走得很遠並且可能會日漸乏味。

深入學習遊戲引擎原理短時間不會讓你的工作有什麼卓越的成效，但是可以彌補只使用遊戲引擎導致的問題，而且學習遊戲引擎原理，更多時候不是一定就為了自己日後要造個遊戲引擎，而是更深入理解自己的遊戲引擎，更好地使用它。當然，千里之行始於足下，經常學習遊戲引擎底層原理的人到了一定的積累的時候，自己造個遊戲引擎也是可以的。對於像學習遊戲引擎原理的人來說，需要製定自己明確的長期目標：

1. 首先，一開始可能對遊戲引擎沒什麼概念，建議還是先使用一兩個遊戲引擎（推薦可以學習虛幻4,虛幻5遊戲引擎，所有免費開源的遊戲引擎都非常值得學習。）

2. 因為遊戲開發就是一門實時渲染的藝術，所以離不開圖形庫的學習。現在主流的圖形庫是Windows平台專用的DirectX 11和通用平台的Opengl。這兩個圖形庫，至少需要入門其中一個。經實測，入門DirectX 11過程比入門Opengl難上很多，如果想要學習更高端的軟件工程中設計原理以及c++中的智慧型指針等可以選擇

3. 然後，你就可以開始看計算機圖形學的書籍了。如果你發現你的理論底子不足，這個時候就需要補一下線性代數、基本的微積分、還有3D數學的知識(內容難但不多)。

4. 遊戲引擎中包含了各個部分，上面的渲染只是遊戲引擎的一部分。還有其它諸如著色器編寫、地形編寫、物理引擎編寫、模型和動畫、人工智能(AI)設計、網絡編程等等，完成渲染部分的基本學習後，你可以選擇自己感興趣的部分進行專攻，畢竟我們實際工作大多數時候是團隊開發，而不是單打獨鬥，每個人都應該精通自己所擅長的那部分。

在不少的編程語言都會視其為一個項目，如貪食蛇小遊戲，俄羅斯方塊等，但這並不是我們想要在2022年玩到的遊戲。在划時代的技術下，我們更多的依賴各式各樣硬件加速技術和軟件工程技術去製作一款遊戲。

![](pic/GAMES104%20Mindmap%20V1.0.jpg)

# 備忘錄
> 部分內容來自於知乎
