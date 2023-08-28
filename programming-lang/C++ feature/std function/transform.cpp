/**
 * if object acts as function pointer (aka. functor), it can be replcaed by function or callable.
 * back_inserter use in vector is like push_back()
 */ 
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

ostream &operator<<(ostream &os, vector<int> &p) {
    for (auto x : p) 
        os << x << ' ';
    return os;
}

struct f1 {
    int operator() (int x) {
        return abs(x);
    }
};

int f2(int p, int boundary) {
    return abs(p) > boundary;
}

int f4(int p) {
    return abs(p);
}

int main() {
        
    vector<int> in {-3, -2, -1};

    // without back_inserter, enough space 
    vector<int> v0(in.size());
    transform(in.begin(), in.end(), v0.begin(), f4);
    cout << v0 << endl;

    // callable function
    vector<int> v1;
    transform(in.begin(), in.end(), back_inserter(v1), [](int p) { return abs(p); });
    cout << v1 << endl;

    // functor, since transform() require Unary operation which is function. f1 is a uninitialized class 
    vector<int> v2;
    transform(in.begin(), in.end(), back_inserter(v2), f1());
    cout << v2 << endl;

    // function
    vector<int> v3;
    transform(in.begin(), in.end(), back_inserter(v3), f4);
    cout << v3 << endl;

    // callable function
    vector<int> v4;
    auto f3 = [](int p) {
        return abs(p);
    };
    transform(in.begin(), in.end(), back_inserter(v4), f3);
    cout << v4 << endl;

    // bind convert to callable object
    using namespace std::placeholders;
    transform(v4.begin(), v4.end(), back_inserter(v4), bind(f2, _1, 1));
    cout << v4 << endl;

    return 0;
}