// vim:set sw=4 et:

#include "secretary.h"

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
    for (size_t n = 2; n < 20; ++n) find_best_decision_check_monotone(n);
    return 0;
}
