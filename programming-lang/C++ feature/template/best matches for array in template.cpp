// the best matching type for array in template<>
#include <iostream>
using namespace std;

// since `const T &arr` has generally appear, for not blocking the most suitable function, it has 
// slightly low priority if among best matching
template<typename T>
void print(const T &arr) {
    cout << "const T &" << endl;
}

template<typename T>
void print(T &arr) {
    cout << "T &" << endl;
}

// nontype template
template<typename T, size_t N>
void print(const T (&arr)[N]) {
    cout << "nontype" << endl;
}

int main() {
    
    int a1[] = {1, 2, 3};
    cout << "int: ";
    print(a1);                              // print(T &), no const 

    const int a2[] = {1, 2, 3};             // print(const T (&arr)[N]), has const but print(const T &arr) has lower priority
    cout << "const int: ";
    print(a2);

    const vector<int> a3 {1, 2, 3};         // print(T &), has const and print(const T (&arr)[N]) doesn't match
    cout << "vector: ";
    print(a3);

    return 0;
}