/**
 * Complejidad Computacional
 * Practica 2 - Automata de pila
 * 
 * @author Elías Hernández Abreu
 * @brief Transition header
 */

#pragma once

#include <string>

class Transition {
public:
    /**
    * Reads a transition from a string
    * @param line The line with the transition definition
    */
    Transition(std::string line);

    /**
    * Gets the state of the transition
    * @returns The state of the transition
    */
    const std::string& get_from_state() const { return from_state; }

    /**
    * Gets the input read of the transition
    * @returns The input read of the transition
    */
    const char& get_input_read() const { return input_read; }

    /**
    * Gets the stack read of the transition
    * @returns The stack read of the transition
    */
    const char& get_stack_read() const { return stack_read; }

    /**
    * Gets the ending state of the transition
    * @returns The ending state of the transition
    */
    const std::string& get_to_state() const { return to_state; }

    /**
    * Gets the stack write of the transition
    * @returns The stack write of the transition
    */
    const std::string& get_stack_write() const { return stack_write; }

    /**
    * Overload of printing operator
    * @param out The outgoing stream
    * @param transition The transition to print
    * @returns The outgoing stream
    */
    friend std::ostream& operator<<(std::ostream& out, const Transition& transition);

private:
    std::string from_state;
    char input_read;
    char stack_read;
    std::string to_state;
    std::string stack_write;
};
