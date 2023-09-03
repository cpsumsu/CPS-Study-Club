// using reference instead of static is also a method to continue the state of random_engine
#include <iostream>
#include <vector>
using namespace std;

#include <random>       // default_random_engine; uniform_real_distribution<>
#include <functional>

void print_distribution(default_random_engine e, uniform_real_distribution<double> u) {
    for (int i = 0; i < 5; i++)
        cout << u(e) << ' ';
    cout << endl;
}

// don't use const in defaul_random_engine and uniform_real_distribution
void ref_print_distribution(default_random_engine &e, uniform_real_distribution<double> u) {
    for (int i = 0; i < 5; i++) 
        cout << u(e) << ' ';
    cout << endl;
}

int main() {

    default_random_engine e;
    uniform_real_distribution<double> u(0, 1);      // generate floating-point number

    print_distribution(e, u);
    print_distribution(e, u);

    ref_print_distribution(e, u);
    ref_print_distribution(e, u);
    ref_print_distribution(e, u);

    print_distribution(e, u);
    print_distribution(e, u);

    return 0;
}