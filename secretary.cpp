// vim:set sw=4 et:

#include <algorithm>
#include <vector>
#include <iostream>

template <typename T>
struct permutation {
    size_t n;
    std::vector<T> up;
    std::vector<T> down;
    std::vector<T> prefix_rank;
    size_t k;

    permutation(size_t n) : n(n), up(n) {
        std::iota(up.begin(), up.end(), T());
        down = up;
        prefix_rank = down;
        k = 0;
    }

    void swap(T i) {
        std::iter_swap(&up[i], &up[i+1]);
        std::iter_swap(&prefix_rank[i], &prefix_rank[i+1]);
        if (up[i] < up[i+1]) {
            prefix_rank[i+1] += 1;
        } else {
            prefix_rank[i] -= 1;
        }
        down[up[i]] = i;
        down[up[i+1]] = i+1;
    }

    void move_left(size_t i) {
        swap(down[i] - 1);
    }

    void move_right(size_t i) {
        swap(down[i]);
    }

    bool next() {
        size_t i = n;
        size_t k = ++this->k;
        while (i--) {
            size_t state = k % (2*(i+1));
            k /= i+1;
            if (state == 0 || state == i+1) continue;
            if (state < i+1) move_left(i);
            else move_right(i);
            return true;
        }
        return false;
    }
};

int main() {
    permutation<int> p(5);
    do {
        for (auto x : p.up) { std::cout << x << ' '; }
        std::cout << std::endl;
        for (auto x : p.prefix_rank) { std::cout << x << ' '; }
        std::cout << std::endl;
        for (auto x : p.down) { std::cout << x << ' '; }
        std::cout << std::endl << std::endl;
    } while (p.next());
    return 0;
}
