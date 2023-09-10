#include <iostream>
#include <vector>
#include <numeric>      // std::numeric_limits<int>::max()
#include <iomanip>      // std::setw()
using namespace std;

#define INF 1e9         // usually INF = INT_MAX or std::numeric_limits<int>::max()

class adjacency_matrix {
public:
    adjacency_matrix(int m, int n) : M(m), N(n), graph(M, vector<int>(M)) {
        // initialize matrix
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (i == j)
                    graph[i][j] = 0;
                else
                    graph[i][j] = INF;
            }
        }

        // input edge
        for (int i = 0; i < N; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            graph[a - 1][b - 1] = c;
        }
    }

    // print the matrix
    friend ostream &operator<<(ostream &os, const adjacency_matrix &matrix) {
        for (auto &i : matrix.graph) {
            for (auto &j : i) {
                if (j == 1e9)
                    os << 99 << ' ';
                else
                    os << setw(2) << j << ' ';
            }
            os << endl;
        }
        return os;
    }

    int M, N;       // vertice and edge
    vector<vector<int>> graph;
};

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    adjacency_matrix A(vertices, edges);

    cout << A << endl;
}

/*
5 5 
2 3 2
1 2 -3
1 5 5
4 5 2
3 4 3
*/