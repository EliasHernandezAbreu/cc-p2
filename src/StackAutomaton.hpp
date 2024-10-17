#pragma once

#include <set>
#include <string>
#include <vector>

#include "Transition.hpp"

class StackAutomaton {
public:
    StackAutomaton(std::string declaration);
    bool solve(std::string word) const;

private:
    std::set<std::string> states;
    std::set<char> input_symbols;
    std::set<char> stack_symbols;
    std::string initial_state;
    char initial_stack;
    std::vector<Transition> transitions;
};
