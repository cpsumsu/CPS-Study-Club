#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <cstring>
#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef long long LL;
typedef long long int lli;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INF = 0x7f7f7f7f; // 最大值2139062143。用於代替INT_MAX 
const int N = 1e5 + 10; // 用於定義常量數組
#define MAXN ((int) 1e5) // 用於定義常量數組
#define MAXM ((int) 1e5)
#define MAXPROD ((int) 1e5)
lli var1, var2;
#define rep(i, l, u) for (lli i = l; i <= u; i++)

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int A[N], h[N], d[N];
vector<vector<int>> g;
int m, n, t;
LL dp[N];
// 建圖模版: init graph 無向邊
void initg(int i, int j)
{
	g[i].push_back(j);
	g[j].push_back(i);
}

void bfs()
{
	memset(d, 0x7f, sizeof(d));
	queue<int> q;
	q.push(1);
	d[1] = 0;
	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		for (auto v : g[t])
		{
			if (d[v] != INF) continue;
			d[v] = d[t] + 2;
			q.push(v);
		}
	}
}

void p()
{
	memset(h, -1, sizeof(h));
	cin >> n >> m >> t;
	g.resize(MAXN);
	for (int i = 2; i <= n; ++i) cin >> A[i];
	for (int i = 0; i < m ; ++i)
	{
		int x, y; 
		cin >> x >> y;
		initg(x, y);
	}
	bfs();
	for (int i = 1; i <= n; ++i)
		for (int j = d[i]; j <= t; ++j)
			dp[j] = max(dp[j], dp[j - d[i]] + A[i]);
	for (int i = 1; i <= t; ++i)
		cout << dp[i] << " ";
	cout << endl;
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	//int t; // 測試用例
	//cin >> t;
	//for (int i = 0; i < t; ++i)
	//{

	//}
	p();
	return 0;
}