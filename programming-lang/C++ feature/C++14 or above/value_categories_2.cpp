// #is_same #is_same_v #is_reference_v
#include <iostream>
using namespace std;

void rvFunc(string &&str) {
    cout << "origin: " << endl;     
    cout << is_same<decltype(str), string>::value << endl;
    cout << is_same<decltype(str), string &>::value << endl;
    cout << is_same<decltype(str), string &&>::value << endl;

    // consider it is str is rvalue reference, expression makes it becomes a lvaule reference
    cout << "expression: " << endl;
    cout << is_same<decltype((str)), string>::value << endl;
    cout << is_same<decltype((str)), string &>::value << endl;
    cout << is_same<decltype((str)), string &&>::value << endl;

    cout << "addition: " << endl;
    cout << is_same<decltype(str + str), string>::value << endl;    // return prvalue 
    cout << is_same<decltype(str + str), string &>::value << endl;
    cout << is_same_v<decltype(str + str), string &&> << endl;
    cout << is_reference_v<decltype(str + str)> << endl;

    cout << is_same<decltype(str[0]), char &>::value << endl;       // index operator return lvalue reference
}

void two() {
    // a + a return prvalue, which is assignable which is obviously a bug 
    string a ("abc");
    a + a = a;          
}

int main() {
    
    rvFunc("hello");

    return 0;
}