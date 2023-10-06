// #perfect return in lambda #C++20
#include <iostream>
#include <type_traits>
#include <vector>
#include <sstream>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;

void add(vector<int> one) {
    cout << "COPY" << endl;
    one.push_back(10);
}

void minu(vector<int> &&one) {
    cout << "MOVE" << endl;
    one.pop_back();
}

template<typename Func, typename... Arg>
decltype(auto) alter(Func f, Arg &&...s) {
    return f(std::forward<Arg>(s)...);
}

decltype(auto) alter_lambda = [](auto f, auto &&s) -> decltype(auto) {
    return f(std::forward<decltype(s)>(s));
};

int main() {

    vector<int> a {1, 2, 3};
    alter(add, a);
    alter(minu, std::move(a));

    alter_lambda(add, a);
    alter_lambda(minu, std::move(a));
    return 0;
}