// #recursive lambda expression
// c++14 generic feature, recursive function convert into recursive lambda expression
#include <iostream>
#include <functional>
using namespace std;

// #define NORMAL_FUNCTION

void lambda_mutable() {
    int x = 0;
    auto f1 = [=]() mutable -> void {
        x = 100;

        cout << x << endl;
    };

    f1();
    cout << x << endl;
}

#ifdef NORMAL_FUNCTION

// normal function implementation
int term(int x) {
    return x * 10;
}

int next(int y) {
    return y + 1;
}

int _sum(int a, int b) {
    if (term(a) <= b)
        return 1;
    return _sum(a, next(b)) + 1;
}

int sum(int a, int b) {
    return _sum(a, b);
}
#endif


void lambda_recursion() {
    auto term = [](int x) {
        return x * 10;
    };

    auto next = [](int y) {
        return y + 1;
    };

    const auto sum = [term, next](int a, int b) {
        auto _sum = [term, next](int a, int b, auto &_sum) mutable {
            if (term(a) <= b)
                return 1;
            return _sum(a, next(b), _sum) + 1;
        };
        return _sum(a, b, _sum);
    };

    cout << sum(1, 1);
}

void functor_recursion() {
    auto term = [](int x) {
        return x * 10;
    };

    auto next = [](int y) {
        return y + 1;
    };

    function<int(int, int)> sum = [&](int a, int b) -> int {
        if (term(a) <= b)
            return 1;
        return sum(a, next(b)) + 1;
    };

    cout << sum(1, 1) << endl;
}


int main() {
    
    // lambda_mutable();
    // lambda_recursion();
    functor_recursion();
    // sum(1, 1);
    return 0;
}