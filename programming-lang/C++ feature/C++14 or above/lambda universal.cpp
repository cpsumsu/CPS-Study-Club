// #universal reference application  #lambda universal reference
#include <iostream>
using namespace std;

class Str {
private:
    string name;
public:
    Str(const char *c) : name(c) {}

    string &&getName() && {
        cout << "MOVE" << endl;
        return std::move(name);
    }

    const string &getName() const & {
        cout << "COPY" << endl;
        return name;
    }
};

// ordinary universal reference, support since C++11
template <typename T>
void Fun(T &&one) {

    cout << one.getName() << endl;
    cout << std::forward<T>(one).getName() << endl;
}

// lambda universal reference, support since C++20
auto fun = []<typename T>(T &&arg) {
    cout << std::forward<T>(arg).getName() << endl;
};

int main() {
    Str one("world");

    Fun(one);
    Fun(Str("hello"));   

    fun(Str("hi"));

    return 0;
}