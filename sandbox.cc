#include "./core/core.h"

using namespace std;

int main()
{
    // int _step, int _alt, int _oct, Direction _dir)
    Pitch p(0, 0, 2, asc);
    printf(isPitch(p) ? "true" : "false");
    std::cout << std::endl;
    p.showParams();
    return 0;
}