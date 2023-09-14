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
lli var1, var2;
#define rep(i, l, u) for (lli i = l; i <= u; i++)

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int A[N];
vector<vector<int>> g;
int m, n;
// 建圖模版１ init graph 無向邊
void initg(int i, int j)
{
	g[i].push_back(j);
	g[j].push_back(i);
}

int main()
{
	// 這裡是加速 cin，如果確定代碼沒有問題但又過不了，可以刪掉
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int t; // 測試用例
	cin >> t;
	for (int i = 0; i < t; ++i)
	{

	}
	return 0;
}