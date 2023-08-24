// the following functions have the same call signature `int (int, int)`. In c, one can use pointer to 
// function (ie: `int (*ptr)(int, int) = function`) to do the same thing. However, lambda expression 
// and class operator() can't use this kind of pointer. Instead, std::function<int(int, int)> 
// unify the type of pointer.
#include <iostream>
#include <map>
#include <functional>       // std::function<>, std::modulus<>
using namespace std;

int add(int a, int b) {     // std::plus<int>
    return a + b;
}

struct multi {              // std::multiplies<int>
    int operator()(int a, int b) {
         return a * b;
    }
};

int main() {
    
    auto minus = [](int a, int b) {         // equivalent to std::minus<int>
        return a - b;
    };

    map<string, function<int(int, int)>> hash = {
        {"+", add},
        {"-", minus},
        {"*", multi()},
        {"/", [](int a, int b) { return a / b; }},      // std::divides<int>
        {"%", modulus<int>()}
    };

    cout << hash["+"](10, 14) << endl;
    cout << hash["-"](10, 14) << endl;
    cout << hash["*"](10, 14) << endl;
    cout << hash["/"](10, 14) << endl;
    cout << hash["%"](10, 14) << endl;

    return 0;
}