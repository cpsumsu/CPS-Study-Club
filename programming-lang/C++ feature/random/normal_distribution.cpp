#include <iostream>
#include <vector>
using namespace std;

#include <random>

int main() {
    
    default_random_engine e;
    normal_distribution<double> n(4, 1.5);
    vector<size_t> vals(9);

    for (int i = 0; i < 300; i++) {
        size_t v = lround(n(e));
        if (v < vals.size())
            ++vals[v];
    }
    for (size_t j = 0; j != vals.size(); j++)
        cout << j << ": " << string(vals[j], '*') << endl;
    
    return 0;
}