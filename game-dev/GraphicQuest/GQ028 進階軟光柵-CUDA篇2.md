# 進階軟光柵-CUDA篇2
# vec3.h 向量類
之前我們寫了個向量類。為此，我們使用 __host__ __device__ 關鍵字註釋所有 vec3 類成員函數，以便我們可以在 GPU 和 CPU 上執行它們。

```c++
class vec3  {
public:
// __host__ = CPU , __device__ = GPU
     __host__ __device__ vec3() {}
     __host__ __device__ vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
     __host__ __device__ inline float x() const { return e[0]; }
     __host__ __device__ inline float y() const { return e[1]; }
     __host__ __device__ inline float z() const { return e[2]; }
```

在除 operator>> 和 operator<< 方法之外的所有方法之前使用這些 __host__ __device__ 關鍵字。

鑑於此類，您可以更新 main.cu 代碼以訪問由 vec3 而不是 3 個浮點數組成的 FB，類似於 C++ 代碼。

那麼，重改寫我們的vec3類吧:

```c++
// vec3.h
#ifndef VEC3H
#define VEC3H

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {
public:
	__host__ __device__ vec3() {}
	__host__ __device__ vec3(float e0, float e1, float e2) { e[0] = e0, e[1] = e1, e[2] = e2; }

	__host__ __device__ inline float x() const { return e[0]; }
	__host__ __device__ inline float y() const { return e[1]; }
	__host__ __device__ inline float z() const { return e[2]; }
	// 多寫一個rgb以備不時之需
     // 這裡以後會改寫 main.cu 中的rgb函數返回值
	// float r = fb[pixel_index + 0];
	// float g = fb[pixel_index + 1];
	// float b = fb[pixel_index + 2];
	__host__ __device__ inline float r() const { return e[0]; }
	__host__ __device__ inline float g() const { return e[1]; }
	__host__ __device__ inline float b() const { return e[2]; }

	// 之前沒有寫 operator+()，這次多寫一個
	__host__ __device__ inline const vec3& operator+() const { return *this; }
	// 負向量
	__host__ __device__ inline vec3 operator-() const { return vec3(-e[0], -e[1], e[2]); }
	__host__ __device__ inline float operator[](int i) const { return e[i]; }
	__host__ __device__ inline float& operator[](int i) { return e[i]; }

	// +-*/
	__host__ __device__ inline vec3& operator+=(const vec3& v2);
	__host__ __device__ inline vec3& operator-=(const vec3& v2);
	__host__ __device__ inline vec3& operator*=(const vec3& v2);
	__host__ __device__ inline vec3& operator/=(const vec3& v2);
	__host__ __device__ inline vec3& operator*=(const float t);
	__host__ __device__ inline vec3& operator/=(const float t);

	// 向量長度
	__host__ __device__ inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	// 向量xyz平方和
	__host__ __device__ inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	// 如果向量在所有維度上都非常接近於零，則返回 true。
	__host__ __device__ inline bool near_zero() const
	{
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}
	__host__ __device__ inline void make_unit_vector();
	
public:
	// 這裡使用的是flaot，因為double會消耗2~3倍的時間
     // 我們需要小心檢查雙精度代碼。當前的 GPU 在以單精度進行計算時運行速度最快。在某些 GPU 上，雙精度計算可能會慢幾倍。例如，這可能看起來像一個單精度計算：

     // float t = 0.5*(unit_direction.y() + 1.0);

     // 但是，此代碼將以雙精度計算乘法和加法。雖然 unit_direction.y() 結果是浮點數，但由於浮點常量 0.5 和 1.0 是雙精度值，因此浮點值被上轉換為數學運算的雙精度值。只有將結果寫入 t 時，才會轉換為單精度。要強制執行單精度數學運算，您需要強制這些常量浮動。請注意，vec3() 構造函數會在不進行任何計算的情況下強制值浮動，因此您無需更改這些值。
	float e[3];
};


// 通用函數列表

// 輸出向量e1e2e3
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
// 多寫一個
inline std::istream& operator>>(std::istream& in, vec3& v) {
	return in >> v.e[0] >> v.e[1] >> v.e[2];
}

__host__ __device__ inline void vec3::make_unit_vector() {
	float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k; e[1] *= k; e[2] *= k;
}

// 向量與向量的+-*/

__host__ __device__ inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

__host__ __device__ inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

__host__ __device__ inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

__host__ __device__ inline vec3 operator/(const vec3& v1, const vec3& v2) {
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

// 乘以常數

__host__ __device__ inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

__host__ __device__ inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

__host__ __device__ inline vec3 operator/(vec3 v, double t)
{
	return (1 / t) * v;
}

// 點乘
__host__ __device__ inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// 外積 
// https://zh.wikipedia.org/zh-tw/%E5%8F%89%E7%A7%AF
__host__ __device__ inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

__host__ __device__ inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}


////// 統一放在外面
// 向量加法
__host__ __device__ inline vec3& vec3::operator+=(const vec3& v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}
// 向量減法
__host__ __device__ inline vec3& vec3::operator-=(const vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}
// 向量與向量相乘
__host__ __device__ inline vec3& vec3::operator*=(const vec3& v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}
// 向量與向量相除
__host__ __device__ inline vec3& vec3::operator/=(const vec3& v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}
// 向量乘法
__host__ __device__ inline vec3& vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}
__host__ __device__ inline vec3& vec3::operator/=(const float t)
{
	return *this *= 1 / t;
}

#endif
```

