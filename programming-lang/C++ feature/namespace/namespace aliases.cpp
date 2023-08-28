// #different name of namespace 
#include <iostream>
using namespace std;

namespace cplusplus_c11 {
    namespace A {
        void print() {
            cout << "A" << endl;
        }
    }
    void print() { 
        cout << "cplusplus_c11" << endl;
    }
}

// namespace aliases
namespace c11 = cplusplus_c11;

int main() {
    c11::print();
    c11::A::print();
}