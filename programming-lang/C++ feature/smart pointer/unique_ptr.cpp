/**
 * most idea came from c++ primer chapter 12
 * 
 * There are mainly two type of unique_ptr in std:
 *  - unique_ptr<T, destructor = default>
 *  - unique_ptr<T[], destructor>           // built-in array
 */
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

void basic_example() {
    cout << "Example_1" << endl;

    unique_ptr<int> p1(new int(10));
    unique_ptr<string> p2 = make_unique<string>("hello");           // make_unique is suggested to use, c++14

    cout << "p1: " << *p1 << ", p2: " << *p2 << endl;       

    unique_ptr<int[]> p3(new int[3]{1, 2, 3});  // unique pointer support dynamic allocated array, 
                                                // it also has default destructor for built-in array. (see exmpale_3)
    cout << "p3: ";
    for (int i = 0; i < 3; i++)
    //  cout << *((*p3) + i) << ' ';            // error 
        cout << p3[i] << ' ';                   // to deference array in unique pointer, only operator[] is provided

    unique_ptr<vector<int>> p4(make_unique<vector<int>>(vector<int>{10, 20, 30}));      // move constructor is called
    // equivalent to 
    // unique_ptr<vector<int>> p4(new vector<int>{10, 20, 30});

    // However, this is wrong. Compiler considers this is std::initializer_list<int> type, not vector<int>.
    // Require to specify std::vector<int>
    // unique_ptr<vector<int>> p4 = make_unique<vector<int>>({10, 20, 30});   

    cout << endl << "p4: ";
    for (auto x : *p4)
        cout << x << ' ';
}

// copy initialization 
void method_example() {
    cout << "Exmaple_2" << endl;

    unique_ptr<vector<int>> p1(new vector<int>);
    p1->push_back(10);                              // access container and use its methods
    p1->push_back(20);
    p1->push_back(30);

    cout << "p1: ";
    for (auto x : *p1) 
        cout << x << ' ';
    cout << endl;

    // unique_ptr<vector<int>> p2(p1);          // error, each unique pointer has its ownership
    unique_ptr<vector<int>> p2(std::move(p1));      // get p1 ownership, p1 = nullptr
    if (p1 == nullptr)                      
        cout << "yes, p1 point to null" << endl;
    else 
        cout << "p1: " << (*p1)[0] << endl;

    cout << "p2: ";
    for (auto x : *p2)
        cout << x << ' ';
    cout << endl;

    /**
     * release() and reset()
     * 
     * reset() has 3 constructor:
     * - reset()                        // set the object to nullptr
     * - reset(pointer)                 // get the ownership from the pointer, the pointer = null
     * - reset(pointer, destructor)     // provide a destructor for destroy the object
     */

    unique_ptr<vector<int>> p3(p2.release());       // release() return built-in pointer, p2 = nullptr
    // use release() carefully, the memory might not be deleted if no pointer catch it

    if (p2 == nullptr)                      
            cout << "yes, p2 point to null" << endl;
        else 
            cout << "p2: " << (*p2)[0] << endl;

    cout << "p3: ";
    for (auto x : *p3)
        cout << x << ' ';
    cout << endl;

    p2.reset(p3.release());         // p3 = nullptr, p2 get the memory
    cout << "p2: ";
    for (auto x : *p2)
        cout << x << ' ';
    cout << endl;
}

static void del(int *p) {
    cout << "del is called" << endl;
    delete [] p;
}

// user-defined destructor 
void object_example() {
    cout << "Example 3" << endl;

    auto deleter = [](int *p) {
        cout << "deleter is called" << endl;
        delete [] p;
    };  

    auto construct = []() {
        cout << "construct is called" << endl;
        return new int[5];
    };

    int *ptr = new int[6];

    // not construct but construct(). unique_ptr<>(pointer, deleter)
    unique_ptr<int[], decltype(deleter)> p1(construct(), deleter);
    // caution! pointer-to-function
    unique_ptr<int[], decltype(del) *> p2(ptr, del);

    p1.reset();
    p2.reset();
}

int main() {
    basic_example();
    method_example();
    object_example();
    return 0;
}