// inline namespace can avoid the verbose
#include <iostream>
using namespace std;

namespace A {
    int x = 20;
    // int y = 40;          // **error** if inline namespace B has already had member y
    inline namespace B {
        int y = 10;
        inline namespace C {
            int z = 30;
        }
    }
}

// same as 
/*
namespace A {
    int x = 20;
    namespace B {
        int y = 10;
        namespace C {
            int z = 30;
        }
        using namespace C;
    }
    using namespace B;
}
*/


int main() {
    
    cout << A::x << ' ' << A::B::y << ' ' << A::B::C::z << endl;
    cout << A::x << ' ' << A::y << ' ' << A::z << endl;

    return 0;
}