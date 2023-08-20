// partial specialization, possible implementation of remove_reference<>
#include <iostream>
using namespace std;

// #define DEBUG

// origin 
template<typename T>
struct po_remove_reference {    
    #ifdef DEBUG
    po_remove_reference() { cout << "origin" << endl; }
    #endif
    typedef T type;
};

// partial specialization <T &>
template<typename T>
struct po_remove_reference<T &> {
    #ifdef DEBUG
    po_remove_reference() { cout << "T &" << endl; }
    #endif
    typedef T type;
};

// partial specialization <T &&>
template<typename T>
struct po_remove_reference<T &&> {
    #ifdef DEBUG
    po_remove_reference() { cout << "T &&" << endl; }
    #endif
    typedef T type;
};

int main() {
    
    po_remove_reference<decltype(10)>();    
    int i = 10;
    po_remove_reference<decltype(i)>();
    int &&j = 10;
    po_remove_reference<decltype(j)>();
    return 0;
}