// #argument-dependent lookup #namespace visible scope
#include <iostream>
#include <algorithm>
using namespace std;

namespace A {
    class B {
    public:
        friend void print(const B &bb) { cout << bb.a << endl; }
        friend void print() { cout << b << endl; }

    private:
        static const int a = 10;
        static const int b = 20;
    };

    // member of A
    void print(const B &);
    void print();
}

int main() {
    
    A::B run;
    print(run);         // visible since argument-dependent lookup
    A::print();         // require declaring scope 
    
    return 0;
}