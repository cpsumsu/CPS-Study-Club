#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <string>
#include <cstring>
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

int n, m;

#define MAXN ((int) 1e5)
#define MAXM ((int) 1e5)
#define MAXPROD ((int) 1e5)

string map[MAXN + 10];
vector<int> A[MAXN + 10];
int degree[MAXPROD + 10];
bool visited[MAXPROD + 10];

int next(int t)
{
	int i = t / m, j = t % m, ii = i, jj = j;
	if (map[i][j] == 'u') ii -= A[i][j];
	else if (map[i][j] == 'd') ii += A[i][j];
	else if (map[i][j] == 'l') jj -= A[i][j];
	else jj += A[i][j];
	if (ii < 0 || jj < 0 || ii >= n || jj >= m) return -1;
	return ii * m + jj;
}

bool isok(int t)
{
	for (; t >= 0 && !visited[t]; t = next(t)) visited[t] = true;
	for (int i = 0; i < n * m; ++i) if (!visited[i]) return false;
	return true;
}

void p()
{
	cin >> n >> m;
	memset(degree, 0, sizeof(int) * (n * m + 3));
	memset(visited, 0, sizeof(bool) * (n * m + 3));
	for (int i = 0; i < n; i++) map[i].clear(), A[i].clear();
	for (int i = 0; i < n; ++i)
		cin >> map[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			int tmp;
			cin >> tmp;
			A[i].push_back(tmp);
		}
	for (int i = 0, t = 0; i < n; ++i)
		for (int j = 0; j < m; j++, t++)
			degree[next(t)]++;
	for (int t = 0; t < n * m; t++)
	{
		if (degree[t] == 0)
		{
			if (isok(t)) printf("Yes\n");
			else printf("No\n");
			return;
		}
	}
	if (isok(0)) printf("Yes\n");
	else printf("No\n");
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i)
	{
		p();
	}
	return 0;
}