class undirected_matrix {
public:
    int M, N;
    vector<vector<int>> graph;

    undirected_matrix(int m, int n) : M(m), N(n), graph(M, vector<int>(M)) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                if (i == j)
                    graph[i][j] = 0;
                else 
                    graph[i][j] = INF;
            }
        }

        int a, b, c;
        for (int i = 0; i < N; i++) {
            cin >> a >> b >> c;
            --a; --b;
            graph[a][b] = c;
            graph[b][a] = c;
        }
    }

    friend ostream &operator<<(ostream &os, const undirected_matrix &matrix) {
        for (int i = 0; i < matrix.M; i++) {
            for (int j = 0; j < matrix.M; j++) {
                if (matrix.graph[i][j] == INF)
                    os << 99 << ' ';
                else
                    os << setw(2) << matrix.graph[i][j] << ' ';
            }
            os << endl;
        }

        return os;
    }
};

