## ATT&CK

> 來源: https://medium.com/h1dra-security-team/%E5%BE%9E%E7%B4%85%E9%9A%8A%E8%A7%92%E5%BA%A6%E7%9C%8B-mitre-att-ck-att-ck-%E5%9F%BA%E6%9C%AC%E4%BB%8B%E7%B4%B9-d69a72b80d39

紀錄資安攻擊與情資分享的資料庫

是紅隊與藍隊之間溝通的橋樑

ATT&CK® 順應攻擊者的變化，每兩年更新一次 ATT&CK® 內容與定期更新網站

![](https://miro.medium.com/max/828/1*N9sDUNeBjK2Zcct3FPZZ-Q.png)

ATT&CK® 是 MITRE 創立，這個來自美國非營利研究機構源自於麻省理工，專注國防領域先進計畫，並透過 NIST 資助開啟許多[資安研發計畫](https://www.mitre.org/capabilities/cybersecurity/overview)，除了 ATT&CK® 這一個專案之外，還有其他哪一些著名的資安專案，可以大略分成四個主題：

- **資安弱點情資分享**：CVE 漏洞資料庫 (http://cve.mitre.org/）
- **資安威脅情資分享**：ATT&CK® 攻擊資料庫 (https://attack.mitre.org/）
- **資安開源工具分享**：Cuckoo、Yaraprocessor
- **資安相關計畫分享**：軟體安全、供應鏈風險管理、應用程式安全等

ATT&CK® 的存在則是為了**記錄惡意攻擊者的行為**，並表示主要有四個原因促成了 ATT&CK® 這個專案

![](https://miro.medium.com/max/828/1*j9YajuA6wZix7OB5q6w5Mg.png)

**關於惡意攻擊者**

許多國家培養「國家駭客」或稱呼為「網軍」進行惡意攻擊，以竊取國家、軍事、政治、商業機密，除了國家駭客外，也有以「營利」為目的駭客集團，勒索特定企業，獲得高額贖金。

這些駭客通常以「特定攻擊目標」、「長期」、「目的性」進行攻擊，也就是所謂的**進階持續性威脅（Advanced Persistent Threat，簡稱 APT）。**

![](https://miro.medium.com/max/828/1*P6zK2i7GH_IGLRzEM0d2AA.png)

**何謂 ATT&CK®**

全稱 Adversarial Tactics, Techniques, and Common Knowledge，
從名字了解 ATT&CK® 是一個收集惡意攻擊者的策略、技巧與通用的資料庫。

收集這些攻擊者的欲達成的目標與攻擊手法，最後整理這些手法，以編列編號的方式做成資料庫，讓參考 ATT&CK® 的人可以很快速透過編號對應到攻擊行為與手法。

![](https://miro.medium.com/max/828/1*cOFYyaV44vuK31DX22BZZg.png)

**以「攻擊者的角度」描述攻擊者用到的手法、軟體與工具**

APT 組織透過一段攻擊流程，取得最終利益，其中攻擊手法可以分解成 TTPs，其中 TTPs 分別為：

- T，Tactics：攻擊者預期達成的目標→該階段的目標，定義戰術與策略
- T，Techniques：達成階段目標所執行的手法→策略中的技巧與技術
- P，Procedures：攻擊者所使用或開發的軟體與工具→技術實現的過程

TTPs 的階層為：Tactics > Techniques > Procedures：
一個 Tactics 階段目標中有多個 Techniques 可達到目標的手法，
一個 Techniques 執行手法有多個使用的 Procedures 軟體或工具。



以數學的角度，可以把 Tactics 與 Techniques 組成一個矩陣，來對照所有的階段目標與執行手法，如下圖顯示：

1. 藍框圈起來為 Tactics，代表攻擊者預期達成的目標。
2. 綠框圈起來為「Resource Development」可達到該目標的 Techniques
3. 紫框圈起來發現相同的 Techniques 也會對應到多個 Tactics，
   因此取決於**該手法是為了達成什麼目的**。

![img](https://miro.medium.com/max/875/1*0HtpBCK-dosRk4Ux2OBAcg.png)



**以一個資安事件作為範例：**

> 駭客透過電子郵件寄送釣魚信件，信件附檔內包含惡意程式，該惡意程式為勒索軟體。
>
> 駭客於信件內容中，**告知該程式可以自動化更新軟體，下載後請立即執行確保安全性，**誘使受害者下載附檔。
>
> 受害者按照指示下載並執行，導致勒索軟體觸發，造成受害者的商業資料被加密，財物損失。

可以解析成以下四個階段：

1. **收集受害者的電子信箱**
2. **寄送夾帶惡意檔案的釣魚信件**
3. **受害者下載與執行惡意檔案**
4. **商業資料被加密**

加以分析這個資安事情並與 ATT&CK® 官方網站中的內容進行對應，了解所謂的 TTPs：

![img](https://miro.medium.com/max/875/1*gBM4_ee32wUtXHTNYVJQUQ.png)

### 1. 搜尋受害者的電子信箱

- Ｔ：預期達成目標：收集
  **→ 對應：TA0043 Reconnaissance**
  這個**戰術**中所列出的手法，都是惡意攻擊者嘗試收集未來行動可用到的資訊如基礎建設的資訊或目標企業的員工資訊，這些可以幫助攻擊者攻擊生命週期的其他階層，如透過收集來的資訊計畫或執行「初始訪問」等。
- Ｔ：駭客使用手法：收集被害者的電子郵件地址
  **→ 對應：T1589.002 Gather Victim Identity Information: Email Addresses
  **這個**手法**是關於進行攻擊受害者之前，攻擊者會先收集電子郵件地址，可能透過社交媒體或是受害人自己公開的網站，以利下一步的攻擊。
- Ｐ：駭客使用工具：Google Hacking、社交媒體或 OSINT
  **→ 對應：未收錄在 Software**

### 2. 寄送夾帶惡意檔案的釣魚信件

- Ｔ：預期達成目標：取得進入受害者網路的初始立足點
  **→ 對應：TA0001 Initial Access
  **這個**戰術**列出關於攻擊者如何進入受害者網路初始立足點的手法，攻擊者可透過 VPN、網路釣魚、硬體、USB 裝置、預設帳號密碼，甚至於供應鏈中部份產品埋入惡意程式碼，作為進入受害者網路的入口。
- Ｔ：駭客使用手法：發送惡意附件的釣魚信件
  **→ 對應：T1566.001 Phishing: Spearphishing Attachment
  **該**手法**提到攻擊者會發送有惡意附件的釣魚信件，以試圖取得受害者系統的網路存取權限。釣魚信件的內容，會誘使受害者開啟甚至解壓縮，附件的格式可能為 docx、exe、sh、pdf、zip、rar 等格式。當打開惡意附件或解壓縮，攻擊者的惡意程式碼會利用漏洞或直接於受害者系統執行。
- Ｐ：駭客使用工具：Gmail 或 mail Server
  **→ 對應：Software 中許多 APT 組織透過該手法進行攻擊**

### 3. 受害者開啟與執行惡意檔案

- Ｔ：預期達成目標：嘗試執行惡意程式碼
  **→ 對應：TA0002 Execution
  **該**戰術**為於受害者的系統執行惡意攻擊者的程式碼，導致受害者網路被入侵或是竊取資料，甚至攻擊者也可以遠端操控受害者電腦。惡意程式碼由許多不同的程式語言撰寫，或是濫用 Windows 本身的管理功能。
- Ｔ：駭客使用手法：誘使惡意攻擊者開啟含有惡意程式碼的檔案
  **→ 對應：T1204.002 User Execution: Malicious File
  **該**手法**需仰賴受害者開啟惡意檔案後執行惡意程式碼，受害者會受到社交工程攻擊，被要求執行惡意檔案。甚至攻擊者可能會偽裝惡意檔案，以增加受害者打開檔案的可能性。
- Ｐ：駭客使用工具：自製的惡意檔案
  **→ 對應：Software 中有許多 APT 組織製作的惡意檔案可以參考**

### 4. 商業資料被加密

- Ｔ：預期達成目標：
  **→ 對應：TA0040 Impact
  **該**戰術**是惡意攻擊者會嘗試控制、中斷或破壞受害者的系統與資料，包含刪除與竄改商業資料、刪除帳號權限、加密資料、新增惡意資料影響業務流程，以及 DoS 阻斷服務。
- Ｔ：駭客使用手法：
  **→ 對應：T1486 Data Encrypted for Impact**
  該手法為攻擊者加密受害者系統中的資料，以中斷系統和資源的可用性，為了達到勒索受害者，取得高額贖金，惡意攻擊者會針對 docx、pdf、圖片、影片、音檔、程式碼進行加密，甚至惡意檔案還有蠕蟲特性，在網路中進行傳播，擴大受害範圍。
- Ｐ：駭客使用工具：WannaCry
  **→ 對應：S0366 WannaCry
  **2017 年 05 月開始進行全球攻擊，除了加密資料之外，該勒索軟體還有蠕蟲功能，透過 SMBv1 漏洞透過 EternalBlue 在網路中進行傳播。

從以上四個流程可以了解關於 TTPs 的概念，進入 ATT&CK® 的官網中，也可以看到該 Techniques 的基本介紹與對應 ID、版本、新增日期與修正日期。