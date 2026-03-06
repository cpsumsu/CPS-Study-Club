> 相关页面：[HTTPS](HTTPS-and-TLS.md)

## 一、概述

HTTP 协议（HyperText Transfer Protocol）是互联网通信的基础。在 HTTP 报文（Message）中，**请求头（Request Headers）** 和 **响应头（Response Headers）** 扮演着“元数据”的角色，它们告诉对方“我是谁”、“我想要什么”、“我发给你的是什么”以及“如何处理这些数据”。

HTTP 报文结构通常分为四部分：
1.  **起始行**（请求行 / 状态行）
2.  **头部区域**（Headers，键值对）
3.  **空行**（区分头部和主体）
4.  **主体**（Body，可选）

下面详细解析请求头和响应头中常见的字段及其作用。

---

### 二、HTTP 请求头 (Request Headers)

**方向**：客户端（浏览器/App） -> 服务器
**作用**：告知服务器关于客户端的信息、请求的资源细节以及客户端能接受的数据格式。

| 字段名 | 说明 | 典型示例 |
| :--- | :--- | :--- |
| **Host** | **必选**。指定服务器的域名和端口。HTTP/1.1 中必须包含。 | `Host: www.google.com` |
| **User-Agent** | 客户端标识。包含浏览器类型、版本、操作系统等。用于兼容性处理或统计。 | `Mozilla/5.0 (Windows NT 10.0; ...)` |
| **Accept** | 客户端能接收的内容类型（MIME Type）。用于内容协商。 | `Accept: application/json` |
| **Accept-Encoding** | 客户端支持的压缩算法。服务器据此决定是否压缩响应。 | `Accept-Encoding: gzip, deflate` |
| **Accept-Language** | 客户端偏好的自然语言。 | `Accept-Language: zh-CN,zh` |
| **Content-Type** | **请求体**的数据格式。POST/PUT 请求中常见。 | `Content-Type: application/json` |
| **Content-Length** | 请求体的字节长度。 | `Content-Length: 128` |
| **Cookie** | 客户端携带的 Cookie 信息，用于维持会话状态。 | `Cookie: sessionId=abc123` |
| **Authorization** | 认证信息。常用于 Bearer Token 或 Basic Auth。 | `Authorization: Bearer <token>` |
| **Cache-Control** | 控制缓存行为。客户端告诉服务器如何处理缓存。 | `Cache-Control: no-cache` |
| **Referer** | 表示当前请求是从哪个页面链接过来的。用于防盗链或统计。 | `Referer: https://google.com` |
| **Origin** | 请求来源的域名（协议 + 域名 + 端口）。主要用于 CORS 跨域检查。 | `Origin: https://example.com` |

---

### 三、HTTP 响应头 (Response Headers)

**方向**：服务器 -> 客户端（浏览器/App）
**作用**：告知客户端关于服务器的信息、资源的状态、数据格式以及缓存策略。

| 字段名                             | 说明                                        | 典型示例                                           |
| :------------------------------ | :---------------------------------------- | :--------------------------------------------- |
| **Content-Type**                | **响应体**的数据格式。浏览器据此决定如何解析（显示 HTML 还是下载文件）。 | `Content-Type: text/html; charset=utf-8`       |
| **Content-Length**              | 响应体的字节长度。                                 | `Content-Length: 1024`                         |
| **Content-Encoding**            | 响应体使用的压缩算法。                               | `Content-Encoding: gzip`                       |
| **Set-Cookie**                  | 服务器要求客户端保存的 Cookie。                       | `Set-Cookie: sessionId=xyz; HttpOnly`          |
| **Cache-Control**               | **最重要**。指示客户端或中间代理如何缓存该响应。                | `Cache-Control: max-age=3600`                  |
| **ETag**                        | 资源的唯一标识符（哈希值）。用于验证缓存是否失效。                 | `ETag: "33a64df551425fcc55e4d42a148795d9"`     |
| **Last-Modified**               | 资源最后修改的时间。用于缓存验证。                         | `Last-Modified: Wed, 21 Oct 2023 07:28:00 GMT` |
| **Location**                    | 配合 3xx 状态码使用，指示重定向的目标 URL。                | `Location: https://new-url.com`                |
| **Server**                      | 服务器软件名称及版本。                               | `Server: nginx/1.18.0`                         |
| **Access-Control-Allow-Origin** | CORS 跨域资源共享。指定允许访问资源的域名。                  | `Access-Control-Allow-Origin: *`               |
| **Strict-Transport-Security**   | HSTS。强制客户端使用 HTTPS 连接。                    | `Strict-Transport-Security: max-age=31536000`  |

---

### 三、报文示例 (Raw HTTP)

为了更直观地理解，以下是原始的 HTTP 通信文本：

#### 1. 请求报文示例
```http
GET /api/users/123 HTTP/1.1
Host: api.example.com
User-Agent: Mozilla/5.0
Accept: application/json
Authorization: Bearer eyJhbGciOiJIUzI1NiIs...
Cache-Control: no-cache
Connection: keep-alive

(空行)
(无 Body，因为是 GET 请求)
```

#### 2. 响应报文示例
```http
HTTP/1.1 200 OK
Date: Mon, 23 Oct 2023 10:00:00 GMT
Server: nginx
Content-Type: application/json; charset=utf-8
Content-Length: 45
Cache-Control: max-age=600
ETag: "a1b2c3d4"
Set-Cookie: session=abc; Path=/; HttpOnly
Access-Control-Allow-Origin: https://www.example.com

(空行)
{"id": 123, "name": "Alice", "role": "admin"}
```

---

### 四、核心机制深度解析

#### 1. 内容协商 (Content Negotiation)
*   **请求侧**：`Accept` 告诉服务器“我想看 JSON"。
*   **响应侧**：`Content-Type` 告诉客户端“我给你的确实是 JSON"。
*   **场景**：移动端和 PC 端访问同一 URL，服务器根据 `User-Agent` 返回不同格式的 HTML；或 API 根据 `Accept` 返回 JSON 或 XML。

#### 2. 缓存控制 (Caching)
这是性能优化的关键。
*   **强缓存**：由 `Cache-Control: max-age=3600` 控制。客户端在 1 小时内直接使用本地副本，**不发送请求**给服务器。
*   **协商缓存**：由 `ETag` / `Last-Modified` 控制。客户端发送请求，带上 `If-None-Match` (对应 ETag)，服务器判断资源未变则返回 `304 Not Modified`，**不返回 Body**，节省流量。

#### 3. 跨域安全 (CORS)
浏览器同源策略限制前端 JS 访问不同域名的接口。
*   **请求**：浏览器自动带上 `Origin` 头。
*   **响应**：服务器必须返回 `Access-Control-Allow-Origin`，浏览器校验通过后才允许 JS 读取响应数据。

#### 4. 连接管理 (Connection)
*   `Connection: keep-alive`：表示 TCP 连接在请求结束后保持打开，后续请求复用该连接，减少 TCP 握手开销。
*   `Connection: close`：表示本次请求响应完成后，立即关闭 TCP 连接。

---

### 五、总结建议

1.  **安全性**：生产环境建议隐藏 `Server` 头（避免泄露版本漏洞），并配置 `Strict-Transport-Security` (HSTS) 和 `X-Content-Type-Options: nosniff`。
2.  **性能**：合理配置 `Cache-Control` 和 `ETag` 是提升网页加载速度的最有效手段之一。
3.  **调试**：在浏览器开发者工具（F12 -> Network）中可以清晰地看到每一次请求的 Request Headers 和 Response Headers，是排查接口问题（如 401 认证失败、403 跨域禁止、缓存不更新）的第一现场。