# 進階軟光柵-CUDA篇3

這裡介紹隨機或隨機確定的值。隨機數是 CUDA 的一個特殊主題，需要 cuRAND 庫。由於計算機上的“隨機數”實際上由偽隨機序列組成，因此我們需要為 GPU 上的每個線程設置和記住狀態。

為此，我們在主例程中為每個像素創建一個 d_rand_state 對象。

```c++
#include <curand_kernel.h>
...
   curandState *d_rand_state;
   checkCudaErrors(cudaMalloc((void **)&d_rand_state, num_pixels*sizeof(curandState)));
...
   render_init<<<blocks, threads>>>(nx, ny, d_rand_state);
   checkCudaErrors(cudaGetLastError());
   checkCudaErrors(cudaDeviceSynchronize());
   render<<<blocks, threads>>>(fb, nx, ny,  ns, d_camera, d_world, d_rand_state);
   checkCudaErrors(cudaGetLastError());
   checkCudaErrors(cudaDeviceSynchronize());
```

我們為每個線程初始化 rand_state。對於性能測量，我希望能夠將隨機初始化的時間與進行渲染的時間分開，所以我將其作為一個單獨的內核。您也可以選擇在渲染內核開始時執行此初始化。

```c++
__global__ void render_init(int max_x, int max_y, curandState *rand_state) {
   int i = threadIdx.x + blockIdx.x * blockDim.x;
   int j = threadIdx.y + blockIdx.y * blockDim.y;
   if((i >= max_x) || (j >= max_y)) return;
   int pixel_index = j*max_x + i;
   //Each thread gets same seed, a different sequence number, no offset
   curand_init(1984, pixel_index, 0, &rand_state[pixel_index]);
}
```

最後，我們將它傳遞給我們的渲染內核，製作一個本地副本並在每個線程中使用它。用 curand_uniform(&local_rand_state) 替換任何 drand48() 調用。

```c++
__global__ void render(vec3 *fb, int max_x, int max_y, int ns, camera **cam, hitable **world, curandState *rand_state) {
   int i = threadIdx.x + blockIdx.x * blockDim.x;
   int j = threadIdx.y + blockIdx.y * blockDim.y;
   if((i >= max_x) || (j >= max_y)) return;
   int pixel_index = j*max_x + i;
   curandState local_rand_state = rand_state[pixel_index];
   vec3 col(0,0,0);
   for(int s=0; s < ns; s++) {
      float u = float(i + curand_uniform(&local_rand_state)) / float(max_x);
      float v = float(j + curand_uniform(&local_rand_state)) / float(max_y);
      ray r = (*cam)->get_ray(u,v);
      col += color(r, world);
   }
   fb[pixel_index] = col/float(ns);
}
```

# Iteration vs. Recursion
顏色函數的默認轉換會導致堆棧溢出，因為它可以多次調用自身。但是，代碼可以簡單地轉換為循環而不是遞歸。事實上，本書後面的代碼限制了 50 級遞歸，所以我們只是在前面幾章添加了這個限制。

原始 C++ 代碼如下所示，您可以看到 world->hit 是否返回 true，函數會重複出現。

```c++
vec3 color(const ray& r, hitable *world) {
   hit_record rec;
   if (world->hit(r, 0.001, MAXFLOAT, rec)) {
      vec3 target = rec.p + rec.normal + random_in_unit_sphere();
      return 0.5*color( ray(rec.p, target-rec.p), world);
   }
   else {
      vec3 unit_direction = unit_vector(r.direction());
      float t = 0.5*(unit_direction.y() + 1.0);
      return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
   }
}
```

將其翻譯成 CUDA ：

```c++
__device__ vec3 color(const ray& r, hitable **world, curandState *local_rand_state) {
   ray cur_ray = r;
   float cur_attenuation = 1.0f;
   for(int i = 0; i < 50; i++) {
      hit_record rec;
      if ((*world)->hit(cur_ray, 0.001f, FLT_MAX, rec)) {
         vec3 target = rec.p + rec.normal + random_in_unit_sphere(local_rand_state);
         cur_attenuation *= 0.5f;
         cur_ray = ray(rec.p, target-rec.p);
      }
      else {
           vec3 unit_direction = unit_vector(cur_ray.direction());
           float t = 0.5f*(unit_direction.y() + 1.0f);
           vec3 c = (1.0f-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
           return cur_attenuation * c;
        }
      }
   return vec3(0.0,0.0,0.0); // exceeded recursion
}
```