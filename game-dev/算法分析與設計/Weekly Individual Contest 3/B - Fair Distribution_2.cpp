#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
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
#define MAXN ((int) 1e5) //
#define MAXM ((int) 1e5)
#define MAXPROD ((int) 1e5)
lli var1, var2;
#define rep(i, l, u) for (lli i = l; i <= u; i++)

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
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
		int n, m;
		cin >> n >> m;
		int k = 1e4;
		int ans = INF;
		for (int i = 1; i <= k; ++i)
		{
			int x = (m + i - 1) / i; // 從 m 開始到 m + k 找x。x少於等於n
			// 8 20
			// 如果 i <= n 即有 1 <= 8: 3 - 1 + 20 * i - 20 = 2
			if (i <= n) ans = min(ans, n - i + x * i - m);
			// x少於等於n
			if (x <= n) ans = min(ans, n - x + x * i - m);
		}
		printf("%d\n", ans);
	}
	return 0;
}