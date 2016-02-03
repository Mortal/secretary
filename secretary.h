// vim:set sw=4 et:

#include <algorithm>
#include <vector>
#include <numeric>

#include <iostream>
#include <map>

template <typename T>
struct permutation {
    size_t n;
    std::vector<T> up;
    std::vector<T> down;
    std::vector<T> prefix_rank;
    std::vector<T> count;

    permutation(size_t n) : n(n), up(n) {
        reset();
    }

    void reset() {
        std::iota(up.begin(), up.end(), T());
        count.resize(up.size());
        for (size_t i = 0; i < count.size(); ++i)
            count[i] = 2 * (i+1);
        down = up;
        prefix_rank = down;
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
        while (i--) {
            size_t state = --count[i];
            if (state == 0) {
                count[i] = 2*(i+1);
            } else if (state == i+1) {
            } else {
                if (state < i+1) move_right(i);
                else move_left(i);
                return true;
            }
        }
        reset();
        return false;
    }
};

double score_strategy(const std::vector<int> & decision) {
    permutation<int> p(decision.size());
    size_t score = 0;
    size_t perms = 0;
    do {
        ++perms;
        // for (auto x : p.up) { std::cout << x << ' '; }
        // std::cout << std::endl;
        size_t i = 0;
        while (i < decision.size()) {
            if (p.prefix_rank[i] < decision[i]) break;
            ++i;
        }
        // std::cout << "Chose " << p.up[i] << " at index " << i << std::endl;
        score += (i == decision.size()) ? decision.size() : p.up[i];
    } while (p.next());
    return (double) score / (double) perms;
}

struct score_strategy_cached {
    double operator()(const std::vector<int> & decision) {
        std::basic_string<int> key(&decision[0], decision.size());
        auto ins = cache.insert({key, 0.0});
        auto it = ins.first;
        bool inserted = ins.second;
        if (inserted) it->second = score_strategy(decision);
        return it->second;
    }

    std::map<std::basic_string<int>, double> cache;
};

void print_decision(const std::vector<int> & decision) {
    std::cout << "\r\e[K";
    for (auto x : decision) std::cout << ' ' << x;
    std::cout << std::flush;
}
