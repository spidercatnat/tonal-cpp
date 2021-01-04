#include <string>
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include "./utils.h"

using namespace std;
using namespace utils;

namespace named
{
    struct Named
    {
        const std::string name;
    };

    struct NamedFound
    {
        const std::false_type empty;
    };

    struct NotFound : public NamedFound
    {
        const std::true_type empty;
        const std::string name;
    };

    template <typename AnySrc>
    bool isNamed(AnySrc src)
    {
        std::string unmangled_type = getUnmangledType(src);
        return unmangled_type == "named::Named" || unmangled_type == "named::NamedFound";
    }

} 
