#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
// #include <map>
using namespace std;

typedef long long LL;
typedef long long int lli;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INF = 0x7f7f7f7f; // 最大值2139062143。用於代替INT_MAX 
const int N = 1e5 + 10; // 用於定義常量數組
#define MAXN ((int) 1e5) //
#define MAXM ((int) 1e5)
#define MAXPROD ((int) 1e5)

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int moves[4][2] = { {0,1},{1,0},{0,-1},{-1,0} }; // 4向移動
// int moves[8][2] = { {0,1},{1,0},{-1,0},{0,-1}, {1,1},{-1,1},{1,-1},{-1,-1} }; // 8向移動
// int moves[6][2] = { {0,1},{1,0},{1,-1},{0,-1},{-1,0},{-1,1} }; // 六邊移動 (網格六邊形專用)

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// static const int N = 1010; // 如题：二维数组大小的在3到1000范围内
int father[N];
int n; // 边的数量

// 并查集初始化
void ginit() {
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
    }
}

// 并查集里寻根的过程
int find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]);
}

// 判断 u 和 v是否找到同一个根
bool same(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

// 将v->u 这条边加入并查集
void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    father[v] = u;
}

int main()
{
    // 這裡是加速 cin，如果確定代碼沒有問題但又過不了，可以刪掉
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t; // 測試用例
    cin >> t;
    ginit(); // 并查集初始化
    for (int i = 0; i < t; ++i)
    {

    }
    return 0;
}