# 對 GPU 進行分類
# ray class
本書中介紹的其餘 C++ 類僅在 GPU 上使用，因此我們僅使用 __device__ 關鍵字對它們進行註釋。這裡我們改寫 ray class 射線類。

```c++
#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray {
public:
    __device__ ray() {}
    __device__ ray(const vec3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    __device__ vec3 origin() const { return orig; }
    __device__ vec3 direction() const { return dir; }

    // at ---> point_at_parameter
    __device__ vec3 point_at_parameter(double t) const {
        return orig + t * dir;
    }

public:
    // 原先這裡是:
    // point3 orig;
    // vec3 dir;

    // 統一使用 vec3 (因為它們的結構都一樣)
    vec3 orig;
    vec3 dir;
};

#endif // !RAYH

```

回到我們的 main.cu 中，您還需要將 __device__ 關鍵字添加到 color 顏色函數，因為它是從渲染內核調用的。


```c++
__device__ vec3 color(const ray& r) {
   vec3 unit_direction = unit_vector(r.direction());
   float t = 0.5f*(unit_direction.y() + 1.0f);
   return (1.0f-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

__global__ void render(vec3 *fb, int max_x, int max_y, vec3 lower_left_corner, vec3 horizontal, vec3 vertical, vec3 origin) {
   int i = threadIdx.x + blockIdx.x * blockDim.x;
   int j = threadIdx.y + blockIdx.y * blockDim.y;
   if((i >= max_x) || (j >= max_y)) return;
   int pixel_index = j*max_x + i;
   float u = float(i) / float(max_x);
   float v = float(j) / float(max_y);
   ray r(origin, lower_left_corner + u*horizontal + v*vertical);
   fb[pixel_index] = color(r);
}
```

這裡是完整代碼:

```c++
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>
#include <time.h>

#include "vec3.h"
#include "ray.h"

// limited version of checkCudaErrors from helper_cuda.h in CUDA examples
#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )

void check_cuda(cudaError_t result, char const* const func, const char* const file, int const line) {
    if (result) {
        std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at " <<
            file << ":" << line << " '" << func << "' \n";
        // Make sure we call CUDA Device Reset before exiting
        cudaDeviceReset();
        exit(99);
    }
}

__device__ vec3 color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}


// float fb ---> vec3 fb
__global__ void render(vec3* fb, int max_x, int max_y,
    vec3 lower_left_corner, vec3 horizontal, vec3 vertical, vec3 origin
) 
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if ((i >= max_x) || (j >= max_y)) return;
    // 注意不要*3!!!
    int pixel_index = j * max_x + i;

    float u = float(i) / float(max_x);
    float v = float(j) / float(max_y);

    ray r(origin, lower_left_corner + u * horizontal + v * vertical);
    fb[pixel_index] = color(r);
}

int main()
{
    // 長寬
    int nx = 1200;
    int ny = 600;
    int tx = 8;
    int ty = 8;

    std::cerr << "Rendering a " << nx << "x" << ny << " image ";
    std::cerr << "in " << tx << "x" << ty << " blocks.\n";

    int num_pixels = nx * ny;
    // 由於我們的fb 改用了 vec3，因此再也不用*3
    size_t fb_size = num_pixels * sizeof(vec3);

    // allocate FB
    vec3* fb;
    checkCudaErrors(cudaMallocManaged((void**)&fb, fb_size));
    
    clock_t start, stop;
    start = clock();

    // Render our buffer
    dim3 blocks(nx / tx + 1, ny / ty + 1);
    // 8 * 8
    dim3 threads(tx, ty);
    // 固定寫法
    render<<<blocks, threads >>>(fb, nx, ny,
        vec3(-2.0, -1.0, -1.0),
        vec3(4.0, 0.0, 0.0),
        vec3(0.0, 2.0, 0.0),
        vec3(0.0, 0.0, 0.0)
        );
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());
    stop = clock();
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    std::cerr << "took " << timer_seconds << " seconds.\n";

    // Output FB as Image
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            size_t pixel_index = j * nx + i;
            int ir = int(255.99 * fb[pixel_index + 0].r());
            int ig = int(255.99 * fb[pixel_index + 1].g());
            int ib = int(255.99 * fb[pixel_index + 2].b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    checkCudaErrors(cudaFree(fb));

}
```

