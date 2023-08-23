#include <iostream>
using namespace std;

template<typename T>
void wrapper(T &&u) {
    /*
        reference collapsing:
        int & && = int &
        int && & = int &
        int & & = int &
        int && && = int &&
    */
    fun(std::forward<T>(u));
    // fun(u);      // compiler copy the rvalue and become lvalue, it want to use rvalue reference, use std::move()
}

class MyClass {};

void fun(MyClass &a) { cout << "in fun(MyClass &)\n"; }
void fun(const MyClass &a) { cout << "in fun(const MyClasss &)\n"; }
void fun(MyClass &&a) { cout << "in fun(MyClass &&)\n"; }

int main() {
    MyClass a;
    const MyClass b;

    fun(a);
    fun(b);
    fun(MyClass());

    cout << "------------Wrapper------------" << endl;
    wrapper(a);
    wrapper(b);
    wrapper(MyClass());

    return 0;
}