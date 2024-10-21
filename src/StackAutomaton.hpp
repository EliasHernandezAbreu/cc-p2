#pragma once

#include <set>
#include <string>
#include <vector>

#include "Transition.hpp"

typedef struct StackAutomatonRuntime {
    std::string current_state;
    std::string word;
    std::string stack;
    int next_transition;
} StackAutomatonRuntime;

class StackAutomaton {
public:
    StackAutomaton(std::string declaration);
    bool solve(std::string word, bool trace) const;

private:
    std::vector<int> getPossibleTransitions(std::string state, std::string word, std::string stack) const;

    std::set<std::string> states;
    std::set<char> input_symbols;
    std::set<char> stack_symbols;
    std::string initial_state;
    char initial_stack;
    std::vector<Transition> transitions;
};
