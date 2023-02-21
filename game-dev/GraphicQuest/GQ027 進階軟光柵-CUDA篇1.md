# 進階軟光柵-CUDA篇1

![](pic/最終成品.png)

最近發布的 NVIDIA GPU、RTX 技術和 Microsoft 的 DirectX 光線追踪重新激發了人們對光線追踪的興趣。使用這些技術極大地簡化了使用光線追踪編寫應用程序的能力。

但是，如果您對光線追踪的實際工作原理感到好奇怎麼辦？一種學習方法是編寫您自己的光線追踪引擎代碼。您想使用 CUDA 構建在您的 GPU 上運行的光線追踪器嗎？如果是這樣，這篇文章適合你！您將一口氣了解有關 CUDA 編程和光線追踪的更多信息。

這個系列文章的每個部分都對應"One Weekend"書中的其中一章。即使您不坐下來用 C++ 編寫自己的光線追踪器，這裡的核心概念也應該讓您開始了解以及使用 CUDA 基於 GPU 的引擎。

One Weekend 書中的 C​​++ 光線追踪引擎絕不是最快的光線追踪器，但將您的 C++ 代碼轉換為 CUDA 可以使速度提高 10 倍或更多！讓我們來看看將 C++ 代碼從一個週末的光線追踪轉換為 CUDA 的過程。

這篇文章假設您了解 CUDA 的一些基礎知識。如果沒有，您可以從 NVIDIA 開發者博客上的更簡單的 CUDA 介紹開始。您需要設置開發環境來編譯和運行 CUDA 代碼。

請注意，當 CUDA 代碼運行超過幾秒時，您可能會注意到錯誤 6 (cudaErrorLaunchTimeout)，並且在 Windows 上，您的屏幕也可能會黑屏幾秒。這是因為當 GPU 在一定時間後沒有響應時，您的窗口管理器認為 GPU 出現故障。

在這篇文章中，您將了解以下內容：

- 由 GPU 寫入並由 CPU 讀取的統一內存幀緩衝區
- 在 GPU 上啟動渲染工作
- 編寫可在 CPU 或 GPU 上運行的 C++ 代碼
- 檢查較慢的雙精度浮點代碼。
- C++內存管理。在 GPU 上分配內存並在運行時在 GPU 上實例化它。
- 使用 cuRAND 生成每線程隨機數。
- CPU = host, GPU = device

# 下載CUDA

