## ELK stack

數據(log)散落在不同的pod，數據缺失observability，因此需要一個平台ELK stack進行：

收集->整理->儲存->分析->可視化->警告

![](..\assets\img\elk-stack\1.PNG)

Elastic stack是甚麼?

![](..\assets\img\elk-stack\2.PNG)

**Kibana**數據可視化

**Elasticsearch**儲存、搜尋、分析

![](..\assets\img\elk-stack\3.PNG)



## **Beats**是甚麼? 

一個輕量的**數據採集器**

![](..\assets\img\elk-stack\4.PNG)

**Packetbeat** 封包數據

**Metricbeat** VM指標(CPU, memory, network)數據

**Winlogbeat** Windows Log數據



Fliebeat example

![](..\assets\img\elk-stack\5.PNG)

Matricbeat example

![](..\assets\img\elk-stack\6.PNG)

![](..\assets\img\elk-stack\7.PNG)



## 甚麼是logstash?

是一個**ETL引擎**，(ETL，Extract-Transform-Load的縮寫，是將業務系統的數據經過**抽取、清洗轉換之後加載到數據倉庫**的過程。)

![](..\assets\img\elk-stack\8.PNG)

Logstash進行一些數據處理，再output到elasticsearch等平台

![](..\assets\img\elk-stack\9.PNG)



## logstash或是beats?

![](..\assets\img\elk-stack\10.PNG)



## Elasticsearch? For search

![](..\assets\img\elk-stack\11.PNG)

![](..\assets\img\elk-stack\12.PNG)

load balancing: 不同的index(database)會放在不同的data node

high availability: replication segment on different data node



## Kibana

![](..\assets\img\elk-stack\13.PNG)

![](..\assets\img\elk-stack\14.PNG)



## ELK stack能做甚麼?

![](..\assets\img\elk-stack\15.PNG)

![](..\assets\img\elk-stack\16.PNG)

![](..\assets\img\elk-stack\17.PNG)

![](..\assets\img\elk-stack\18.PNG)

![](..\assets\img\elk-stack\19.PNG)

應用監察，甚麼時候request多，error的佔比

![](..\assets\img\elk-stack\20.PNG)

![](..\assets\img\elk-stack\21.PNG)

## ELK stack的優勢

導入效益分析

![](..\assets\img\elk-stack\22.PNG)

![](..\assets\img\elk-stack\23.PNG)



## 使用時的注意事項

![](..\assets\img\elk-stack\24.PNG)

**非常注重記憶體**



## Hot-warm?

![](..\assets\img\elk-stack\25.PNG)