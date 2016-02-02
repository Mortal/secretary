// vim:set sw=4 et:

#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>

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

double score_strategy(std::vector<int> decision) {
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

int main() {
    /*
    std::string line;
    std::vector<int> decision;
    while (std::getline(std::cin, line)) {
        decision.clear();
        std::stringstream ss(line);
        int x;
        while (ss >> x) decision.push_back(x);
        auto score = score_strategy(decision);
        std::cout << "Score is " << score << std::endl;
    }
    */
    size_t n;
    while (std::cin >> n) {
        std::vector<int> best(n);
        best[n-1] = n-1;
        double bestScore = score_strategy(best);
        for (size_t i = n - 1; i--;) {
            std::vector<int> decision = best;
#ifdef CHECK_MONOTONE
            bool decreasing = true;
            double prevScore;
#endif
            for (size_t j = 0; j <= i; ++j) {
                decision[i] = j;
                auto score = score_strategy(decision);
#ifdef CHECK_MONOTONE
                if (j == 0) {
                    prevScore = score;
                } else if (decreasing && score > prevScore) {
                    decreasing = false;
                } else if (!decreasing && score < prevScore) {
                    std::cout << "Not monotone" << std::endl;
                    decision[i] = j - 1;
                    for (auto x : decision) std::cout << ' ' << x;
                    std::cout << std::endl;
                    decision[i] = j;
                    for (auto x : decision) std::cout << ' ' << x;
                    std::cout << std::endl;
                }
#endif
                if (score < bestScore) {
                    best = decision;
                    bestScore = score;
                } else {
#ifndef CHECK_MONOTONE
                    if (score > bestScore) {
                        break;
                    }
#endif
                }
                ++decision[i];
            }
        }
        for (auto x : best) std::cout << ' ' << x;
        std::cout << std::endl;
    }
    return 0;
}
