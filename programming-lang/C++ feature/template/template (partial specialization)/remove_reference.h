// partial specialization and general specialization, possible implementation of remove_reference<>
#include <iostream>
using namespace std;

#define DEBUG
#define SPECIALIZATION

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

// testing priority between general and partial specialization
#ifdef SPECIALIZATION
template <>
struct po_remove_reference<int &> {
    po_remove_reference() { cout << "int &" << endl; }
    typedef int type;
};
#endif
