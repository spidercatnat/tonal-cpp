#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <cxxabi.h>

using namespace std;

namespace utils
{
    std::string fillStr(std::string s, int n)
    {
        std::string fill_str;
        for (int i = 0; i < n; i++)
        {
            fill_str.append(s);
        }
        return fill_str;
    }

    template <typename AnyMangled>
    std::string getUnmangledType(AnyMangled var)
    {
        int status;
        char *realname;
        const std::type_info &ti = typeid(var);
        realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
        return realname;
    }

} 
