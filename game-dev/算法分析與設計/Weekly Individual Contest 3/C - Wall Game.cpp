#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <map>
using namespace std;

typedef long long LL;
typedef long long int lli;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INF = 0x7f7f7f7f; // 最大值2139062143。用於代替INT_MAX 
const int N = 5e5 + 10; // 用於定義常量數組
#define MAXN ((int) 1e5) // 用於定義常量數組
#define MAXM ((int) 1e5)
#define MAXPROD ((int) 1e5)
lli var1, var2;
#define rep(i, l, u) for (lli i = l; i <= u; i++)

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

map<PII, LL> mp;
LL ans[N];
LL tot = 0;

// 六邊
int moves[6][2] = { {0,1},{1,0},{1,-1},{0,-1},{-1,0},{-1,1} };

void solve(PII t)
{
    ans[mp[t]] = 6; // 六邊
    for (auto v : moves)
    {
        LL x = t.first + v[0], y = t.second + v[1];
        PII cur = make_pair(x, y);
        if (mp[cur]) // 如果已經存在地塊
        {
            LL a = find(mp[t]), b = find(mp[cur]);
            if (a != b) // 如果祖先不同，則合併地塊father。並維護ans
            {
                father[a] = b;
                ans[b] += ans[a] - 2;
            }
            else ans[b] -= 2; // 如果連通即牆-2
        }
    }
}

int main()
{
    // 這裡是加速 cin，如果確定代碼沒有問題但又過不了，可以刪掉
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t; // 測試用例
    cin >> t;
    n = t;
    ginit(); // 并查集初始化
    for (int i = 0; i < t; ++i)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
        {
            PII t = make_pair(x, y);
            mp[t] = ++tot;
            solve(t);
        }
        else if (op == 2)
        {
            PII t = make_pair(x, y);
            printf("%lld\n", ans[find(mp[t])]);
        }
    }
    return 0;
}