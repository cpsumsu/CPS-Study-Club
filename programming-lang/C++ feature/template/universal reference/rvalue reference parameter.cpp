// po_forward<> is equivalent to forward<>
#include <iostream>
#include <memory>
using namespace std;

#include <type_traits>
#include "forward_and_move.h"

template <typename T, typename U>
void g(T&& t, U&& u)
{
    std::cout << "t is lvalue ref: "
              << std::is_lvalue_reference<decltype(t)>::value << std::endl; // 1
    std::cout << "t is rvalue ref: "
              << std::is_rvalue_reference<decltype(t)>::value << std::endl; // 0
    std::cout << "u is lvalue ref: "
              << std::is_lvalue_reference<decltype(u)>::value << std::endl; // 1
    std::cout << "u is rvalue ref: "
              << std::is_rvalue_reference<decltype(u)>::value << std::endl; // 0
}

template <typename T, typename U>
void f(T&& t, U&& u)
{
    std::cout << "t is lvalue ref: "
              << std::is_lvalue_reference<decltype(t)>::value << std::endl; // 1
    std::cout << "t is rvalue ref: "
              << std::is_rvalue_reference<decltype(t)>::value << std::endl; // 0
    std::cout << "u is lvalue ref: "
              << std::is_lvalue_reference<decltype(u)>::value << std::endl; // 0
    std::cout << "u is rvalue ref: "
              << std::is_rvalue_reference<decltype(u)>::value << std::endl; // 1

    // if define FORWARD in file "fowward_and_move.h", po_forward() version will be used
    #ifdef FORWARD
        g(po_forward<T>(t), po_forward<U>(u));
    #else
        g(t, u);
    #endif
}

int main() {
    
    unique_ptr<int> p1;

    // if define MOVE in file "fowward_and_move.h", po_forward() version will be used
    #ifdef MOVE
        f(po_move(p1), unique_ptr<int>());
    #else
        f(p1, unique_ptr<int>());
    #endif

    return 0;
}