# Hit the Sphere 球體
其實只需要加上 \__device__ 就可以了

```c++
__device__ bool hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0f * a * c;
    return (discriminant > 0.0f);
}

__device__ vec3 color(const ray& r)
{
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
        return vec3(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
```

# Manage Your Memory
新主題介紹了我們如何在 CPU 和 GPU 上處理 CUDA C++ 類的內存管理。我們將在 GPU 上分配場景的對象，這需要兩段代碼。

首先，我們分配一個 d_list of hitables 和一個 d_world 來在 CPU 的主例程中保存這些對象。（d_ 前綴僅用於 device 數據。）接下來，我們調用 create_world Kernel 來構造這些對象。

```c++
    hitable **d_list;
checkCudaErrors(cudaMalloc((void **)&amp;d_list, 2*sizeof(hitable *)));
   hitable **d_world;
   checkCudaErrors(cudaMalloc((void **)&amp;d_world, sizeof(hitable *)));
   create_world&lt;&lt;&lt;1,1&gt;&gt;&gt;(d_list,d_world);
   checkCudaErrors(cudaGetLastError());
   checkCudaErrors(cudaDeviceSynchronize());
```

在 Kernel 中，我們確保只執行一次世界的構建

```c++
__global__ void create_world(hitable **d_list, hitable **d_world) {
    if (threadIdx.x == 0 && blockIdx.x == 0) {
        *(d_list)   = new sphere(vec3(0,0,-1), 0.5);
        *(d_list+1) = new sphere(vec3(0,-100.5,-1), 100);
        *d_world    = new hitable_list(d_list,2);
    }
}
```

要使用這個世界，我們將它傳遞給我們的渲染內核和顏色函數，以及描述我們相機的值

```c++
render<<<blocks, threads>>>(fb, nx, ny,
                            vec3(-2.0, -1.0, -1.0),
                            vec3(4.0, 0.0, 0.0),
                            vec3(0.0, 2.0, 0.0),
                            vec3(0.0, 0.0, 0.0),
                            d_world);
```

還有 kernels

```c++
__global__ void render(vec3 *fb, int max_x, int max_y,vec3 lower_left_corner, vec3 horizontal, vec3 vertical, vec3 origin, hitable **world)
{
   int i = threadIdx.x + blockIdx.x * blockDim.x;
   int j = threadIdx.y + blockIdx.y * blockDim.y;
   if((i >= max_x) || (j >= max_y)) return;
   int pixel_index = j*max_x + i;
   float u = float(i) / float(max_x);
   float v = float(j) / float(max_y);
   ray r(origin, lower_left_corner + u*horizontal + v*vertical);
   fb[pixel_index] = color(r, world);
}

__device__ vec3 color(const ray& r, hitable **world) {
   hit_record rec;
   if ((*world)->hit(r, 0.0, FLT_MAX, rec)) {
      return 0.5f*vec3(rec.normal.x()+1.0f, rec.normal.y()+1.0f, rec.normal.z()+1.0f);
   }
   else {
      vec3 unit_direction = unit_vector(r.direction());
      float t = 0.5f*(unit_direction.y() + 1.0f);
      return (1.0f-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
   }
}
```

完成後，我們構建的內容必須刪除；在 main 的末尾，您可以看到：

```c++
checkCudaErrors(cudaDeviceSynchronize());
free_world<<<1,1>>>(d_list,d_world);
checkCudaErrors(cudaGetLastError());
checkCudaErrors(cudaFree(d_list));
checkCudaErrors(cudaFree(d_world));
checkCudaErrors(cudaFree(fb));
```

free_world():

```c++
__global__ void free_world(hitable **d_list, hitable **d_world) {
   delete *(d_list);
   delete *(d_list+1);
   delete *d_world;
}
```

