跨域（Cross-Domain）是 Web 开发中非常经典且高频遇到的问题。简单来说，就是浏览器出于安全考虑，限制了一个**源**（Origin）的文档或脚本如何与另一个源的资源进行交互。

### 1. 什么是同源策略（Same-Origin Policy）？

跨域问题的根源是浏览器的**同源策略**。这是一种安全协议，规定：**只有当协议、域名、端口**三者完全一致时，两个 URL 才被视为“同源”，否则就是“跨域”。

| URL 1 | URL 2 | 是否跨域 | 原因 |
| :--- | :--- | :--- | :--- |
| `http://www.a.com` | `http://www.a.com` | 否 | 完全一致 |
| `http://www.a.com` | `https://www.a.com` | **是** | **协议**不同 (http vs https) |
| `http://www.a.com` | `http://api.a.com` | **是** | **域名**不同 (www vs api) |
| `http://www.a.com:80` | `http://www.a.com:8080` | **是** | **端口**不同 |
| `http://127.0.0.1` | `http://localhost` | **是** | 域名不同 (虽然都指向本机) |

**注意：** 跨域限制只存在于**浏览器端**。服务器与服务器之间通信（如 Node 调 Java 接口）、爬虫、Postman 等都不受同源策略限制。

### 2. 为什么会有跨域限制？

主要是为了**安全**。如果没有这个限制，恶意网站可以通过脚本读取你银行网站的数据（因为你的浏览器里存有银行的 Cookie），导致数据泄露或 CSRF 攻击。

**跨域通常拦截以下行为：**
1.  **AJAX/Fetch 请求：** 无法读取响应内容（虽然请求可能发送成功了）。
2.  **Cookie/LocalStorage：** 无法读取其他域的存储。
3.  **DOM 操作：** 无法操作其他域页面的 DOM（如 iframe）。

### 3. 常见的跨域解决方案

根据场景不同（开发环境 vs 生产环境，简单需求 vs 复杂需求），有多种解决方案。

#### 3.1 CORS (Cross-Origin Resource Sharing) —— **主流方案**
这是 W3C 的标准方案，通过后端设置 HTTP 响应头来告诉浏览器“我允许这个域访问我”。

*   **原理：** 浏览器发送请求 -> 后端响应头带上 `Access-Control-Allow-Origin` -> 浏览器检查通过 -> 放行。
*   **后端配置示例 (Node/Express):**
    ```javascript
    app.use((req, res, next) => {
      res.header('Access-Control-Allow-Origin', 'http://www.a.com'); // 或者 '*'
      res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization');
      res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE');
      next();
    });
    ```
    
*   **优点：** 标准支持，兼容性好，支持所有 HTTP 动词。
*   **缺点：** 需要后端配合修改代码或配置。

#### 3.2 代理Proxy (Nginx / 开发服务器) —— **开发环境常用**
利用服务器没有同源策略的特点，让浏览器请求同源的开发服务器，开发服务器再转发请求给目标服务器。

*   **开发环境 (Webpack/Vite):**
    ```javascript
    // vite.config.js
    export default {
      server: {
        proxy: {
          '/api': {
            target: 'http://backend.com',
            changeOrigin: true, // 修改请求头中的 Host 为目标域
            rewrite: (path) => path.replace(/^\/api/, '')
          }
        }
      }
    }
    ```
*   **生产环境 (Nginx):**
    ```nginx
    location /api/ {
        proxy_pass http://backend.com/;
    }
    ```
*   **优点：** 前端无需改动代码，不需要后端配合（针对开发环境）。
*   **缺点：** 生产环境需要运维配置 Nginx；增加了一次网络转发。

### 4. CORS 深度解析：简单请求与预检请求

浏览器将 CORS 请求分为两类，这决定了后端需要处理多少逻辑。

#### 4.1 简单请求 (Simple Request)
满足以下所有条件：
1.  方法是 `HEAD`, `GET`, `POST` 之一。
2.  HTTP 头信息不超出以下字段：`Accept`, `Accept-Language`, `Content-Language`, `Content-Type` (仅限 `application/x-www-form-urlencoded`, `multipart/form-data`, `text/plain`)。

**流程：** 浏览器直接发送请求，后端返回带 CORS 头的响应。

#### 4.2 预检请求 (Preflight Request)
如果不满足简单请求条件（例如使用了 `PUT` 方法，或 `Content-Type: application/json`，或自定义了 Header）。

**流程：**
1.  浏览器先发送一个 **`OPTIONS`** 请求（预检）。
2.  后端收到 OPTIONS 请求，检查是否允许该源、该方法和该 Header。
3.  后端返回允许的头信息（如 `Access-Control-Allow-Methods: PUT`）。
4.  浏览器确认无误后，再发送真正的请求。

**后端必须处理 OPTIONS 请求**，否则预检失败，真实请求不会发送。

### 5. 跨域与 Cookie (凭证)

默认情况下，跨域请求**不包含** Cookie。如果业务需要携带 Cookie（如保持登录状态），需要特殊配置。

**前端设置：**
```javascript
fetch('http://api.b.com/data', {
  credentials: 'include' // 或者 xhr.withCredentials = true
});
```

**后端设置：**
1.  `Access-Control-Allow-Credentials: true`
2.  **注意：** 此时 `Access-Control-Allow-Origin` **不能设置为 `*`**，必须指定具体的域名（如 `http://www.a.com`）。

### 6. 常见坑与注意事项

1.  **302 重定向丢失 CORS 头：**
    如果后端接口发生了重定向，重定向后的响应如果没有带上 CORS 头，浏览器会报错。确保重定向链路上的所有响应都有 CORS 头。
2.  **`*` 与 Cookie 互斥：**
    如果你需要携带 Cookie，后端 `Allow-Origin` 绝不能写 `*`，必须动态获取请求头中的 `Origin` 并回写。
3.  **开发环境 vs 生产环境：**
    *   开发时：推荐用 **Proxy**（配置在 `vite.config.js` 或 `webpack` 中），方便调试，不用求后端改配置。
    *   生产时：推荐用 **CORS**（后端配）或 **Nginx 反向代理**（运维配）。
4.  **CSRF 攻击：**
    CORS 是为了防止读取数据，**不能防止 CSRF 攻击**。防止 CSRF 主要靠 Cookie 的 `SameSite` 属性、Token 验证或 Referer 检查。
5.  **Spring Boot 配置：**
    Java 后端常用 `@CrossOrigin` 注解或全局配置 `WebMvcConfigurer` 的 `addCorsMappings` 方法。
