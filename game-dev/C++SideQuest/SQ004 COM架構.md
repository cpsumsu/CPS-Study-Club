# COM架構

COM架構，元件物件模型（英語：Component Object Model，縮寫COM）

其實可以當成是一個普通的c++類，只不過COM架構更加具體且擁有統一的定義

在學習Direct3D的時候經常可以看見以大寫字母“I”為前綴COM接口。例如，表示2D紋理的接口為ID3D11Texture2D

所以在使用COM接口的時候，注意要使用其原有自帶的獲取和釋放方法，不要使用new 和delete

細節還有很多，只需要知道其特殊性和存在就可以了