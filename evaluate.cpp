// vim:set sw=4 et:

#include "secretary.h"
#include <sstream>

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

int main() {
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
    return 0;
}
