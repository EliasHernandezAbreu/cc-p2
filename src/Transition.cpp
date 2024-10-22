/**
 * Complejidad Computacional
 * Practica 2 - Automata de pila
 * 
 * @author Elías Hernández Abreu
 * @brief Transition definition
 */

#include <sstream>
#include <iostream>

#include "Transition.hpp"

Transition::Transition(std::string line) {
    std::stringstream line_stream(line);
    line_stream >> from_state;
    line_stream >> input_read;
    line_stream >> stack_read;
    line_stream >> to_state;
    line_stream >> stack_write;
}

std::ostream& operator<<(std::ostream& out, const Transition& transition) {
    out << "{" << transition.from_state << ", " << transition.input_read << ", "
              << transition.stack_read << ", " << transition.to_state << ", " 
              << transition.stack_write << "}";
    return out; 
}
