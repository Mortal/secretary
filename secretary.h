// vim:set sw=4 et:

#include <algorithm>
#include <vector>
#include <numeric>

#include <iostream>
#include <map>

template <typename T, typename child_t>
struct permutation_base {
    child_t & self() { return *static_cast<child_t *>(this); }

    size_t n;
    std::vector<T> up;
    std::vector<T> down;
    std::vector<T> count;

    permutation_base(size_t n) : n(n), up(n) {
        reset(n);
    }

    void reset(size_t n) {
        up.resize(n);
        std::iota(up.begin(), up.end(), T());
        count.resize(up.size());
        for (size_t i = 0; i < count.size(); ++i)
            count[i] = 2 * (i+1);
        down = up;
    }

    void swap(T i) {
        std::iter_swap(&up[i], &up[i+1]);
        down[up[i]] = i;
        down[up[i+1]] = i+1;
    }

    void move_left(size_t i) {
        self().swap(down[i] - 1);
    }

    void move_right(size_t i) {
        self().swap(down[i]);
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
        self().reset(up.size());
        return false;
    }
};

template <typename T>
struct permutation : public permutation_base<T, permutation<T> > {
    typedef permutation_base<T, permutation<T> > p_t;

    permutation(std::vector<T> decision) : p_t(decision.size()) {
        this->decision = std::move(decision);
        reset(this->decision.size());
    }

    std::vector<T> prefix_rank;
    std::vector<T> decision;
    size_t chosen;

    void reset(size_t n) {
        p_t::reset(n);
        prefix_rank = this->down;
        redecide(0);
    }

    void swap(T i) {
        p_t::swap(i);
        std::iter_swap(&prefix_rank[i], &prefix_rank[i+1]);
        if (this->up[i] < this->up[i+1]) {
            prefix_rank[i+1] += 1;
        } else {
            prefix_rank[i] -= 1;
        }
        if (chosen >= (size_t) i) redecide(i);
    }

    void redecide(size_t i) {
        while (i < decision.size() && prefix_rank[i] >= decision[i]) ++i;
        chosen = i;
    }
};

template <typename T>
double score_strategy(const std::vector<T> & decision) {
    permutation<T> p(decision);
    size_t score = 0;
    size_t perms = 0;
    do {
        ++perms;
        size_t i = p.chosen;
        score += (i == decision.size()) ? decision.size() : p.up[i];
    } while (p.next());
    return (double) score / (double) perms;
}

template <typename T>
struct score_strategy_cached {
    double operator()(const std::vector<T> & decision) {
        std::basic_string<T> key(&decision[0], decision.size());
        auto ins = cache.insert({key, 0.0});
        auto it = ins.first;
        bool inserted = ins.second;
        if (inserted) it->second = score_strategy(decision);
        return it->second;
    }

    std::map<std::basic_string<T>, double> cache;
};

template <typename T>
void print_decision(const std::vector<T> & decision) {
    std::cout << "\r\e[K";
    for (auto x : decision) std::cout << ' ' << x;
    std::cout << std::flush;
}
