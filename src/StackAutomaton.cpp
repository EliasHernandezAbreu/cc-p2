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

    if (states.find(initial_state) == states.end())
        throw std::runtime_error("Initial state not in states");
    if (stack_symbols.find(initial_stack) == stack_symbols.end())
        throw std::runtime_error("Initial stack symbol not in stack symbol set");
    for (Transition tr : transitions) {
        if (states.find(tr.get_from_state()) == states.end())
            throw std::runtime_error("Transition initial state not in states");
        if (states.find(tr.get_to_state()) == states.end())
            throw std::runtime_error("Transition final state not in states");
        if (input_symbols.find(tr.get_input_read()) == input_symbols.end() && tr.get_input_read() != '.')
            throw std::runtime_error("Transition input read not in input symbols");
        if (stack_symbols.find(tr.get_stack_read()) == stack_symbols.end())
            throw std::runtime_error("Transition stack read not in stack symbols");
        if (tr.get_stack_write() != ".") {
            for (char c : tr.get_stack_write()) {
                if (stack_symbols.find(tr.get_stack_read()) == stack_symbols.end())
                    throw std::runtime_error("Transition stack write symbol not in stack symbols");
            }
        }
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

std::vector<int> StackAutomaton::getPossibleTransitions(std::string state, std::string word, std::string stack) const {
}

bool StackAutomaton::solve(std::string word) const {
    std::stack<StackAutomatonRuntime> runtime_stack;
    std::string initial_stack_str(1, initial_stack);
    std::vector<int> possible_next_transitions = getPossibleTransitions(initial_state, word, initial_stack_str);
    StackAutomatonRuntime runtime;
    runtime.current_state = initial_state;
    runtime.word = word;
    runtime.stack = initial_stack_str;
    for (int i : possible_next_transitions) {
        runtime.next_transition = i;
        runtime_stack.push(runtime);
    }

    while (!runtime_stack.empty()) {
        StackAutomatonRuntime current_runtime = runtime_stack.top();
        runtime_stack.pop();
        for (int t : possible_next_transitions) {
            Transition transition = transitions[t];
            runtime.current_state = transition.get_to_state();
            runtime.word = word;
            runtime.next_transition = t;
            runtime.stack = initial_stack_str;
            runtime_stack.push(runtime);
        }
    }

    return false;
}
