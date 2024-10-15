#pragma once

#include <set>
#include <string>

#include "Transition.hpp"

class StackAutomaton {
public:
    StackAutomaton(std::string declaration);

private:
    std::set<std::string> states;
    std::set<char> input_symbols;
    std::set<char> stack_symbols;
    std::string initial_state;
    char initial_stack;
    std::set<Transition> transitions;
};
