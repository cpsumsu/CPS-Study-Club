// #find() #find_if() #find_if_not() #callable 
// demonstration of callable object, lambda expression, function pointer in std::find() ......
#include <iostream>
#include <algorithm>            // find(begin, end, target), find_if(begin, end, unary_predicate), find_if_not(begin, end, unary_prediacte)
#include <vector>
using namespace std;

bool policy(int a) {
    return a <= 10;
}

class A {
public:
    bool operator() (int a) {
        return a <= 10;
    }
};

int main() {
    vector<int> a {1, 2, 3, 34, 45, 4, 5, 4, 4, 6};

    auto p1 = find(a.begin(), a.end(), 4) - a.begin();
    cout << p1 << endl;

    auto p2 = find_if(a.begin(), a.end(), policy) - a.begin();
    cout << p2 << endl;

    auto p22 = find_if(a.begin(), a.end(), A()) - a.begin();
    cout << p22 << endl;

    using namespace std::placeholders;
    auto obj = [](int a, int t) { return a >= t; };

    auto p3 = find_if(a.begin(), a.end(), bind(obj, _1, 10)) - a.begin();
    cout << p3 << endl;

    auto p4 = find_if_not(a.begin(), a.end(), policy) - a.begin();      // unary_predicate opposite to find_if()
    cout << p4 << endl;

    auto p5 = find_if_not(a.begin(), a.end(), [](int x) { return x <= 40; });
    cout << p5 - a.begin() << endl;     
    return 0;
}