此外，還有 hitable.h、hitable_list.h 和 sphere.h 文件，它們都具有從 GPU 調用的類和方法，因此它們需要 __device__ 註釋。最後，還有浮點常量和數學需要注意。

```c++
// hitable.h
#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
};

class hitable  {
    public:
        __device__ virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif

```

```c++
// hitable_list.h
#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list: public hitable  {
    public:
        __device__ hitable_list() {}
        __device__ hitable_list(hitable **l, int n) {list = l; list_size = n; }
        __device__ virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        hitable **list;
        int list_size;
};

__device__ bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
        hit_record temp_rec;
        bool hit_anything = false;
        float closest_so_far = t_max;
        for (int i = 0; i < list_size; i++) {
            if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
}

#endif

```

```c++
// sphere.h
#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable  {
    public:
        __device__ sphere() {}
        __device__ sphere(vec3 cen, float r) : center(cen), radius(r)  {};
        __device__ virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
};

__device__ bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}


#endif

```

完整代碼:

```c++
// main.cu
#include <iostream>
#include <time.h>
#include <float.h>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"

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

__device__ vec3 color(const ray& r, hitable **world) {
    hit_record rec;
    if ((*world)->hit(r, 0.0, FLT_MAX, rec)) {
        return 0.5f*vec3(rec.normal.x()+1.0f, rec.normal.y()+1.0f, rec.normal.z()+1.0f);
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f*(unit_direction.y() + 1.0f);
        return (1.0f-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

__global__ void render(vec3 *fb, int max_x, int max_y,
                       vec3 lower_left_corner, vec3 horizontal, vec3 vertical, vec3 origin,
                       hitable **world) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;
    if((i >= max_x) || (j >= max_y)) return;
    int pixel_index = j*max_x + i;
    float u = float(i) / float(max_x);
    float v = float(j) / float(max_y);
    ray r(origin, lower_left_corner + u*horizontal + v*vertical);
    fb[pixel_index] = color(r, world);
}

__global__ void create_world(hitable **d_list, hitable **d_world) {
    if (threadIdx.x == 0 && blockIdx.x == 0) {
        *(d_list)   = new sphere(vec3(0,0,-1), 0.5);
        *(d_list+1) = new sphere(vec3(0,-100.5,-1), 100);
        *d_world    = new hitable_list(d_list,2);
    }
}

__global__ void free_world(hitable **d_list, hitable **d_world) {
    delete *(d_list);
    delete *(d_list+1);
    delete *d_world;
}

int main() {
    int nx = 1200;
    int ny = 600;
    int tx = 8;
    int ty = 8;

    std::cerr << "Rendering a " << nx << "x" << ny << " image ";
    std::cerr << "in " << tx << "x" << ty << " blocks.\n";

    int num_pixels = nx*ny;
    size_t fb_size = num_pixels*sizeof(vec3);

    // allocate FB
    vec3 *fb;
    checkCudaErrors(cudaMallocManaged((void **)&fb, fb_size));

    // make our world of hitables
    hitable **d_list;
    checkCudaErrors(cudaMalloc((void **)&d_list, 2*sizeof(hitable *)));
    hitable **d_world;
    checkCudaErrors(cudaMalloc((void **)&d_world, sizeof(hitable *)));
    create_world<<<1,1>>>(d_list,d_world);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());

    clock_t start, stop;
    start = clock();
    // Render our buffer
    dim3 blocks(nx/tx+1,ny/ty+1);
    dim3 threads(tx,ty);
    render<<<blocks, threads>>>(fb, nx, ny,
                                vec3(-2.0, -1.0, -1.0),
                                vec3(4.0, 0.0, 0.0),
                                vec3(0.0, 2.0, 0.0),
                                vec3(0.0, 0.0, 0.0),
                                d_world);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaDeviceSynchronize());
    stop = clock();
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    std::cerr << "took " << timer_seconds << " seconds.\n";

    // Output FB as Image
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            size_t pixel_index = j*nx + i;
            int ir = int(255.99*fb[pixel_index].r());
            int ig = int(255.99*fb[pixel_index].g());
            int ib = int(255.99*fb[pixel_index].b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    // clean up
    checkCudaErrors(cudaDeviceSynchronize());
    free_world<<<1,1>>>(d_list,d_world);
    checkCudaErrors(cudaGetLastError());
    checkCudaErrors(cudaFree(d_list));
    checkCudaErrors(cudaFree(d_world));
    checkCudaErrors(cudaFree(fb));

    // useful for cuda-memcheck --leak-check full
    cudaDeviceReset();
}

```
