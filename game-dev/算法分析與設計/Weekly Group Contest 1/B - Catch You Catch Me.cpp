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

int moves[4][2] = { {0,1},{1,0},{0,-1},{-1,0} }; // 4向移動 順時針
// int moves[8][2] = { {0,1},{1,0},{-1,0},{0,-1}, {1,1},{-1,1},{1,-1},{-1,-1} }; // 8向移動
// int moves[6][2] = { {0,1},{1,0},{1,-1},{0,-1},{-1,0},{-1,1} }; // 六邊移動 (網格六邊形專用)

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

// 檢查是否是質數
bool isprime(int x)
{
	if (x < 2) return false;
	for (int i = 2; i * i <= x; ++i)
		if (x % i == 0) return false;
	return true;
}

// 檢查是否是回文數、回文串
bool ok(int i)
{
	string s = to_string(i);
	int n = s.size();
	for (int i = 0; i < n; ++i)
		if (s[i] != s[n - 1 - i]) return false;
	return true;
}

vector<vector<int>> g;
vector<bool> vis;
vector<int> ans;

void dfs(int cur)
{
	vis[cur] = true;
	bool noF = true;
	for (int i = 0; i < g[cur].size(); ++i)
	{
		int a = g[cur][i];
		if (vis[a]) 
			continue;
		noF = false;
		dfs(a);
		ans[cur] = max(ans[cur], ans[a] + 1);
	}
	if (noF)
	{
		ans[cur] = 1;
	}
}

int main()
{
	// 這裡是加速 cin，如果確定代碼沒有問題但又過不了，可以刪掉
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n; // 測試用例
	cin >> n;
	g.resize(N);
	vis.resize(N, false);
	ans.resize(N);
	for (int i = 0; i < n - 1; ++i)
	{
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	if (g[1].size() == 0)
	{
		cout << 0 << endl;
	}
	else
	{
		int s = 0;
		dfs(1);
		for (int i = 0; i < g[1].size(); ++i)
		{
			// cout << g[cur][i] << " ";
			s += ans[g[1][i]];
		}
		cout << s << endl;
	}
	return 0;
}