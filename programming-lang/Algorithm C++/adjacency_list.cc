#include <iostream>
#include <climits>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <cstring>
#include <stack>
#include <list>
#include <deque>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;

#define INF 1e9

class adjacency_list {
public:
    adjacency_list(int m, int n) : M(m), N(n), first(M, -1), next(N), u(N), v(N), w(N) {
        int a, b, c;
        for (int i = 0; i < N; i++) {
            cin >> a >> b >> c;
            u[i] = --a;
            v[i] = --b;
            w[i] = c;

            next[i] = first[u[i]];
            first[u[i]] = i;
        }
    }

    friend ostream &operator<<(ostream &os, const adjacency_list &a) {
        for (int i = 0; i < a.M; i++) {
            for (int k = a.first[i]; k != -1; k = a.next[k]) 
                os << a.u[k] << ' ' << a.v[k] << ' ' << a.w[k] << endl;
        }
        return os;
    }

    int M, N;
    vector<int> first, next, u, v, w;
};

int main() {
    
    int M, N;
    cin >> M >> N;
   
    adjacency_list A(M, N);
    cout << A << endl;

}

/*
4 5
1 4 9
2 4 6
1 2 5
4 3 8
1 3 7
*/