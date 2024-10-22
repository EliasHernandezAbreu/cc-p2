/**
 * Complejidad Computacional
 * Practica 2 - Automata de pila
 * 
 * @author Elías Hernández Abreu
 * @brief Automaton header
 */

#pragma once

#include <set>
#include <string>
#include <vector>

#include "Transition.hpp"

/**
 * Struct to keep track of iterations, transitions, etc.
 */
typedef struct StackAutomatonRuntime {
    std::string current_state;
    std::string word;
    std::string stack;
    int next_transition;
    int iteration;
} StackAutomatonRuntime;

class StackAutomaton {
public:

    /**
    * Reads an automaton from a string
    * @param declaration The string with the declaration
    */
    StackAutomaton(std::string declaration);

    /**
    * Runs the automaton for a given word
    * @param word The word to test
    * @param trace Whether to print the trace or not
    * @returns True if the word belongs, false if not
    */
    bool solve(std::string word, bool trace) const;

    /**
    * Checks if all symbols of a word are present on the symbol set
    * (DOES NOT CHECK IF THE WORD BELONG TO THE ALPHABET)
    * @param word The word to check
    * @returns Whether the symbols belong or not
    */
    bool wordBelongs(std::string word) const;

private:
    /**
    * Gets possible transitions from a given state
    * @param state The current state
    * @param word The curren input word
    * @param stack The current stack
    * @returns A vector with all possible indexes of possible transitions
    */
    std::vector<int> getPossibleTransitions(std::string state, std::string word, std::string stack) const;

    std::set<std::string> states;
    std::set<char> input_symbols;
    std::set<char> stack_symbols;
    std::string initial_state;
    char initial_stack;
    std::vector<Transition> transitions;
};
