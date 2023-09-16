#include <iostream>
#include <string>
#include <vector>
using namespace std;

void get_next(string t, vector<int>& next)
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < t.size() - 1)
    {
        if (j == -1 || t[i] == t[j])
        {
            next[++i] = ++j;
        }
        else
        {
            j = next[j];
        }
    }
}

int KMP_search(string s, string t)
{
    int i = 0, j = 0;
    vector<int> next(t.size());
    get_next(t, next);
    while (j == -1 || (i < s.size() && j < t.size())) // 此处涉及-1和unsigned比较
        // 由于signed int的负数最高位是1，转换成unsigned int之后，就会变成一个很大的unsigned int型正数
    {
        if (j == -1 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == t.size())
        return i - j;
    else
        return -1;
}

int main()
{
    string s = "aaab";
    string t = "ab";
    cout << KMP_search(s, t) << endl;
    return 0;
}