[官網](https://developer.nvidia.com/cuda-downloads)

# 第一張照片

還記得之前我們第一張生成圖片嗎?

這是它的c++代碼，現在我們要把它變成CUDA代碼

首先先打開 __VS 2022__ 打開剛剛下載好的CUDA範本 (這裡用的是CUDA 12.0 Runtime)

```c++
#include <iostream>

int main()
{
	const int image_width = 256;
	const int image_height = 256;

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	
	for (int i = image_height - 1; i >= 0; --i)
	{
		for (int j = 0; j < image_width; ++j)
		{
			auto r = double(j) / (image_width - 1);
			auto g = double(i) / (image_height - 1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
}
```

![](https://media.discordapp.net/attachments/877161509808115713/1077495701719756820/image.png?width=1506&height=1002)


```c++
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);

__global__ void addKernel(int *c, const int *a, const int *b)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];
}

int main()
{
    const int arraySize = 5;
    const int a[arraySize] = { 1, 2, 3, 4, 5 };
    const int b[arraySize] = { 10, 20, 30, 40, 50 };
    int c[arraySize] = { 0 };

    // Add vectors in parallel.
    cudaError_t cudaStatus = addWithCuda(c, a, b, arraySize);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }

    printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
        c[0], c[1], c[2], c[3], c[4]);

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

    return 0;
}

// Helper function for using CUDA to add vectors in parallel.
cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size)
{
    int *dev_a = 0;
    int *dev_b = 0;
    int *dev_c = 0;
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
        goto Error;
    }

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
        goto Error;
    }

    // Copy input vectors from host memory to GPU buffers.
    cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

    // Launch a kernel on the GPU with one thread for each element.
    addKernel<<<1, size>>>(dev_c, dev_a, dev_b);

    // Check for any errors launching the kernel
    cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        goto Error;
    }
    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaStatus = cudaDeviceSynchronize();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
        goto Error;
    }

    // Copy output vector from GPU buffer to host memory.
    cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemcpy failed!");
        goto Error;
    }

Error:
    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
    
    return cudaStatus;
}
```

裡面的 $addKernel<<<1, size>>>$ 部分語法可能會引起某些錯誤，但是可以正常運行，代碼內容為數組相加，請忽略掉這部分錯誤。

這裡的文件尾名為 .cu ，但是其實可以用 c++ 語法去理解以上代碼。

第 1 章以為紅色和綠色通道生成具有簡單漸變的圖像結束。在串行語言中，您使用嵌套的 for 循環來遍歷所有像素。在 CUDA 中，調度程序獲取線程塊並在 GPU 上調度它們。但是，在我們開始之前，我們必須做一些準備工作……

我們進行的每個 CUDA API 調用都會返回一個我們應該檢查的錯誤代碼。在我們重置 CUDA 設備並退出之前，我們使用 checkCudaErrors 宏檢查 cudaError_t 結果以將錯誤輸出到標準輸出。有關任何錯誤的幫助，請參閱 [cudaError_t](https://docs.nvidia.com/cuda/cuda-runtime-api/group__CUDART__TYPES.html) 枚舉部分，了解每個錯誤代碼的含義。

```c++
// CUDA前置頭文件
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <time.h>

// limited version of checkCudaErrors from helper_cuda.h in CUDA examples
#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )

// 應該都是固定寫法了
void check_cuda(cudaError_t result, char const* const func, const char* const file, int const line) {
    if (result) {
        std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at " <<
            file << ":" << line << " '" << func << "' \n";
        // Make sure we call CUDA Device Reset before exiting
        cudaDeviceReset();
        exit(99);
    }
}
```

我們在主機上分配一個 nx*ny (長\*寬) 圖像大小的幀緩衝區 (FB) 來保存 GPU 計算的 RGB 浮點值，從而允許 CPU 和 GPU 之間的通信。 

由 cudaMallocManaged 分配統一內存，這使我們能夠依靠 CUDA 運行時將幀緩衝區按需移動到 GPU 進行渲染，然後返回 CPU 以輸出 PPM 圖像。使用 cudaDeviceSynchronize 讓 CPU 知道 GPU 何時完成渲染。

```c++

int main()
{
    // 長寬
    int nx = 1200;
    int ny = 600;

    int num_pixels = nx * ny;
    size_t fb_size = 3 * num_pixels * sizeof(float);

    // allocate FB
    float* fb;
    checkCudaErrors(cudaMallocManaged((void**)&fb, fb_size));
}
```

此調用在 GPU 上渲染圖像，並讓 CUDA 運行時將 GPU 上的工作劃分為 8×8 線程塊。您也可以嘗試其他適合您電腦的線程尺寸。我們應該嘗試找到符合以下條件的塊：
1. 一個小的方形塊，因此我們的程序工作很類似。這應該有助於每個像素完成相似數量的工作。如果塊中某些像素的工作時間比其他像素長得多，則該塊的效率會受到影響。
2. 的像素數是 32 的倍數，以便均勻地適應 [__Wrap__](https://developer.nvidia.com/blog/using-cuda-warp-level-primitives/) (這個我也不太清楚，可能要看這篇文章) 。

```c++
    int tx = 8;
    int ty = 8;
    ...
    // Render our buffer
    dim3 blocks(nx/tx+1,ny/ty+1);
    dim3 threads(tx,ty);
    render<<<blocks, threads>>>(fb, nx, ny);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());
```

由於本書代碼的編寫方式，我沒有選擇在 GPU 上將最終的浮點值轉換為 8 位分量。作為進一步的性能改進，您還可以選擇讓 GPU 將最終浮點值轉換為 8 位分量，從而在讀回數據時節省帶寬。

線程以塊的形式啟動，每個塊有 64 個線程運行內核函數渲染（注意 __global__ 標識符）。使用 threadIdx 和 blockIdx CUDA 內置變量，我們識別圖像 (i,j) 中每個線程的坐標，因此它知道如何計算最終顏色。對於大小不是塊大小倍數的圖像，有可能在圖像外部運行額外的線程。我們必須確保這些線程不會嘗試寫入幀緩衝區並提前返回。

回到 host (CPU)上，在 cudaDeviceSynchronize 之後，我們可以訪問 host 上的幀緩衝區以將圖像輸出到標準輸出。

```c++
__global__ void render(float *fb, int max_x, int max_y) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if((i >= max_x) || (j >= max_y)) return;
    int pixel_index = j*max_x*3 + i*3;
    fb[pixel_index + 0] = float(i) / max_x;
    fb[pixel_index + 1] = float(j) / max_y;
    fb[pixel_index + 2] = 0.2;
}
```

```c++
    // Output FB as Image
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            size_t pixel_index = j*3*nx + i*3;
            float r = fb[pixel_index + 0];
            float g = fb[pixel_index + 1];
            float b = fb[pixel_index + 2];
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    checkCudaErrors(cudaFree(fb));
```

完整代碼:

```c++
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <time.h>

// limited version of checkCudaErrors from helper_cuda.h in CUDA examples
#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )

void check_cuda(cudaError_t result, char const *const func, const char *const file, int const line) {
    if (result) {
        std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at " <<
            file << ":" << line << " '" << func << "' \n";
        // Make sure we call CUDA Device Reset before exiting
        cudaDeviceReset();
        exit(99);
    }
}

__global__ void render(float *fb, int max_x, int max_y) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if((i >= max_x) || (j >= max_y)) return;
    int pixel_index = j*max_x*3 + i*3;
    fb[pixel_index + 0] = float(i) / max_x;
    fb[pixel_index + 1] = float(j) / max_y;
    fb[pixel_index + 2] = 0.2;
}

int main() {
    int nx = 1200;
    int ny = 600;
    int tx = 8;
    int ty = 8;

    std::cerr << "Rendering a " << nx << "x" << ny << " image ";
    std::cerr << "in " << tx << "x" << ty << " blocks.\n";

    int num_pixels = nx*ny;
    size_t fb_size = 3*num_pixels*sizeof(float);

    // allocate FB
    float *fb;
    checkCudaErrors(cudaMallocManaged((void **)&fb, fb_size));

    clock_t start, stop;
    start = clock();
    // Render our buffer
    dim3 blocks(nx/tx+1,ny/ty+1);
    dim3 threads(tx,ty);
    render<<<blocks, threads>>>(fb, nx, ny);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());
    stop = clock();
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    std::cerr << "took " << timer_seconds << " seconds.\n";

    // Output FB as Image
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            size_t pixel_index = j*3*nx + i*3;
            float r = fb[pixel_index + 0];
            float g = fb[pixel_index + 1];
            float b = fb[pixel_index + 2];
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    checkCudaErrors(cudaFree(fb));
}

```

完成後，我們還將 cudaFree 幀緩衝區。您可以在此處將C++的代碼與CUDA的代碼進行比較。這樣，您應該會生成與 C++ 程序非常相似的結果。

![](pic/chapter01-1024x512.jpg)

