#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <set>
#include <cstring>
#include <stack>
#include <list>
#include <deque>
#include <cmath>
#include <climits>
#include <algorithm>
#include <numeric>
using namespace std;

template<typename A, typename B> ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &con) { for (const auto &it : con) { cout << it << ' '; } return os; }

template<typename T_vector>
void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {
    if (start < 0) start = 0;
    if (end < 0) end = int(v.size());

    for (int i = start; i < end; i++) {
        cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');
    }
}

void run_case() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int tests;
    cin >> tests;
    while (tests-- > 0)
        run_case();
    
    return 0;
}