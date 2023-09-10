#include <iostream>
using namespace std;

long long string_to_ll(const string &s) {
    long long ret = 0;
    for (auto c : s) {
        ret = ret * 10 + (c - '0');
    }

    return ret;
}

double string_to_double(const string &s) {
    double ret = 0.0;
  
    auto u = s.find_first_of('.');

    for (int i = 0; i < u; i++) {
        ret = ret * 10 + (s[i] - '0');
    }

    for (int i = u + 1; i < s.size(); i++) {
        ret += double(s[i] - '0') / (pow(10, (i - u)));
    }

    return ret;
}

int main() {
    string r = "132";
    cout << string_to_ll(r) << endl;

    string c = "12.34";
    cout << string_to_double(c) << endl;
    return 0;
}


