/**
 * Complejidad Computacional
 * Practica 2 - Automata de pila
 * 
 * @author Elías Hernández Abreu
 * @brief Main file
 */

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "StackAutomaton.hpp"

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf("You must specify the name of the file with the "
             "declaration of the automaton. User \"%s -h\" for further help.\n",
             argv[0]);
        return 1;
    }

    bool log = false;
    std::string file_name = "";
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printf("Runs an emptying stack automaton on the given strings, "
                   "which halts its execution when the stack empties or there "
                   "are no more input symbols to read. If both conditions are met, "
                   "the string belongs to the alphabet described.\n"
                   "\nArguments:\n"
                   "<FILE> : the file with the description of the automaton"
                   "\nOptions:\n"
                   "-h : print this message\n"
                   "-l : print a log of the execution\n");
            return 0;
        } else if (strcmp(argv[i], "-l") == 0) {
            log = true;
        } else {
            file_name = argv[i];
        }
    }

    if (file_name == "") {
        printf("You must specify the name of the file with the "
             "declaration of the automaton. User \"%s -h\" for further help.\n",
             argv[0]);
        return 1;
    }
    if (!std::filesystem::exists(file_name)) {
        printf("Could not open file \"%s\"\n", file_name.c_str());
        return 1;
    }
    std::ifstream input(file_name);
    if (!input.is_open()) {
        printf("Could not open file \"%s\"\n", file_name.c_str());
        return 1;
    }

    std::stringstream file_contents_buf;
    file_contents_buf << input.rdbuf();
    std::string file_contents = file_contents_buf.str();

    try {
        StackAutomaton automaton(file_contents);
        std::string word = "";
        std::cout << "Enter a word to analyse (use \".\" to exit): ";
        while (std::getline(std::cin, word)) {
            if (word == ".") break;
            bool belongs = automaton.solve(word, log);
            if (belongs) printf("The word %s belongs\n", word.c_str());
            else printf("The word %s does NOT belong\n", word.c_str());
            std::cout << "\nEnter a word to analyse (use \".\" to exit): ";
        }

    } catch (std::runtime_error e) {
        printf("%s\n", e.what());
    }

    return 0;
}
