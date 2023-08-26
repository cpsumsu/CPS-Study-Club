// #visiblility of namespace #namespace and function

// since A::b and b are not in the same scope, so local variable b hide namespace member name,
// so need to call namespace member b explicitly
#include <iostream>
using namespace std;

namespace A {
    int a = 10;
    int b = 20;
    int c = 30;
}

int a = 40;             // global scope

int main() {
    
    using namespace A;
    cout << b << endl;      // A::b = 20 shown

    int b = 50;
    cout << b << endl;      // b = 50 shown, which means it hide A::b
    cout << A::b << endl;

    return 0;
}