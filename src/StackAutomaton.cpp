#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "StackAutomaton.hpp"

StackAutomaton::StackAutomaton(std::string declaration) {
    std::stringstream declaration_stream;
    std::regex comment_regex("#.*\\n");
    declaration_stream << std::regex_replace(declaration, comment_regex, "");

    std::string states_line;
    std::string input_symbols_line;
    std::string stack_symbols_line;
    std::string initial_state_line;
    std::string initial_stack_line;

    std::getline(declaration_stream, states_line);
    std::getline(declaration_stream, input_symbols_line);
    std::getline(declaration_stream, stack_symbols_line);
    std::getline(declaration_stream, initial_state_line);
    std::getline(declaration_stream, initial_stack_line);

    // states_line.erase(std::remove_if(states_line.begin(), states_line.end(), ::isspace), states_line.end());
    input_symbols_line.erase(std::remove_if(input_symbols_line.begin(), input_symbols_line.end(), ::isspace), input_symbols_line.end());
    stack_symbols_line.erase(std::remove_if(stack_symbols_line.begin(), stack_symbols_line.end(), ::isspace), stack_symbols_line.end());
    initial_state_line.erase(std::remove_if(initial_state_line.begin(), initial_state_line.end(), ::isspace), initial_state_line.end());
    initial_stack_line.erase(std::remove_if(initial_stack_line.begin(), initial_stack_line.end(), ::isspace), initial_stack_line.end());

    std::stringstream states_stream(states_line);
    std::stringstream input_symbols_stream(input_symbols_line);
    std::stringstream stack_symbols_stream(stack_symbols_line);
    std::stringstream initial_state_stream(initial_state_line);
    std::stringstream initial_stack_stream(initial_stack_line);

    std::string tmp_str;
    char tmp_chr;

    while (states_stream >> tmp_str) states.emplace(tmp_str);
    while (input_symbols_stream >> tmp_chr) input_symbols.emplace(tmp_chr);
    while (stack_symbols_stream >> tmp_chr) stack_symbols.emplace(tmp_chr);
    initial_state_stream >> initial_state;
    initial_stack_stream >> initial_stack;

    std::string transition_line;
    while (std::getline(declaration_stream, transition_line)) {
        Transition transition(transition_line);
        transitions.push_back(transition);
    }


    std::cout << "Reading correct? " << states_stream.eof() << input_symbols_stream.eof() << stack_symbols_stream.eof()
              << initial_state_stream.eof() << (initial_stack_line.size() == 1) << "\n";
    printf("states: [ ");
    for (std::string str : states) printf("%s ", str.c_str());
    printf("]\ninput symbols: [ ");
    for (char c : input_symbols) printf("%c ", c);
    printf("]\nstack symbols: [ ");
    for (char c : stack_symbols) printf("%c ", c);
    printf("]\ninitial state: %s\n", initial_state.c_str());
    printf("initial stack: %c\ntransitions: [\n", initial_stack);
    for (Transition t : transitions) std::cout << t << "\n";
    printf("]\n");
}

bool StackAutomaton::solve(std::string word) const {
    return true;
}