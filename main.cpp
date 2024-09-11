#include <iostream>

#include "automaton.hpp"

int main() {
    Automaton<int, int> a{
        {
            {0, [](int value) {
                if (value == 0) return 2;
                return 1;
            }},
            {1, [](int value) {
                if (value == 0) return 3;
                return 0;
            }},
            {2, [](int value) {
                if (value == 0) return 0;
                return 3;
            }},
            {3, [](int value) {
                if (value == 0) return 1;
                return 2;
            }},
        },
        0,
        {0},
    };

    auto state = a.simulate({0, 0, 1, 0, 1, 1, 0, 1});
    std::cout << "final state: " << state << "\n";
    if (a.isAcceptingState(state)) {
        std::cout << "valid\n";
    } else {
        std::cout << "invalid\n";
    }
}