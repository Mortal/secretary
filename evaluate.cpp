// vim:set sw=4 et:

#include "secretary.h"
#include <sstream>

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
