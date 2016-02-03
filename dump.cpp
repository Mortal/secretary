// vim:set sw=4 et:
#include "secretary.h"

struct permutation_simple : public permutation_base<int, permutation_simple> {
    typedef permutation_base<int, permutation_simple> p_t;
    using p_t::permutation_base;
};

int main() {
    permutation_simple p(4);
    do {
        for (auto x : p.up) std::cout << ' ' << x;
        std::cout << std::endl;
    } while (p.next());
    return 0;
}
