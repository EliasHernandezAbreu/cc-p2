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

bool StackAutomaton::solve(std::string word, bool trace) const {
    // Add initial transitions to the stack
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

    // Try each trantition in fi-lo order (stack)
    if (trace)
        printf("%10s | %10s | %10s | %15s\n\n", "State", "Word", "Stack", "Transitions");
    if (trace) {
        std::stringstream pnt_str;
        bool first = true;
        for (int pnt : possible_next_transitions) {
            if (!first) pnt_str << ", ";
            pnt_str << pnt;
            first = false;
        }
        printf("%10s | %10s | %10s | %15s\n",
               initial_state.c_str(), word.c_str(),
               initial_stack_str.c_str(), pnt_str.str().c_str());
    }

    while (!runtime_stack.empty()) {
        StackAutomatonRuntime current_runtime = runtime_stack.top();
        runtime_stack.pop();

        // Take transition
        Transition t = transitions[current_runtime.next_transition];
        std::string current_word;
        std::string current_stack;
        std::string current_state;
        if (t.get_input_read() != '.') current_word = current_runtime.word.erase(0, 1);
        else current_word = current_runtime.word;
        current_stack = current_runtime.stack.erase(0, 1);
        if (t.get_stack_write() != ".")
            current_stack.insert(current_stack.begin(), t.get_stack_write().begin(), t.get_stack_write().end());
        current_state = t.get_to_state();
        if (current_stack.empty() && current_word.empty()) {
            if (!trace) return true;
            // stack is empty so there cant be any transitions
            printf("%10s | %10s | %10s | %15s\n",
                   current_state.c_str(), current_word.c_str(),
                   current_stack.c_str(), "");
            return true;
        }

        // Get next transitions and add them to the stack
        possible_next_transitions = getPossibleTransitions(current_state, current_word, current_stack); 
        for (int t_index : possible_next_transitions) {
            Transition transition = transitions[t_index];
            runtime.current_state = current_state;
            runtime.word = current_word;
            runtime.next_transition = t_index;
            runtime.stack = current_stack;
            runtime_stack.push(runtime);
        }

        // Print trace
        if (!trace) continue;
        std::stringstream pnt_str;
        bool first = true;
        for (int pnt : possible_next_transitions) {
            if (!first) pnt_str << ", ";
            pnt_str << pnt;
            first = false;
        }
        printf("%10s | %10s | %10s | %15s\n",
               current_state.c_str(), current_word.c_str(),
               current_stack.c_str(), pnt_str.str().c_str());
    }

    return false;
}

std::vector<int> StackAutomaton::getPossibleTransitions(std::string state, std::string word, std::string stack) const {
    std::vector<int> possible_transitions;
    for (int i = 0; i < transitions.size(); i++) {
        Transition t = transitions[i];
        if (t.get_from_state() == state &&
            (t.get_input_read() == word[0] || t.get_input_read() == '.') &&
            t.get_stack_read() == stack[0]) possible_transitions.push_back(i);
    }
    return possible_transitions;
}
