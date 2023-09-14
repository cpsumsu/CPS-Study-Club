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

const int N = 1e5 + 10;
char s[N];
int nex[N];

void p()
{
	// cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int n;
	cin >> n;
	scanf("%s", s + 1);
	for (int i = 2, j = 0; i <= n; i++) {
		while (j && s[i] != s[j + 1]) 
			j = nex[j];
		if (s[i] == s[j + 1]) j++;
		nex[i] = j;
	}
	for (int i = 1; i <= n; i++) {
		if (nex[i] != 0) {
			printf("Wrong Answer");
			return;
		}
	}
	printf("Correct");
	return;
}

int main()
{
	p();
	return 0;
}