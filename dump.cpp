// vim:set sw=4 et:
#include "secretary.h"

int main() {
    permutation<int> p(4);
    do {
        for (auto x : p.up) std::cout << ' ' << x;
        std::cout << std::endl;
    } while (p.next());
    return 0;
}
