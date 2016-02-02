// vim:set sw=4 et:

#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

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

void find_best_decision(size_t n) {
    score_strategy_cached c;
    std::vector<int> best(n);
    best[n-1] = n;
    double bestScore = c(best);
    for (size_t i = n-1; i--;) {
        std::vector<int> decision = best;
        for (size_t j = 0; j <= i + 1 && j <= (size_t) best[i+1]; ++j) {
            decision[i] = j;
            print_decision(decision);
            auto score = c(decision);
            if (score < bestScore) {
                best = decision;
                bestScore = score;
            } else if (score > bestScore) {
                break;
            }
        }
    }
    print_decision(best);
    std::cout << ' ' << bestScore << std::endl;
}

void find_best_decision_check_monotone(size_t n) {
    score_strategy_cached c;
    std::vector<int> best(n);
    double bestScore = c(best);
    for (size_t i = n; i--;) {
        std::vector<int> decision = best;
        bool decreasing = true;
        double prevScore = 0;
        for (size_t j = 0; j <= i + 1; ++j) {
            decision[i] = j;
            print_decision(decision);
            auto score = c(decision);
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
            if (score < bestScore) {
                best = decision;
                bestScore = score;
            }
        }
    }
    print_decision(best);
    std::cout << ' ' << bestScore << std::endl;
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
        find_best_decision(n);
    }
    return 0;
}
