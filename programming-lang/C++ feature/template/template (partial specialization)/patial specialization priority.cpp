// specialization > partial specialization in priority since former is more explicit 
#include <iostream>
using namespace std;

#include "remove_reference.h"

int main() {
    
    po_remove_reference<decltype(10)>();    

    int i = 10;
    po_remove_reference<decltype(i)>();

    int &y = i;
    po_remove_reference<decltype(y)>();

    int &&j = 10;
    po_remove_reference<decltype(j)>();

    po_remove_reference<int &>();       // specialization > partial specialization
    return 0;
}