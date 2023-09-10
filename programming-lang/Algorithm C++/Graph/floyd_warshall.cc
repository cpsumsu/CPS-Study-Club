#include <iostream>
#include <climits>
#include <vector>
using namespace std;

ostream &operator<<(ostream &os, vector<int> &m) {
    for (auto &x : m)
        os << x << ' ';
    return os;
}

#define INF 99

void print_matrix(vector<vector<int>> &m) {
    for (auto &x : m)
        cout << setw(2) << x << endl;
    cout << endl;
}

void floyd_warshall(vector<vector<int>> &map) {
    int N = map.size();

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i][k] < INF && map[k][j] < INF && map[i][j] > map[i][k] + map[k][j])
                    map[i][j] = map[i][k] + map[k][j];
            }
        }
    }
}

int main() {
    
    int vertice, edge;
    cin >> vertice >> edge;

    // initialization 
    vector<vector<int>> map(vertice, vector<int>(vertice, INF));
    for (int i = 0; i < vertice; i++) {
        for (int j = 0; j < vertice; j++) {
            if (i == j) map[i][j] = 0;
        }
    }

    int a, b, c;
    for (int i = 0; i < edge; i++) {
        cin >> a >> b >> c;
        map[a - 1][b - 1] = c;
    }


    print_matrix(map);
    
    floyd_warshall(map);

    print_matrix(map);

    return 0;
}