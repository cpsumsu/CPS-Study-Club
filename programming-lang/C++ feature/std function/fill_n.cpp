// #back_inserter #fill() #fill_n()
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

ostream &operator<<(ostream &os, vector<int> &p) {
    for (auto x : p)
        os << x << ' ';
}

int main() {
    vector<int> v1 {1, 2, 3};
    fill(v1.begin(), v1.end(), 1);
    cout << "v1: " << v1 << endl;

    vector<int> v2 {1, 2, 3};
    fill_n(v2.begin(), 2, 2);
    cout << "v2: " << v2 << endl;

    vector<int> v3;
    auto it = back_inserter(v3);
    fill_n(it, 3, 10);
    cout << "v3: " << v3 << endl;
    return 0;
}