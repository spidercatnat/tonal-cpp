#include <iostream>
#include <numeric>
#include <vector>
#include <string>

using namespace std;

std::string fillStr(std::string s, int n)
{
    std::string fill_str;
    for (int i = 0; i < n; i ++) {
        fill_str.append(s);
    }
    return fill_str;
}

int main()
{
    cout << fillStr("C", 2) << endl;
    return 0;
}