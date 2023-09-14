#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <string>
using namespace std;

typedef long long LL;
typedef long long int lli;
typedef unsigned long long ull;
lli var1, var2;
#define rep(i, l, u) for (lli i = l; i <= u; i++)


template <typename T>
T mmax(const T& lhs, const T& rhs)
{
	return lhs > rhs ? lhs : rhs;
}

template <typename T>
T mmin(const T& lhs, const T& rhs)
{
	return lhs < rhs ? lhs : rhs;
}

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	string s;
	vector<bool> a(7);
	for (int i = 1; i <= 6; ++i)
	{
		cin >> s;
		if (s == "true") a[i] = true;
		else a[i] = false;
	}
	int ans = 4;
	// 基本狀況
	ans += a[1] == a[4];
	ans += a[2] == a[5];
	ans += a[3] == a[6];
	// 第三圈(當三個圈都交叉了)
	if (ans == 7)
	{
		ans += a[1] && a[4] && !a[3] && !a[6];
		ans += !a[1] && !a[2] && !a[4] && !a[5];
		ans += a[2] && a[3] && a[5] && a[6];
	}
	printf("%d\n", ans);

	return 0;
}