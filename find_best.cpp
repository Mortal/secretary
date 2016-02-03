// vim:set sw=4 et:

#include "secretary.h"

typedef int T;

void find_best_decision(size_t n) {
    score_strategy_cached<T> c;
    std::vector<T> best(n);
    best[n-1] = n;
    double bestScore = c(best);
    for (size_t i = n-1; i--;) {
        std::vector<T> decision = best;
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

int main() {
    size_t n;
    while (std::cin >> n) {
        find_best_decision(n);
    }
    return 0;
}
