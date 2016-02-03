// vim:set sw=4 et:
#include "secretary.h"
#include <sstream>

struct permutation_simple : public permutation_base<int, permutation_simple> {
    typedef permutation_base<int, permutation_simple> p_t;
    using p_t::permutation_base;
};

int main(int argc, char ** argv) {
    size_t n = 4;
    if (argc > 1) std::stringstream(argv[1]) >> n;
    permutation_simple p(n);
    do {
        for (auto x : p.up) std::cout << ' ' << x;
        std::cout << std::endl;
    } while (p.next());
    for (auto x : p.up) std::cout << ' ' << x;
    std::cout << std::endl;
    return 0;
}
