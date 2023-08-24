// The distinction between lvalue and rvalue shown by uncommon examples
#include <iostream>
#include <utility>      // std::move()
using namespace std;

void example_1() {
    int a = 10;

    // int &b = 10;         // ** error ** 10 is a rvalue, since it will be release after ';'
    int &b = a;             // ok
    const int &c = 10;      // ok, rvalue reference to const <=> rvalue reference

    int &&d = 10;           // ok, 10 is rvalue
    // int &&e = d;         // ** error **, x is now a variable (lvalue)
    int &&e = std::move(d);
    int &&f = e * 100;      // ok, expression is rvalue
}

void example_2() {

    auto func = []() -> int {
        int x = 10;
        return x;
    };

    auto func_lvalue = []() ->int & {       // x is a local variable, just for demonstration
        int x = 10;
        return x;
    };

    int x = func();
    // int &y = func();            // ** error ** returned value is temprorary value
    int &&z = func();

    /* before c++11, this sitution is unable to prevent, now can use rvalue qualifier to prevent */
    string s1, s2;                 
    s1 + s2 = "hello";              // declare the object is lvalue 

    func_lvalue() = 100;
}

int main() {
    example_1();
    example_2();
    return 0;
}

