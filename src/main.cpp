/**
 * Complejidad Computacional
 * Practica 2 - Automata de pila
 * 
 * @author Elías Hernández Abreu
 * @brief Main file
 */

#include <cstdio>
#include <fstream>
#include <sstream>

#include "StackAutomaton.hpp"

int main (int argc, char *argv[]) {
    if (argc != 2) {
        puts("You must specify the name of the file with the"
             " declaration of the automaton");
        return 1;
    }

    std::string file_name = argv[1];
    std::ifstream input(file_name);
    if (input.bad()) {
        printf("Could not open file \"%s\"\n", file_name.c_str());
        return 1;
    }

    std::stringstream file_contents_buf;
    file_contents_buf << input.rdbuf();
    std::string file_contents = file_contents_buf.str();

    StackAutomaton automaton(file_contents);

    return 0;
}
