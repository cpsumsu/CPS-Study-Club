// no conversion from pointer to reference to an array
// combined with template specialization example
#include <iostream>
using namespace std;

#define SPECIALIZATION

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

#ifdef SPECIALIZATION
template <>
void print(const char *&arr) {
    cout << "const char * specialization" << endl;
}

template <>
void print(const char * const &arr) {
    cout << "const char * const specialization" << endl;
}
#endif

int main() {

    const char *a1 = "one";
    cout << "const char *: ";
    print(a1);
   
    const char * const b1 = "two";
    cout << "const char * const: ";
    print(b1);


    return 0;
}