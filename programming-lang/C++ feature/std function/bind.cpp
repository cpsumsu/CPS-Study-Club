// #bind #function pointer #ref() #callable object
/**
 * bind(callabe, arg_list), where arg_list is parater list. bind() return callable object
 * 
 * Note: argument using bind() or lambda expression default as pass by value. However, ostream can't use copy, so use ref()
 */
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
using namespace std::placeholders;

static bool size_compare(const string &s, string::size_type sz) {
    return s.size() >= sz;
}

// function pointer
void Ex_1() {
    vector<int> vec = {0,1,2,3,4,5,16,17,18,19};
       
   // bind second argument to less_equal, also initialize less_equal<int> and use its operator()
   cout << count_if(vec.begin(), vec.end(), bind(less_equal<int>(), _1, 10)) << endl;
   
   vector<string> svec = {"one", "two", "three", "four", "ten", "eleven", "twelve", "thirteen"};

   // decltype(size_compare) = bool(const string &s, string::size_type sz)
   function<decltype(size_compare)> fp1 = size_compare;        

   //decltype(fp1)::result_type ret;
   function<bool(const string&)> fp2 = bind(size_compare, _1, 6);
   cout << count_if(svec.begin(), svec.end(), fp2) << endl;
   // equivalent to 
   cout << count_if(svec.begin(), svec.end(), bind(size_compare, _1, 6)) << endl;
}

// lambda expression
void Ex_2() {
    vector<int> a { 1, 2, 3, 4, 5, 6, 7 };

    auto ob = [](int a, int target) {
        return a == target;
    };

    auto obj = bind(ob, _1, 3);     // ob is function, _1 and t are argument corresponding to (int a, int target)
                                    // _1 can be embeded by find_if.
    auto sc = find_if(a.begin(), a.end(), obj);
    // equivalent to `auto sc = find_if(a.begin(), a.end(), bind(ob, _1, 3));`
}

// ref() to ostream &os, trailing return 
void Ex_3() {
    vector<int> a { 1, 2, 3, 4, 5 };

    // replace `auto` 
    function<ostream&(ostream &, int, char)> print = [](ostream &os, int x, char c) -> ostream & {
        return os << x << c << endl;
    };
    for_each(a.begin(), a.end(), bind(print, ref(cout), _1, ' '));

    function<ostream &(int)> print_ans = bind(print, ref(cout), _1, ' ');
    for_each(a.begin(), a.end(), print_ans);
}

int main() {

    Ex_1();
    Ex_2();
    Ex_3();

    return 0;
}
