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

    std::stringstream states_stream(states_line);
    std::stringstream input_symbols_stream(input_symbols_line);
    std::stringstream stack_symbols_stream(stack_symbols_line);
    std::stringstream initial_state_stream(initial_state_line);
    std::stringstream initial_stack_stream(initial_stack_line);

    std::string tmp_str;
    char tmp_chr;
    while (states_stream >> tmp_str) states.emplace(tmp_str);
    while (input_symbols_stream >> tmp_chr) input_symbols.emplace(tmp_chr);

    printf("states: [ ");
    for (std::string str : states) printf("%s ", str.c_str());
    printf("]\ninput symbols: [ ");
    for (char c : input_symbols) printf("%c ", c);
    printf("]");
}
