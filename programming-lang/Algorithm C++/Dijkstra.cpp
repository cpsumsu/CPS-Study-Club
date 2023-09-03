#include <iostream>
#include <vector>
using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &p) { for (auto x : p) os << x << ' '; return os; }

#define INF 99

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

vector<int> dijkstra(vector<vector<int>> &A) {
    int M = A.size();
    vector<int> dist(M);
    vector<bool> visit(M, false);
    visit[0] = true;

    for (int i = 0; i < M; i++)
        dist[i] = A[0][i];

    int u;
    for (int i = 0; i < M - 1; i++) {
        int min = INF;
        for (int j = 0; j < M; j++) {
            if (visit[j] == 0 && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        visit[u] = true;
        for (int v = 0; v < M; v++) {
            if (A[u][v] != INF) {
                if (dist[v] > dist[u] + A[u][v])
                    dist[v] = dist[u] + A[u][v];
            }
        }
    }

    return dist;
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    adjacency_matrix A(vertices, edges);

    cout << dijkstra(A.graph);

    return 0;
}

/*
6 9
1 2 1
1 3 12
2 3 9
2 4 3
3 5 5
4 3 4
4 5 13
4 6 15
5 6 4
*/