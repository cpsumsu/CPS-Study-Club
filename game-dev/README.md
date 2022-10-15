## 前言

> 我們所有的夢想都可以真的，只要我們有勇氣去追求它們（All our dreams can come true, if we have the courage to pursue them）。 
> ———— 華特·迪士尼

# 遊戲編程筆記
個人學習遊戲編程，收錄於CPSStudyClub，以後可能再整理一下倉庫內的目錄

## 值得一看的b站影片
- [GAMES-Webinar b站主頁](https://space.bilibili.com/512313464)
  - 一個關於研究計算機圖形學組織，內有大量圖形學，每星期有研討會，包含大量關於學術界和工業界前沿知識講授。
  - GAMES101, GAMES202, GAMES104 都是很優質的系列!
- [CSAPP-深入理解计算机系统](https://www.bilibili.com/video/BV1cD4y1D7uR)
  - 源於書本 - 深入理解计算机系统，不論是中文和英文都難以理解，這裡有高質量動畫影片能通俗易懂計算機原理
## 值得一看的YT影片
- [C++ 3D DirectX 11 Tutorial](https://www.youtube.com/watch?v=2NOgrpXks9A&t=1s&ab_channel=ChiliTomatoNoodle)
  - 由ChiliTomatoNoodle發佈的C++ 3D DirectX 11教學，一個很硬核的教學系列，內含主要為DirectX 11 API和軟件工程等知識，學習前需要了解基本的圖形學數學知識和使用github等技巧，Chili也在Discord活躍中，在c++領域中也有許多相關影片
- [Vol 036 如何设计一个逼真的三维模型 | 回形针](https://www.youtube.com/watch?v=LgZctC4uM3Q&t=354s&ab_channel=%E5%9B%9E%E5%BD%A2%E9%92%88PaperClip)
  - 內有計算機圖形學中著名的貝塞爾曲線和B樣條
## 值得一看的知乎專題
- [《DirectX12 3D游戏开发实战》](https://zhuanlan.zhihu.com/p/422696799)
  - DirectX12 圖形api 教學筆記
- [实时渲染GI｜Directional Occlusion：SSDO](https://zhuanlan.zhihu.com/p/369750415)
  - 環境光吸收質量，一種為相互靠近的物體增加柔和的陰影，極大地提升高圖像質量
- [浅谈卡通渲染与真实感渲染结合思路](https://zhuanlan.zhihu.com/p/561494026)
  - "三渲二" 技術導讀，很好的科普文章
- [UE5渲染技术简介：Nanite篇](https://zhuanlan.zhihu.com/p/382687738)
  - 在GAMES104前沿技術課上有提及，目前還沒有看懂
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
- 《GPU Gems 1 》
- 《GPU Gems 2 》
- 《GPU Gems 3 》
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
- 計算機圖形學筆記 - 實時渲染篇 (Real–time Rendering)
  1. [實時渲染1_Shadow Mapping、PCSS、VSSM、SDF Shadows](./GraphicQuest/GQ009%20實時渲染1_Shadow%20Mapping、PCSS、VSSM、SDF%20Shadows.md)
- C++ DirectX 11 筆記 (源於Chili架構):
  1. [Mipmapping](C++MainQuest/C++DirectX/LV201-Mipmapping.md)
  2. [Anisotropic Filtering](C++MainQuest/C++DirectX/LV202-Anisotropic%20Filtering.md)
  3. [Alpha Compositing](C++MainQuest/C++DirectX/LV203-Alpha%20Compositing.md)
  4. [Ztest](C++MainQuest/C++DirectX/LV204-Ztest.md)
  5. [CD3D11](C++MainQuest/C++DirectX/LV205-CD3D11.md)
- C++ WindowsAPI 筆記 (源於Chili架構):
  1. [創建WinMain](C++MainQuest/C++Windows/LV001-創建WinMain.md)
  2. [更多WinMain資料](C++MainQuest/C++Windows/LV002-更多WinMain資料.md)
  3. [創建一個窗口](C++MainQuest/C++Windows/LV003-創建一個窗口.md)
- C++ 雜項 筆記:
  1. [i++和++i哪個快](./C++SideQuest/SQ001%20i++和++i哪個快.md)
  2. [神寄的ASCII碼](C++SideQuest/SQ002%20神寄的ASCII碼.md)
  3. [基於複製的瞬間移動](./C++SideQuest/SQ003%20基於複製的瞬間移動.md)
  4. [COM架構](./C++SideQuest/SQ004%20COM架構.md)

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


# 備忘錄
> 部分內容來自於知乎
