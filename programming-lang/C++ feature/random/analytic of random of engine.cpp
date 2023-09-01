// distribution() function has a fixed algorithm, the only edependent is the raw random number
// default_random_engine. 
#include <iostream>
#include <vector>
using namespace std;

#include <random>       // default_random_engine; uniform_real_distribution<>
#include <functional>

#include "print_random_engine.h"

// For experiement perspective, generate same sequence is very helpful
vector<unsigned> bad_generator() {
    uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e;        // default_random_engine is regarded as raw random number

    vector<unsigned> ret;
    for (unsigned i = 0; i < 10; i++)
        ret.emplace_back(u(e));
    return ret;
}

// `static` hold default_randome_engine state across calls to the function
vector<unsigned> good_generator() {
    uniform_int_distribution<unsigned> u(0, 9);
    static default_random_engine e;

    vector<unsigned> ret;
    for (size_t i = 0; i < 10; i++)
        ret.emplace_back(u(e));
    return ret;
}

void testing(function<vector<unsigned>()> f) {
    vector<unsigned> a(f());
    vector<unsigned> b(f());

    cout << "a == b: " << (a == b ? "equal" : "unequal") << endl;
}

int main() {

    default_random_engine e;
    uniform_real_distribution<double> u(0, 1);      // generate floating-point number

    // they are the same since the random_engine only call first time, due to copy.
    print_distribution(u);
    print_distribution(u);

    // their value are diff. since random_engine step twice
    ref_print_distribution(u, e);
    ref_print_distribution(u, e);

    testing(bad_generator);     // generate same vector
    testing(good_generator);    // generate diff. vector
}